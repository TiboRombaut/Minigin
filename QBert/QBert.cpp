//#include <iostream>
#include <MiniginPCH.h>
#include <Minigin.h>

#include "TextureComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Scene.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "PlayerIndexComponent.h"
#include "SubjectComponent.h"
#include "ObserverPlayer.h"
using namespace dae;
void LoadGame()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	std::shared_ptr<TextureComponent> component{ std::make_shared<TextureComponent>() };
	component->SetTexture("background.jpg");
	go->addComponent(component);

	std::shared_ptr<TextureComponent> componentTexture{ std::make_shared<TextureComponent>() };
	componentTexture->SetTexture("logo.png");
	componentTexture->SetPosition(216, 180);
	go->addComponent(componentTexture);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto component2 = std::make_shared<TextComponent>("Programming 4 Assignment", font);
	component2->SetPosition(80, 20);
	go->addComponent(component2);

	auto component3 = std::make_shared<FPSComponent>();
	go->addComponent(component3);
	scene.Add(go);




	//init player
	int playerIndex{ 0 };
	auto& renderer = dae::Renderer::GetInstance();
	auto& input = dae::InputManager::GetInstance();

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

	renderer.InitPlayer(playerIndexComponent->GetIndexPlayer(), healtComponent->GetRemainingLives(), scoreComponent->GetScore());

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
	ChangeTextureCommand* changeTexture = new ChangeTextureCommand(go, component, "../Data/logo.png");

	input.AddCommand(ControllerButton::RightBump,KeyBoardAndMouseButton::MouseButtonRight, WayKeyBoardButton::MouseButtonUp,playSound);
	input.AddCommand(ControllerButton::LeftBump, KeyBoardAndMouseButton::MouseButtonMiddle, WayKeyBoardButton::MouseButtonDown, muteSound);
	input.AddCommand(ControllerButton::ButtonA, KeyBoardAndMouseButton::ButtonS, WayKeyBoardButton::buttonUp, kill);
	input.AddCommand(ControllerButton::ButtonB, KeyBoardAndMouseButton::ButtonD, WayKeyBoardButton::buttonUp, colorChange);
	input.AddCommand(ControllerButton::ButtonX, KeyBoardAndMouseButton::ButtonA, WayKeyBoardButton::buttonUp, defeatedCoily);
	input.AddCommand(ControllerButton::ButtonY, KeyBoardAndMouseButton::ButtonW, WayKeyBoardButton::buttonUp, caughtSlickOrSam);
	input.AddCommand(ControllerButton::Start, KeyBoardAndMouseButton::ButtonE, WayKeyBoardButton::buttonUp, remainingDisks);
	input.AddCommand(ControllerButton::DownDpad, KeyBoardAndMouseButton::ButtonArrowDown, WayKeyBoardButton::buttonDown, kill2);
	input.AddCommand(ControllerButton::LeftDpad, KeyBoardAndMouseButton::ButtonArrowLeft, WayKeyBoardButton::buttonDown, colorChange2);
	input.AddCommand(ControllerButton::RightDpad, KeyBoardAndMouseButton::ButtonArrowRight, WayKeyBoardButton::buttonDown, defeatedCoily2);
	input.AddCommand(ControllerButton::UpDpad, KeyBoardAndMouseButton::ButtonArrowUp, WayKeyBoardButton::buttonDown, caughtSlickOrSam2);
	input.AddCommand(ControllerButton::Back, KeyBoardAndMouseButton::ButtonSpace, WayKeyBoardButton::buttonDown, remainingDisks2);
	input.AddCommand(ControllerButton::None, KeyBoardAndMouseButton::ButtonC, WayKeyBoardButton::buttonDown, changeTexture);

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

int main()
{
	dae::Minigin engine;
	engine.Run(LoadGame);

	
	return 0;

	
}