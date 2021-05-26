#include "ControlComponent.h"


void ControlComponent::SetFieldData(FieldDataPlayer data)
{
	m_QBertFieldData = data;
}

FieldDataPlayer ControlComponent::GetFieldDataPlayer()const
{
	return m_QBertFieldData;
}

bool ControlComponent::GetCanMove()
{
	float minTime{0.5f};
	if (m_CurrentTime > minTime)
	{
		return true;
	}
	return false;
}
void ControlComponent::ResetCurrentTime()
{
	m_CurrentTime = 0.0f;
}
