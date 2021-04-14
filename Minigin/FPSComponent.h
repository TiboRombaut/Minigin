#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

class FPSComponent :
	public dae::BaseComponent
{
public:
	FPSComponent();

	virtual ~FPSComponent();
	void Update() override;
	void Render() const override;

	void SetPosition(float x, float y);

	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;
private:
	float m_UpdateTime;
	std::shared_ptr<dae::TextComponent> m_pTextComponent;
};
