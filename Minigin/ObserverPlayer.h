#pragma once
#include "Observer.h"

namespace dae
{
	class ObserverPlayer final : public Observer
	{
	public:
		~ObserverPlayer() override = default;
		void Notify(const GameObject* object, Event event)override;
	};
}

