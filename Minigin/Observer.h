#pragma once
#include "GameObject.h"

namespace dae
{
	enum class Event
	{
		PlayerDied,
		ScoreIncrease
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const GameObject* object, Event event) = 0;
	};
}
