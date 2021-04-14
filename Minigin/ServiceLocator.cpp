#include "MiniginPCH.h"
#include "ServiceLocator.h"

dae::Null_Sound_System dae::ServiceLocator::m_Default_ss{};
dae::Sound_System* dae::ServiceLocator::m_ss_Instance{ &m_Default_ss };

dae::Sound_System& dae::ServiceLocator::get_sound_system()
{
	return *m_ss_Instance;
}

void dae::ServiceLocator::register_sound_system(Sound_System* ss)
{
	m_ss_Instance = ss == nullptr ? &m_Default_ss : ss;
}