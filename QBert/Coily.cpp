#include "Coily.h"

#include <GameTime.h>
#include <memory>
#include <GameObject.h>
Coily::Coily(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field)
	:m_CoilyGameObject(pObject)
{
	m_pCommandMoveLeftUp = new MoveLeftUpCommand(pObject, field, "../Data/BackGroundTileYellow.png");
	m_pCommandMoveRightUp = new MoveRightUpCommand(pObject, field, "../Data/BackGroundTileYellow.png");
	m_pCommandMoveRightDown = new MoveRightDownCommand(pObject, field, "../Data/BackGroundTileYellow.png");
	m_pCommandMoveLeftDown = new MoveLeftDownCommand(pObject, field, "../Data/BackGroundTileYellow.png");
}

Coily::~Coily()
{
	delete m_pCommandMoveLeftUp;
	delete m_pCommandMoveRightUp;
	delete m_pCommandMoveRightDown;
	delete m_pCommandMoveLeftDown;
}



void Coily::Update()
{
	m_CurrentTime += GameTime::GetInstance().GetDeltaTime();

	if (GetCanMove())
	{
		if (IsEgg)
		{
			int whatMovement = rand() % 2;
			switch (whatMovement)
			{
			case 0:
				//move left
				m_pCommandMoveLeftDown->Execute();
				break;
			case 1:
				//move right
				m_pCommandMoveRightDown->Execute();
				break;
			default:
				//nothing
				break;
			}

			if (m_QBertFieldData.Row == 6)
			{
				std::cout << "reachedBottom\n";
				IsEgg = false;
				//change texture
				m_CoilyGameObject->GetComponent<dae::TextureComponent>()->SetTexture("../Data/Coily.png");
				// //startPathfinding
				//GetGameObject()->SetIsActive(false);
			}
		}
		else
		{
			//do pathfinding
			//std::cout << "pathfinding\n";
		}
	}

}