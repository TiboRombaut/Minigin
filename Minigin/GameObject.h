#pragma once
#include "Transform.h"
#include "BaseComponent.h"
#include "Command.h"

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		void Update();
		void Render() const;

		void SetPosition(float x, float y);
	//	void AddComponent(BaseComponent* component);

		void addComponent(std::shared_ptr<BaseComponent > component);
		//void AddCommand(std::shared_ptr < Command> pCommand);

		template <typename T>
		T* GetComponent() const
		{
			for (const std::shared_ptr<BaseComponent>& component : m_Components)
			{
				T* temp = dynamic_cast<T*>(component.get());
				if (temp != nullptr)
				{
					return temp;
				}
			}
			return nullptr;
		}

		//template <typename T>
		//T* GetComponent() const
		//{
		//	for (BaseComponent* component : m_Components)
		//	{
		//		if (dynamic_cast<T*>(component)) return (T*)component;
		//	}
		//	return nullptr;
		//}
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_Components;
		//std::vector<BaseComponent*> m_Components;
		Transform m_Transform;
		//std::vector<std::shared_ptr<Command>> m_pCommands;
	};
}
