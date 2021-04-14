#include "MiniginPCH.h"
#include "HealthComponent.h"

#include "GameObject.h"
#include "SubjectComponent.h"
dae::HealthComponent::HealthComponent()
	: BaseComponent()
	, m_MaxLives(3)
{
	m_CurrentLives = m_MaxLives;
}

void dae::HealthComponent::LoseLive()
{
	m_CurrentLives--;
	m_pObject->GetComponent<SubjectComponent>()->Notify(m_pObject, Event::PlayerDied);
}