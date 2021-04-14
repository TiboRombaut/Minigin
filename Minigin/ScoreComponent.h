#pragma once
#include "BaseComponent.h"

namespace dae
{
	class ScoreComponent :
		public dae::BaseComponent
	{
	public:
		ScoreComponent();
		~ScoreComponent() = default;

		void Update() override {};
		void Render() const override {};

		void AddScore(int amount);
		int GetScore()const { return m_CurrentScore; };
	private:
		int m_CurrentScore;
	};
}
