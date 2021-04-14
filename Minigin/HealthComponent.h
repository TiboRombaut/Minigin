#pragma once
#include "BaseComponent.h"

namespace dae {
	class HealthComponent :
		public dae::BaseComponent
	{
	public:
		HealthComponent();
		~HealthComponent() = default;

		void Update() override {};
		void Render() const override {};

		void LoseLive();
		int GetRemainingLives()const { return m_CurrentLives; };
	private:
		int m_MaxLives;
		int m_CurrentLives;
	};
}

