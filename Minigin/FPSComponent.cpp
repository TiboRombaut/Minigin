#include "MiniginPCH.h"
#include "FPSComponent.h"

#include "ResourceManager.h"
#include "GameTime.h"

FPSComponent::FPSComponent()
{
	m_UpdateTime = 0.0f;
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);

	m_pTextComponent = std::make_shared<dae::TextComponent>("FPS", font);
}

FPSComponent::~FPSComponent()
{
}

void FPSComponent::Update()
{
	m_UpdateTime += GameTime::GetInstance().GetDeltaTime();
	if (m_UpdateTime >= 1.0f)
	{
		m_pTextComponent->SetText(std::to_string(GameTime::GetInstance().GetFPS()) + " FPS");
		m_pTextComponent->Update();
		m_UpdateTime -= 1.0f;
	}
}

void FPSComponent::Render() const
{
	m_pTextComponent->Render();
}

void FPSComponent::SetPosition(float x, float y)
{
	m_pTextComponent->SetPosition(x, y);
}