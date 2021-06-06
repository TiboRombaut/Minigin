#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(const std::string& fileName)
{
	SetTexture(fileName);
}

void dae::TextureComponent::Update() {}

void dae::TextureComponent::Render() const
{
	const auto pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
	m_FileName = fileName;
}

void dae::TextureComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

int dae::TextureComponent::GetWidth() const
{
	return m_pTexture->GetWidth();
}

int dae::TextureComponent::GetHeight() const
{
	return m_pTexture->GetHeight();
}

std::string dae::TextureComponent::GetFileName()const
{
	return m_FileName;
}

