#include "MiniginPCH.h"
#include "GameObject.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (size_t i = 0; i < m_Components.size(); ++i)
	{
		m_Components[i]->Update();
	}
}

//void dae::GameObject::AddCommand(std::shared_ptr < Command> pCommand)
//{
//	//std::vector<Command*>::const_iterator isCommandAlreadyInVector =
//	//	std::find_if(m_pCommands.cbegin(), m_pCommands.cend(), [pCommand](Command* pC)->bool
//	//		{
//	//			return pCommand == pC;
//	//		});
//	//if (isCommandAlreadyInVector == m_pCommands.cend())
//	//{
//	////	std::cout << typeid(*pCommand).name(), ErrorLevel::warning);
//	//	//Logger::GetInstance().Log(" was already added!\n", ErrorLevel::warning);
//	//}
//	m_pCommands.push_back(pCommand);
//}


void dae::GameObject::Render() const
{
	for (size_t i = 0; i < m_Components.size(); ++i)
	{
		m_Components[i]->Render();
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
