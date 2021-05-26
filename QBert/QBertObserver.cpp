#include "QBertObserver.h"
#include "HealthComponent.h"
#include "Renderer.h"
#include "ScoreComponent.h"
#include "PlayerIndexComponent.h"
#include <iostream>

void QBertObserver::Notify(const dae::GameObject* object, dae::Event event)
{
	switch (event)
	{
	case dae::Event::PlayerDied:
		std::cout << "PlayerDied : " << object->GetComponent<dae::HealthComponent>()->GetRemainingLives() << std::endl;
		//dae::Renderer::GetInstance().UpdateLives(object->GetComponent<dae::PlayerIndexComponent>()->GetIndexPlayer(), object->GetComponent<dae::HealthComponent>()->GetRemainingLives());
		m_HealthComp->SetText("Health: " + std::to_string(object->GetComponent<dae::HealthComponent>()->GetRemainingLives()));

		break;
	case dae::Event::ScoreIncrease:
		std::cout << "Increasing score: " << object->GetComponent<dae::ScoreComponent>()->GetScore() << std::endl;
		//dae::Renderer::GetInstance().UpdateScore(object->GetComponent<dae::PlayerIndexComponent>()->GetIndexPlayer(), object->GetComponent<dae::ScoreComponent>()->GetScore());
		m_ScoreComp->SetText("Score: " + std::to_string(object->GetComponent<dae::ScoreComponent>()->GetScore()));
		
		break;
	default:
		break;
	}
}

void QBertObserver::SetScoreComp(std::shared_ptr<dae::TextComponent> scoreComp)
{
	m_ScoreComp = scoreComp;
}

void QBertObserver::SetHealthComp(std::shared_ptr<dae::TextComponent> healthComp)
{
	m_HealthComp = healthComp;
}