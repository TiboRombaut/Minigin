#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{

    class SubjectComponent : public dae::BaseComponent
    {
    public:
        SubjectComponent();
        virtual ~SubjectComponent();

        void Update() override {};
        void Render() const override {};

        void AddObserver(std::shared_ptr<Observer> pObserver);
        void RemoveObserver(std::shared_ptr<Observer> pObserver);
        void Notify(GameObject* pObject, Event event);

        SubjectComponent(const SubjectComponent& other) = delete;
        SubjectComponent(SubjectComponent&& other) = delete;
        SubjectComponent& operator=(const SubjectComponent& other) = delete;
        SubjectComponent& operator=(SubjectComponent&& other) = delete;
    private:
        std::vector<std::shared_ptr<Observer>> m_pObservers;
    };
}

