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


void dae::SubjectComponent::addObserver(std::shared_ptr<Observer> observer)
{
	m_pObservers.push_back(std::move(observer));
}

void dae::SubjectComponent::removeObserver(std::shared_ptr<Observer> observer)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer));
}

void dae::SubjectComponent::Notify(GameObject* object, Event event)
{
	for(size_t i = 0; i < m_pObservers.size();++i)
	{
		m_pObservers[i]->Notify(object, event);
	}
}