#include <SDL.h>
#undef main

#include <Minigin.h>
#include <TextureComponent.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include <ScoreComponent.h>
#include <InputManager.h>
#include <Renderer.h>
#include <Scene.h>
#include <TextComponent.h>
#include <FPSComponent.h>
#include <PlayerIndexComponent.h>
#include <SubjectComponent.h>
#include <ObserverPlayer.h>
#include <memory>
#include <iostream>
#include <vector>
#include "Structs.h"
#include "QBertComponent.h"
#include "CommandQbert.h"
#include "AIComponent.h"
using namespace dae;


void LoadGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> component{ std::make_shared<dae::TextureComponent>() };
	component->SetTexture("background.jpg");
	go->addComponent(component);

	
	std::vector<FieldData> m_Field;

	float widthStartPos = 250;
	float HeightStartPos = 200;
	float textureWidth = 0;
	float textureHeight = 0;
	for (int row = 0; row < 7; ++row)
	{
		//The row we are on determines how many colums we have
		int temp = row + 1;
		for (int column = 0; column < temp; ++column)
		{
			if (row == 4 && column == 0)
			{
				std::shared_ptr<TextureComponent> componentTextureColorWheel{ std::make_shared<TextureComponent>() };
				componentTextureColorWheel->SetTexture("ColorWheel.png");
				float posXColorWheel = widthStartPos - (textureWidth/3);

				componentTextureColorWheel->SetPosition(posXColorWheel, HeightStartPos - textureHeight /3);
				FieldData currentDataColorWheel;
				currentDataColorWheel.Row = row-1;
				currentDataColorWheel.Column = column-1;
				currentDataColorWheel.MiddlePosX = posXColorWheel + textureWidth / 4;
				currentDataColorWheel.MiddlePosY = HeightStartPos;
				currentDataColorWheel.TextureComponent = componentTextureColorWheel;

				m_Field.push_back(currentDataColorWheel);
				go->addComponent(componentTextureColorWheel);
			}
			else if (row == 4 && column == temp - 1)
			{
				std::shared_ptr<TextureComponent> componentTextureColorWheel{ std::make_shared<TextureComponent>() };
				componentTextureColorWheel->SetTexture("ColorWheel.png");
				float posXColorWheel = widthStartPos + (column * textureWidth) + textureWidth;

				componentTextureColorWheel->SetPosition(posXColorWheel, HeightStartPos- textureHeight/3);
				FieldData currentDataColorWheel;
				currentDataColorWheel.Row = row-1;
				currentDataColorWheel.Column = column;
				currentDataColorWheel.MiddlePosX = posXColorWheel + textureWidth / 4;
				currentDataColorWheel.MiddlePosY = HeightStartPos;
				currentDataColorWheel.TextureComponent = componentTextureColorWheel;

				m_Field.push_back(currentDataColorWheel);
				go->addComponent(componentTextureColorWheel);
			}

			std::shared_ptr<TextureComponent> componentTexture{ std::make_shared<TextureComponent>() };
			componentTexture->SetTexture("BackGroundTileRed.png");
			if (row == 0)
			{
				textureWidth = float(componentTexture->GetWidth());
				textureHeight = float(componentTexture->GetHeight());
			}


			float posX = widthStartPos + (column * textureWidth);

			componentTexture->SetPosition(posX, HeightStartPos);
			FieldData currentData;
			currentData.Row = row;
			currentData.Column = column;
			currentData.MiddlePosX = posX + textureWidth / 4;
			currentData.MiddlePosY = HeightStartPos;
			currentData.TextureComponent = componentTexture;
			
			m_Field.push_back(currentData);
			go->addComponent(componentTexture);
		}
		widthStartPos -= textureWidth / 2;
		HeightStartPos += textureHeight / 4 * 3;
	}


	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto component2 = std::make_shared<TextComponent>("Programming 4 Assignment", font);
	component2->SetPosition(80, 20);
	go->addComponent(component2);

	auto component3 = std::make_shared<FPSComponent>();
	go->addComponent(component3);
	scene.Add(go);

	auto qBertComponent = std::make_shared<dae::GameObject>();
	FieldDataPlayer QBertFieldData;
	QBertFieldData.Row = m_Field[0].Row;
	QBertFieldData.Column = m_Field[0].Column;

	std::shared_ptr<TextureComponent> componentTextureQBert{ std::make_shared<TextureComponent>() };
	componentTextureQBert->SetTexture("QBert.png");
	componentTextureQBert->SetPosition(m_Field[0].MiddlePosX, m_Field[0].MiddlePosY);
	std::shared_ptr<QBertComponent> componentQbertData{ std::make_shared<QBertComponent>() };
	qBertComponent->addComponent(componentTextureQBert);
	componentQbertData->SetFieldData(QBertFieldData);
	qBertComponent->addComponent(componentQbertData);
	scene.Add(qBertComponent);

	auto UggComponent = std::make_shared<dae::GameObject>();
	FieldDataPlayer UggFieldData;
	UggFieldData.Row = m_Field[20].Row;
	UggFieldData.Column = m_Field[20].Column;

	std::shared_ptr<TextureComponent> componentTextureUgg{ std::make_shared<TextureComponent>() };
	componentTextureUgg->SetTexture("EnemyUgg.png");
	componentTextureUgg->SetPosition(m_Field[20].MiddlePosX, m_Field[20].MiddlePosY);
	std::shared_ptr<AIComponent> componentUggData{ std::make_shared<AIComponent>(UggComponent ,m_Field) };
	UggComponent->addComponent(componentTextureUgg);
	componentUggData->SetFieldData(UggFieldData);
	UggComponent->addComponent(componentUggData);
	scene.Add(UggComponent);

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
//	//ChangeTextureCommand* changeTexture = new ChangeTextureCommand(go, component, "../Data/logo.png");
	MoveLeftDownCommand* moveLeft = new MoveLeftDownCommand(qBertComponent, m_Field, "../Data/BackGroundTileYellow.png");
	MoveRightDownCommand* moveRight= new MoveRightDownCommand(qBertComponent, m_Field, "../Data/BackGroundTileYellow.png");
	MoveLeftUpCommand* moveLeftUp = new MoveLeftUpCommand(qBertComponent, m_Field, "../Data/BackGroundTileYellow.png");
	MoveRightUpCommand* moveRightUp = new MoveRightUpCommand(qBertComponent, m_Field, "../Data/BackGroundTileYellow.png");
//	qBertComponent
	input.AddCommand(ControllerButton::None,KeyBoardAndMouseButton::ButtonA, WayKeyBoardButton::buttonDown, moveLeft);
	input.AddCommand(ControllerButton::None,KeyBoardAndMouseButton::ButtonD, WayKeyBoardButton::buttonDown, moveRight);
	input.AddCommand(ControllerButton::None,KeyBoardAndMouseButton::ButtonQ, WayKeyBoardButton::buttonDown, moveLeftUp);
	input.AddCommand(ControllerButton::None,KeyBoardAndMouseButton::ButtonE, WayKeyBoardButton::buttonDown, moveRightUp);
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
	input.AddCommand(ControllerButton::Back, KeyBoardAndMouseButton::Button0, WayKeyBoardButton::buttonDown, remainingDisks2);
	//input.AddCommand(ControllerButton::None, KeyBoardAndMouseButton::ButtonC, WayKeyBoardButton::buttonDown, changeTexture);

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