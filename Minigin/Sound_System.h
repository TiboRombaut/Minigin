#pragma once
//#include "../3rdParty/SDL_Audio/audio.h"
#include <mutex>
#include <queue>

namespace dae
{
	class Sound_System
	{
	public:
		Sound_System() = default;

		virtual ~Sound_System() = default;
		virtual void Play(int soundId, float volume, std::string fileName) = 0;
		virtual void ToggleMute() = 0;

		Sound_System(const Sound_System&) = delete;
		Sound_System& operator=(const Sound_System&) = delete;
		Sound_System(Sound_System&&) = delete;
	};

	class Null_Sound_System final : public Sound_System
	{
	public:
		~Null_Sound_System()override = default;
		void Play(int , float,std::string )override{}
		void ToggleMute() override {}
	};
}

