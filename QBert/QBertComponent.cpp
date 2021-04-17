#include "QBertComponent.h"
#include <GameTime.h>
//FieldDataPlayer QBertComponent::GetFieldData()const
//{
//	return m_QBertFieldData;
//}
//
//void QBertComponent::SetFieldData(FieldDataPlayer data)
//{
//	m_QBertFieldData = data;
//}
//
//bool QBertComponent::GetCanMove()
//{
//	//float minTime{0.5f};
//	//if (m_CurrentTime > minTime)
//	//{
//	//	m_CurrentTime = 0.0f;
//	//	return true;
//	//}
//	//return false;
//
//}

void QBertComponent::Update()
{
	m_CurrentTime += GameTime::GetInstance().GetDeltaTime();
}