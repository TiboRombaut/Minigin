#pragma once
#include "BaseComponent.h"

namespace dae
{
	class PlayerIndexComponent :
		public dae::BaseComponent
	{
	public:
		PlayerIndexComponent(int index);
		PlayerIndexComponent() = default;
		~PlayerIndexComponent() = default;

		void Update() override {};
		void Render() const override {};
		void setIndex(int index) { m_CurrentIndexPlayer = index; };
		int GetIndexPlayer()const { return m_CurrentIndexPlayer; };
	private:
		int m_CurrentIndexPlayer;
	};
}

