#pragma once
#include "Sound_System.h"

namespace dae
{
	class ConsoleSoundSystem final : public Sound_System
	{
	public:
		ConsoleSoundSystem(Sound_System* pSoundSystem);
		~ConsoleSoundSystem() override = default;
		void Play(int soundId, float volume,std::string fileName) override;
		void ToggleMute() override;
	private:
		Sound_System* m_pSoundSystem{ nullptr };
	};
}

