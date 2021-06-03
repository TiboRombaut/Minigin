#include "UggAndWrongway.h"

#include <GameTime.h>
#include <memory>
#include <GameObject.h>
UggAndWrongway::UggAndWrongway(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field,
	float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> textureComp)
	:AIComponent(timeItTakesToMove,textureComp)
{
	m_pCommandMoveLeftUp = new MoveLeftUpCommand(pObject, field, "../Data/BackGroundTileYellow.png");
	m_pCommandMoveRightUp = new MoveRightUpCommand(pObject, field, "../Data/BackGroundTileYellow.png");
}

UggAndWrongway::~UggAndWrongway()
{
	delete m_pCommandMoveLeftUp;
	delete m_pCommandMoveRightUp;
}

void UggAndWrongway::Update()
{
	m_CurrentTime += GameTime::GetInstance().GetDeltaTime();

	if (m_NeedsToMove)
	{
		UpdateMovement();
	}

	if (GetCanMove())
	{
		//std::cout << "move ugg and wrongway"
		if (m_QBertFieldData.Row == 0 && m_QBertFieldData.Column == 0)
		{
			GetGameObject()->SetIsActive(false);
		}
		int whatMovement = rand() % 2;
		switch (whatMovement)
		{
		case 0:
			//move left
			m_pCommandMoveLeftUp->Execute();
			break;
		case 1:
			//move right
			m_pCommandMoveRightUp->Execute();
			break;
		default:
			//nothing
			break;
		}
	}

}