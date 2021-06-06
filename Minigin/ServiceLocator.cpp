#include "MiniginPCH.h"
#include "ServiceLocator.h"

dae::Null_Sound_System dae::ServiceLocator::m_Default_ss{};
dae::Sound_System* dae::ServiceLocator::m_pSs_Instance{ &m_Default_ss };

dae::Sound_System& dae::ServiceLocator::Get_Sound_System()
{
	return *m_pSs_Instance;
}

void dae::ServiceLocator::Register_Sound_System(Sound_System* pSs)
{
	m_pSs_Instance = pSs == nullptr ? &m_Default_ss : pSs;
}