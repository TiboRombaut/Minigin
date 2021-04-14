#include "MiniginPCH.h"
#include "ConsoleSoundSystem.h"

dae::ConsoleSoundSystem::ConsoleSoundSystem(Sound_System* pSoundSystem)
	: m_pSoundSystem{ pSoundSystem }
{
}

void dae::ConsoleSoundSystem::Play(int soundId, float volume,std::string fileName)
{
	if (m_pSoundSystem != nullptr)
		 m_pSoundSystem->Play(soundId, volume,fileName);
}

void dae::ConsoleSoundSystem::ToggleMute()
{
	m_pSoundSystem->ToggleMute();
}
