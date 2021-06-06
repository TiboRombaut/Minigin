#include "MiniginPCH.h"
#include "SubjectComponent.h"
#include "Observer.h"
#include "GameObject.h"

dae::SubjectComponent::SubjectComponent()
	: BaseComponent()
{
}

dae::SubjectComponent::~SubjectComponent()
{
}


void dae::SubjectComponent::AddObserver(std::shared_ptr<Observer> pObserver)
{
	m_pObservers.push_back(std::move(pObserver));
}

void dae::SubjectComponent::RemoveObserver(std::shared_ptr<Observer> pObserver)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver));
}

void dae::SubjectComponent::Notify(GameObject* object, Event event)
{
	for(size_t i = 0; i < m_pObservers.size();++i)
	{
		m_pObservers[i]->Notify(object, event);
	}
}