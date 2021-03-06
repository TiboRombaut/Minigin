#pragma once

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent() = default;

		virtual void Update() = 0;
		virtual void Render() const = 0;
		void setGameObject(GameObject* pGameObject)
		{
			m_pObject = pGameObject;
		}

		GameObject* GetGameObject()const
		{
			return m_pObject;
		}

		bool GetIsActiveComponent()const
		{
			return m_IsActive;
		}

		void SetIsActiveComponent(bool isActive)
		{
			m_IsActive = isActive;
		}

		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
	protected:
		bool m_IsActive = true;
		GameObject* m_pObject = nullptr;
	};
}
