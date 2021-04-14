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
#include "PlayerIndexComponent.h"
#include "ScoreComponent.h"
#include "SubjectComponent.h"
#include "Time.h"
#include "ServiceLocator.h"
#include "SDL_Sound_System.h"
#include "ConsoleSoundSystem.h"
#include "../3rdParty/SDL_Audio/audio.h"
#include "ObserverPlayer.h"
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
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	std::shared_ptr<TextureComponent> component{ std::make_shared<TextureComponent>() };
	component->SetTexture("background.jpg");
	go->addComponent(component);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	component = std::make_shared<TextureComponent>();
	component->SetTexture("logo.png");
	component->SetPosition(216, 180);
	go->addComponent(component);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	auto component2 = std::make_shared<TextComponent>("Programming 4 Assignment", font);
	component2->SetPosition(80, 20);
	go->addComponent(component2);
	scene.Add(go);

	auto component3 = std::make_shared<FPSComponent>();
	go->addComponent(component3);
	scene.Add(go);



	//init player
	int playerIndex{ 0 };
	auto& renderer = Renderer::GetInstance();

	std::shared_ptr<ObserverPlayer> pPlayerObserver = std::make_shared<ObserverPlayer>();
	
	std::shared_ptr<GameObject> qBert = std::make_shared<GameObject>();
	std::shared_ptr<HealthComponent> healtComponent = std::make_shared<HealthComponent>();
	std::shared_ptr<SubjectComponent> subjectComponent = std::make_shared<SubjectComponent>();
	std::shared_ptr<ScoreComponent> scoreComponent = std::make_shared<ScoreComponent>();
	std::shared_ptr<PlayerIndexComponent> playerIndexComponent = std::make_shared<PlayerIndexComponent>(playerIndex);
	subjectComponent->addObserver(pPlayerObserver);
	qBert->addComponent(healtComponent);
	qBert->addComponent(scoreComponent);
	qBert->addComponent(subjectComponent);
	qBert->addComponent(playerIndexComponent);
	scene.Add(qBert);

	renderer.InitPlayer(playerIndexComponent->GetIndexPlayer(),healtComponent->GetRemainingLives(),scoreComponent->GetScore());

	playerIndex++;
	std::shared_ptr<GameObject> qBert2 = std::make_shared<GameObject>();
	std::shared_ptr<HealthComponent> healtComponent2 = std::make_shared<HealthComponent>();
	std::shared_ptr<SubjectComponent> subjectComponent2 = std::make_shared<SubjectComponent>();
	std::shared_ptr<ScoreComponent> scoreComponent2 = std::make_shared<ScoreComponent>();
	std::shared_ptr<PlayerIndexComponent> playerIndexComponent2 = std::make_shared<PlayerIndexComponent>(playerIndex);
	subjectComponent2->addObserver(pPlayerObserver);
	qBert2->addComponent(healtComponent2);
	qBert2->addComponent(scoreComponent2);
	qBert2->addComponent(subjectComponent2);
	qBert2->addComponent(playerIndexComponent2);
	scene.Add(qBert2);

	renderer.InitPlayer(playerIndexComponent2->GetIndexPlayer(), healtComponent2->GetRemainingLives(), scoreComponent2->GetScore());

	
	PlaySoundCommand* playSound = new PlaySoundCommand(qBert, "../Data/road.wav");
	MuteCommand* muteSound = new MuteCommand(qBert);
	Kill* kill = new Kill(qBert);
	ColorChange* colorChange = new ColorChange(qBert);
	CoilyDefeated* defeatedCoily = new CoilyDefeated(qBert);
	CatchingSlickOrSam* caughtSlickOrSam = new CatchingSlickOrSam(qBert);
	RemainingDisks* remainingDisks = new RemainingDisks(qBert);

	Kill* kill2 = new Kill(qBert2);
	ColorChange* colorChange2 = new ColorChange(qBert2);
	CoilyDefeated* defeatedCoily2 = new CoilyDefeated(qBert2);
	CatchingSlickOrSam* caughtSlickOrSam2 = new CatchingSlickOrSam(qBert2);
	RemainingDisks* remainingDisks2 = new RemainingDisks(qBert2);
	auto& input = InputManager::GetInstance();
	
	input.AddCommand(ControllerButton::RightBump,  playSound );
	input.AddCommand(ControllerButton::LeftBump, muteSound);
	input.AddCommand(ControllerButton::ButtonA, kill);
	input.AddCommand(ControllerButton::ButtonB, colorChange);
	input.AddCommand(ControllerButton::ButtonX, defeatedCoily);
	input.AddCommand(ControllerButton::ButtonY, caughtSlickOrSam);
	input.AddCommand(ControllerButton::Start,  remainingDisks);
	input.AddCommand(ControllerButton::DownDpad, kill2);
	input.AddCommand(ControllerButton::LeftDpad, colorChange2);
	input.AddCommand(ControllerButton::RightDpad, defeatedCoily2);
	input.AddCommand(ControllerButton::UpDpad,caughtSlickOrSam2);
	input.AddCommand(ControllerButton::Back, remainingDisks2);

	//printing controls:
	std::cout << "Controls: \n\n";
	std::cout << "Player1: \n";
	std::cout << "PlaySound:        Xbox Controller: A,	    Playstation: Cross \n";
	std::cout << "Color change:     Xbox Controller: B,	    Playstation: Circle \n";
	std::cout << "Defeating coily:  Xbox Controller: X,	    Playstation: Square \n";
	std::cout << "CaughtSlickOrSam: Xbox Controller: Y,	    Playstation: Triangle \n";
	std::cout << "Remaining disks:  Xbox Controller: Start,   Playstation: Options \n\n";
	
	std::cout << "Player2: Arrow = dpad on controller \n";
	std::cout << "Kill:             Xbox Controller: ArrowDown,  Playstation: ArrowDown \n";
	std::cout << "Color change:     Xbox Controller: ArrowLeft,  Playstation: ArrowLeft \n";
	std::cout << "Defeating coily:  Xbox Controller: ArrowRight, Playstation: ArrowRight \n";
	std::cout << "CaughtSlickOrSam: Xbox Controller: ArrowUp,    Playstation: ArrowUp \n";
	std::cout << "Remaining disks:  Xbox Controller: Back,       Playstation: Share \n\n";
}

void dae::Minigin::Cleanup()
{
	endAudio();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();
	SDL_Sound_System* pSoundSystem = new SDL_Sound_System();
	auto pConsoleSound = new ConsoleSoundSystem(pSoundSystem);
	ServiceLocator::register_sound_system(pConsoleSound);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();
		bool doContinue = true;

		while (doContinue)
		{
			time.Update();
			doContinue = input.ProcessInput();
			sceneManager.Update();
			//pSoundSystem->Update();
			renderer.Render();

			auto sleepTime = duration_cast<duration<float>>(time.GetPreviousTime() + milliseconds(int(time.GetMsPerFrame())) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	delete pConsoleSound;
	delete pSoundSystem;
	Cleanup();
}