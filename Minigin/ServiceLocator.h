#pragma once
#include "Sound_System.h"

namespace dae {

	class ServiceLocator final
	{
	public:
		static Sound_System& get_sound_system();
		static void register_sound_system(Sound_System* ss);
	private:
		static Sound_System* m_ss_Instance;
		static dae::Null_Sound_System m_Default_ss;
	};
}
