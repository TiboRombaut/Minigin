#pragma once
#include "Observer.h"
#include <memory>
#include "TextComponent.h"

class QBertObserver : public dae::Observer
{
public:
	~QBertObserver()override = default;
	void Notify(const dae::GameObject* pObject, dae::Event event)override;
	void SetScoreComp(std::shared_ptr<dae::TextComponent> pScoreComp);
	void SetHealthComp(std::shared_ptr<dae::TextComponent> pHealthComp);
private:
	int m_Score = 0;
	std::shared_ptr<dae::TextComponent> m_pScoreComp = nullptr;
	std::shared_ptr<dae::TextComponent> m_pHealthComp = nullptr;

};

