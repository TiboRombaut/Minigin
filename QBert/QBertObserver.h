#pragma once
#include "Observer.h"
#include <memory>
#include "TextComponent.h"
class QBertObserver : public dae::Observer
{
public:
	~QBertObserver()override = default;
	void Notify(const dae::GameObject * object, dae::Event event)override;
	//virtual void AddScore(int value) = 0;
	void SetScoreComp(std::shared_ptr<dae::TextComponent> scoreComp);
	void SetHealthComp(std::shared_ptr<dae::TextComponent> healthComp);
private:
	int m_Score = 0;
	std::shared_ptr<dae::TextComponent> m_ScoreComp = nullptr;
	std::shared_ptr<dae::TextComponent> m_HealthComp = nullptr;

};

