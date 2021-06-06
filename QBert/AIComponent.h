#pragma once
#include "ControlComponent.h"
#include "PlayingField.h"

class AIComponent : public ControlComponent
{
public:
	explicit AIComponent(float timeItTakesToMove,  std::shared_ptr<dae::TextureComponent> pTextureComp);

	virtual void Update() = 0;
	virtual void Render()const = 0;

	void SetIsDead(bool isDead);
	bool GetIsDead()const;

	~AIComponent() = default;
	AIComponent(const AIComponent& other) = delete;
	AIComponent(AIComponent&& other) = delete;
	AIComponent& operator=(const AIComponent& other) = delete;
	AIComponent& operator=(AIComponent&& other) = delete;
private:
	bool m_IsDead = false;
};

