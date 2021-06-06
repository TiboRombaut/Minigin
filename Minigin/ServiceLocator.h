#pragma once
#include "Sound_System.h"

namespace dae {

	class ServiceLocator final
	{
	public:
		static Sound_System& Get_Sound_System();
		static void Register_Sound_System(Sound_System* pSs);
	private:
		static Sound_System* m_pSs_Instance;
		static dae::Null_Sound_System m_Default_ss;
	};
}
