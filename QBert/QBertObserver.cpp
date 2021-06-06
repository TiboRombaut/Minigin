#include "QBertObserver.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

void QBertObserver::Notify(const dae::GameObject* pObject, dae::Event event)
{
	switch (event)
	{
	case dae::Event::PlayerDied:
		m_pHealthComp->SetText("Health: " + std::to_string(pObject->GetComponent<dae::HealthComponent>()->GetRemainingLives()));
		break;
	case dae::Event::ScoreIncrease:
		m_pScoreComp->SetText("Score: " + std::to_string(pObject->GetComponent<dae::ScoreComponent>()->GetScore()));
		break;
	default:
		break;
	}
}

void QBertObserver::SetScoreComp(std::shared_ptr<dae::TextComponent> pScoreComp)
{
	m_pScoreComp = pScoreComp;
}

void QBertObserver::SetHealthComp(std::shared_ptr<dae::TextComponent> pHealthComp)
{
	m_pHealthComp = pHealthComp;
}