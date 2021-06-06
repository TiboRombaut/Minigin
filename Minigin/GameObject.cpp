#include "MiniginPCH.h"
#include "GameObject.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	if (m_IsActive)
	{
		for (size_t i = 0; i < m_Components.size(); ++i)
		{
			if (m_Components[i]->GetIsActiveComponent())
			{
				m_Components[i]->Update();
			}
		}
	}
}

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> component)
{
	for (size_t i = 0; i < m_Components.size(); ++i)
	{
		if (m_Components[i] == component)
		{
			m_Components.erase(m_Components.begin() + i);
		}
	}
}

void dae::GameObject::Render() const
{
	if (m_IsActive)
	{
		for (size_t i = 0; i < m_Components.size(); ++i)
		{
			if (m_Components[i]->GetIsActiveComponent())
			{
				m_Components[i]->Render();
			}
		}
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::addComponent(std::shared_ptr<BaseComponent> component)
{
	
	component->setGameObject(this);
	m_Components.push_back(component);
}
