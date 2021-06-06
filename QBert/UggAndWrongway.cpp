#include "UggAndWrongway.h"

#include <GameTime.h>
#include <GameObject.h>

UggAndWrongway::UggAndWrongway(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField,
	float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> pTextureComp)
	:AIComponent(timeItTakesToMove, pTextureComp)
{
	m_pCommandMoveLeftUp = new MoveLeftUpCommand(pObject, pField);
	m_pCommandMoveRightUp = new MoveRightUpCommand(pObject, pField);
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
		if (m_FieldData.Row == 0 && m_FieldData.Column == 0)
		{
			GetGameObject()->SetIsActive(false);
		}
		int whatMovement = rand() % 2;
		switch (whatMovement)
		{
		case 0:
			m_pCommandMoveLeftUp->Execute();
			break;
		case 1:
			m_pCommandMoveRightUp->Execute();
			break;
		default:
			break;
		}
	}

}