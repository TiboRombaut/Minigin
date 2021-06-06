#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "ScoreComponent.h"
#include "SubjectComponent.h"
#include "GameTime.h"
#include "ServiceLocator.h"
#include "SDL_Sound_System.h"
#include "ConsoleSoundSystem.h"
#include "../3rdParty/SDL_Audio/audio.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
#pragma warning(push)
#pragma warning(disable: 6031)
	_putenv("SDL_AUDIODRIVER=DirectSound");
#pragma warning(pop)
	SDL_Init(SDL_INIT_AUDIO);
	initAudio();
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
}

void dae::Minigin::Cleanup()
{
	endAudio();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(std::function<void()> loadGame)
{
	Initialize();
	SDL_Sound_System* pSoundSystem = new SDL_Sound_System();
	auto pConsoleSound = new ConsoleSoundSystem(pSoundSystem);
	ServiceLocator::Register_Sound_System(pConsoleSound);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	loadGame();

	{
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = GameTime::GetInstance();
		auto& renderer = Renderer::GetInstance();
		bool doContinue = true;

		while (doContinue)
		{
			time.Update();
			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();

			auto sleepTime = duration_cast<duration<float>>(time.GetPreviousTime() + milliseconds(int(time.GetMsPerFrame())) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	delete pConsoleSound;
	delete pSoundSystem;
	Cleanup();
}