#pragma once
#include "Sound_System.h"

namespace dae
{
	struct PlaySound
	{
		int SoundId;
		float Volume;
		std::string FileName;
	};

	class SDL_Sound_System final : public Sound_System 
	{
	public:
		SDL_Sound_System();
		~SDL_Sound_System() override;
		void Play(int soundId, float volume,std::string fileName) override;
		void ToggleMute() override;
	private:
		void ProcessQueue();

		bool m_IsMuted{ false };
		std::queue<PlaySound> m_SoundQueue;
		std::thread m_Thread;
		std::mutex m_Mutex;		
		std::condition_variable m_WorkAvaible;
	};
}

