#include "MiniginPCH.h"
#include "ObserverPlayer.h"


#include "HealthComponent.h"
#include "Renderer.h"
#include "ScoreComponent.h"
#include "PlayerIndexComponent.h"



void dae::ObserverPlayer::Notify(const GameObject* object, Event event)
{
	switch (event)
	{
	case Event::PlayerDied:
		std::cout << "PlayerDied : " << object->GetComponent<dae::HealthComponent>()->GetRemainingLives() << std::endl;
		//dae::Renderer::GetInstance().UpdateLives(object->GetComponent<PlayerIndexComponent>()->GetIndexPlayer(), object->GetComponent<dae::HealthComponent>()->GetRemainingLives());
		break;
	case Event::ScoreIncrease:
		std::cout << "Increasing score: " << object->GetComponent<ScoreComponent>()->GetScore() << std::endl;
		//dae::Renderer::GetInstance().UpdateScore(object->GetComponent<PlayerIndexComponent>()->GetIndexPlayer(), object->GetComponent<ScoreComponent>()->GetScore());
		break;
	default:
		break;
	}
}
