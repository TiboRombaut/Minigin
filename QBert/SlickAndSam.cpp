#include "SlickAndSam.h"
#include <GameTime.h>
#include <memory>
#include <GameObject.h>
SlickAndSam::SlickAndSam(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field, 
	float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> textureComp)
	:AIComponent(timeItTakesToMove,textureComp)
{
	m_pCommandMoveLeftDown = new MoveLeftDownCommand(pObject, field, "../Data/BackGroundTileYellow.png");
	m_pCommandMoveRightDown = new MoveRightDownCommand(pObject, field, "../Data/BackGroundTileYellow.png");
}

SlickAndSam::~SlickAndSam()
{
	delete m_pCommandMoveLeftDown;
	delete m_pCommandMoveRightDown;
}

void SlickAndSam::Update()
{
	m_CurrentTime += GameTime::GetInstance().GetDeltaTime();

	if (m_NeedsToMove)
	{
		UpdateMovement();
	}

	if (GetCanMove())
	{
		std::cout << "moveCharacter";
		if (m_QBertFieldData.Row == 6)
		{
			GetGameObject()->SetIsActive(false);
		}
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
	}

}