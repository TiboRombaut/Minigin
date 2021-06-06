#pragma once
#include "GameObject.h"
#include "HealthComponent.h"
#include "TextureComponent.h"


class Command
{
protected:
	std::shared_ptr<dae::GameObject> getActor()const { return m_pActor; };
public:
	explicit  Command(std::shared_ptr<dae::GameObject> actor);
	virtual ~Command() = default;
	virtual void Execute() = 0;
private:
	std::shared_ptr<dae::GameObject> m_pActor;
};