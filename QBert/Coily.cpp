#include "Coily.h"

#include <GameTime.h>

Coily::Coily(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField, std::vector<std::shared_ptr<QBertComponent>>& Qberts,
	float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> pTextureComp, bool isPlayerControlled)
	:AIComponent(timeItTakesToMove, pTextureComp)
	,m_pCoilyGameObject(pObject)
	, m_pQBerts(Qberts)
	,m_IsPlayerControlled(isPlayerControlled)
{
	m_pCommandMoveLeftUp = new MoveLeftUpCommand(pObject, pField);
	m_pCommandMoveRightUp = new MoveRightUpCommand(pObject, pField);
	m_pCommandMoveRightDown = new MoveRightDownCommand(pObject, pField);
	m_pCommandMoveLeftDown = new MoveLeftDownCommand(pObject, pField);
}

Coily::~Coily()
{
	delete m_pCommandMoveLeftUp;
	delete m_pCommandMoveRightUp;
	delete m_pCommandMoveRightDown;
	delete m_pCommandMoveLeftDown;
}

MoveLeftUpCommand* Coily::GetCommandUpLeft()const
{
	return m_pCommandMoveLeftUp;
}

MoveRightUpCommand*  Coily::GetCommandUpRight()const
{
	return m_pCommandMoveRightUp;
}

MoveRightDownCommand* Coily::GetCommandDownRight()const
{
	return m_pCommandMoveRightDown;
}

MoveLeftDownCommand* Coily::GetCommandDownLeft()const
{
	return m_pCommandMoveLeftDown;
}

bool Coily::GetIsDead()const
{
	return m_IsDead;
}

void Coily::SetIsDead(bool isDead)
{
	m_IsDead = isDead;
}

void Coily::SetIsEgg(bool isEgg)
{
	m_IsEgg = isEgg;
}

void Coily::Update()
{
	m_CurrentTime += GameTime::GetInstance().GetDeltaTime();

	if (m_NeedsToMove)
	{
		UpdateMovement();
	}

	if (GetCanMove())
	{
		if (m_IsEgg)
		{
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

			if (m_FieldData.Row == 6)
			{
				m_IsEgg = false;
				m_pCoilyGameObject->GetComponent<dae::TextureComponent>()->SetTexture("../Data/Coily.png");
			}
		}
		else if(!m_IsPlayerControlled)
		{
			int qBertIndex{ 0 };

			if (m_pQBerts.size() > 1)
			{
				int distanceQBert{ 10000 };
				for (size_t i = 0; i < m_pQBerts.size(); ++i)
				{
					int rowResult = m_FieldData.Row - m_pQBerts[i]->GetFieldDataPlayer().Row;
					int colResult = m_FieldData.Column - m_pQBerts[i]->GetFieldDataPlayer().Column;
					if (rowResult < 0)
					{
						rowResult *= -1;
					}
					if (colResult < 0)
					{
						colResult *= -1;
					}

					int resultRowColDis = rowResult + colResult;
					if (resultRowColDis < distanceQBert)
					{
						qBertIndex = int(i);
						distanceQBert = resultRowColDis;
					}
				}
			}

			int rowResult = m_FieldData.Row - m_pQBerts[qBertIndex]->GetFieldDataPlayer().Row;
			int colResult = m_FieldData.Column - m_pQBerts[qBertIndex]->GetFieldDataPlayer().Column;

			if (colResult <= 0 && rowResult <= 0)
			{
				m_pCommandMoveRightDown->Execute();
				return;
			}
			if (colResult >= 0 && rowResult <= 0)
			{
				m_pCommandMoveLeftDown->Execute();
				return;
			}
			if (colResult <= 0 && rowResult >= 0)
			{
				m_pCommandMoveRightUp->Execute();
				return;
			}
			if (colResult >= 0 && rowResult >= 0)
			{
				m_pCommandMoveLeftUp->Execute();
				return;
			}
		}
	}

}