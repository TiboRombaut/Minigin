#include "SlickAndSam.h"

#include <GameTime.h>
#include <GameObject.h>

SlickAndSam::SlickAndSam(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField,
	float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> pTextureComp)
	:AIComponent(timeItTakesToMove, pTextureComp)
{
	m_pCommandMoveLeftDown = new MoveLeftDownCommand(pObject, pField);
	m_pCommandMoveRightDown = new MoveRightDownCommand(pObject, pField);
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
		if (m_FieldData.Row == 6)
		{
			GetGameObject()->SetIsActive(false);
		}
		int whatMovement = rand() % 2;
		switch (whatMovement)
		{
		case 0:
			m_pCommandMoveLeftDown->Execute();
			break;
		case 1:
			m_pCommandMoveRightDown->Execute();
			break;
		default:
			break;
		}
	}
}