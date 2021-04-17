#include "AIComponent.h"
#include <GameTime.h>
#include <memory>
#include <GameObject.h>
AIComponent::AIComponent(std::shared_ptr<dae::GameObject> pObject,std::vector<FieldData>& field)
{
	//std::shared_ptr<dae::GameObject> tempGameObject(GetGameObject());
	m_pCommandMoveLeftUp = new MoveLeftUpCommand(pObject, field, "../Data/BackGroundTileYellow.png");
	m_pCommandMoveRightUp = new MoveRightUpCommand(pObject, field, "../Data/BackGroundTileYellow.png");
}
//FieldDataPlayer AIComponent::GetFieldData()const
//{
//	return m_QBertFieldData;
//}

AIComponent::~AIComponent()
{
	delete m_pCommandMoveLeftUp;
	delete m_pCommandMoveRightUp;
}


//void AIComponent::SetFieldData(FieldDataPlayer data)
//{
//	m_QBertFieldData = data;
//}
//
//bool AIComponent::GetCanMove()
//{
//	float minTime{ 2.0f };
//	if (m_CurrentTime > minTime)
//	{
//		return true;
//	}
//	return false;
//}

void AIComponent::Update()
{
	m_CurrentTime += GameTime::GetInstance().GetDeltaTime();

	if (GetCanMove())
	{
		int whatMovement = rand() % 2;
		switch (whatMovement)
		{
		case 0 :
			//move left
			m_pCommandMoveLeftUp->Execute();
			break;
		case 1 :
			//move right
			m_pCommandMoveRightUp->Execute();
			break;
		default:
			//nothing
			break;
		}
	}

}