#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "SubjectComponent.h"

dae::ScoreComponent::ScoreComponent()
	: BaseComponent()
	,m_CurrentScore(0)
{
}

void dae::ScoreComponent::AddScore(int amount)
{
	m_CurrentScore += amount;
	m_pObject->GetComponent<SubjectComponent>()->Notify(m_pObject, Event::ScoreIncrease);
}