#include "MiniginPCH.h"
#include "SDL_Sound_System.h"
#include "../3rdParty/SDL_Audio/audio.c"

dae::SDL_Sound_System::SDL_Sound_System()
{
	m_Thread = std::thread([this]() { this->ProcessQueue(); });
}

dae::SDL_Sound_System::~SDL_Sound_System()
{
	m_WorkAvaible.notify_one();
	m_Thread.join();
	//do somethting with workavaible to stop thisprob the same before join
}

void dae::SDL_Sound_System::Play(int soundId,float volume,std::string fileName)
{
	PlaySound playSound{ soundId,volume,fileName };
	std::lock_guard<std::mutex> mLock{ m_Mutex };
	m_SoundQueue.push(playSound);
	m_WorkAvaible.notify_one();
}

void dae::SDL_Sound_System::ToggleMute()
{
	m_IsMuted = !m_IsMuted;
}

void dae::SDL_Sound_System::ProcessQueue()
{
	do
	{
		std::unique_lock<std::mutex> mLock{ m_Mutex };
		if (!m_SoundQueue.empty())
		{
			PlaySound soundToPlay = m_SoundQueue.front();
			m_SoundQueue.pop();
			if (!m_IsMuted)
			{
				playSound(soundToPlay.FileName.c_str(), static_cast<int>(SDL_MIX_MAXVOLUME * soundToPlay.Volume));
			}
		}

		if (m_SoundQueue.empty())
		{
			m_WorkAvaible.wait(mLock);
		}
	} while (!m_SoundQueue.empty());
}