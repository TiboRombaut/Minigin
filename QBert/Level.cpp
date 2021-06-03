#include "Level.h"
#include <TextureComponent.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include <ScoreComponent.h>
#include <InputManager.h>
#include <Renderer.h>
#include <TextComponent.h>
#include <FPSComponent.h>
#include <PlayerIndexComponent.h>
#include <SubjectComponent.h>
#include <ObserverPlayer.h>
#include <memory>
#include <iostream>
#include <vector>
#include "Structs.h"
#include "CommandQbert.h"
#include "QBertObserver.h"
#include "GameTime.h"
#include "UggAndWrongway.h"
#include "SlickAndSam.h"
#include "Coily.h"
#include "glm/vec2.hpp"
using namespace dae;
Level::Level()
{

}

void Level::LoadGameSolo(dae::Scene& currentScene)
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//qBert->SetIsActive(false);
	LoadGame(currentScene,font);
	auto qBert = std::make_shared<dae::GameObject>();
	FieldDataPlayer QBertFieldData;
	QBertFieldData.Row = m_PlayingField->GetPlayerFieldDataLast().Row;
	QBertFieldData.Column = m_PlayingField->GetPlayerFieldDataLast().Column;

	int playerIndex{ 0 };

	//std::shared_ptr<GameObject> qBertComponent = std::make_shared<GameObject>();
	//qBertComponent->addComponent(scoreComponent);
	//qBertComponent->addComponent(subjectComponent);
	//scene.Add(qBertComponent);

	std::shared_ptr<QBertObserver> pPlayerObserver = std::make_shared<QBertObserver>();
	std::shared_ptr<PlayerIndexComponent> playerIndexComponent = std::make_shared<PlayerIndexComponent>(playerIndex);
	auto scoreDisplay = std::make_shared <dae::GameObject>();
	auto livesDisplay = std::make_shared<TextComponent>("Score: 0", font);
	auto healthDisplay = std::make_shared<TextComponent>("Health: 3", font);
	livesDisplay->SetPosition(200, 0);
	healthDisplay->SetPosition(200, 100);
	//livesDisplay->SetText("Score: 0");

	scoreDisplay->addComponent(livesDisplay);
	scoreDisplay->addComponent(healthDisplay);
	currentScene.Add(scoreDisplay);

	pPlayerObserver->SetScoreComp(livesDisplay);
	pPlayerObserver->SetHealthComp(healthDisplay);
	std::shared_ptr<SubjectComponent> subjectComponent = std::make_shared<SubjectComponent>();
	subjectComponent->addObserver(pPlayerObserver);
	std::shared_ptr<ScoreComponent> scoreComponent = std::make_shared<ScoreComponent>();
	std::shared_ptr<HealthComponent> healtComponent = std::make_shared<HealthComponent>();

	std::shared_ptr<TextureComponent> componentTextureQBert{ std::make_shared<TextureComponent>() };
	componentTextureQBert->SetTexture("QBert.png");
	componentTextureQBert->SetPosition(m_PlayingField->GetPlayerFieldDataLast().MiddlePosX, m_PlayingField->GetPlayerFieldDataLast().MiddlePosY);
	std::shared_ptr<QBertComponent> componentQbertData{ std::make_shared<QBertComponent>(0.5f,componentTextureQBert) };
	m_pQBerts.push_back(componentQbertData);
	qBert->addComponent(componentTextureQBert);
	componentQbertData->SetFieldData(QBertFieldData);
	qBert->addComponent(componentQbertData);
	qBert->addComponent(scoreComponent);
	qBert->addComponent(subjectComponent);
	qBert->addComponent(playerIndexComponent);
	qBert->addComponent(healtComponent);
	currentScene.Add(qBert);

	auto& input = dae::InputManager::GetInstance();

	MoveLeftDownCommand* moveLeft = new MoveLeftDownCommand(qBert, m_PlayingField, "../Data/BackGroundTileYellow.png");
	MoveRightDownCommand* moveRight = new MoveRightDownCommand(qBert, m_PlayingField, "../Data/BackGroundTileYellow.png");
	MoveLeftUpCommand* moveLeftUp = new MoveLeftUpCommand(qBert, m_PlayingField, "../Data/BackGroundTileYellow.png");
	MoveRightUpCommand* moveRightUp = new MoveRightUpCommand(qBert, m_PlayingField, "../Data/BackGroundTileYellow.png");

	input.AddCommand(ControllerButton::LeftDpad, KeyBoardAndMouseButton::ButtonA, WayKeyBoardButton::buttonDown, moveLeft);
	input.AddCommand(ControllerButton::DownDpad, KeyBoardAndMouseButton::ButtonD, WayKeyBoardButton::buttonDown, moveRight);
	input.AddCommand(ControllerButton::UpDpad, KeyBoardAndMouseButton::ButtonQ, WayKeyBoardButton::buttonDown, moveLeftUp);
	input.AddCommand(ControllerButton::RightDpad, KeyBoardAndMouseButton::ButtonE, WayKeyBoardButton::buttonDown, moveRightUp);

	auto coily = std::make_shared<dae::GameObject>();
	FieldDataPlayer CoilyFieldData;
	CoilyFieldData.Row = m_PlayingField->GetPlayerFieldDataFirst().Row;
	CoilyFieldData.Column = m_PlayingField->GetPlayerFieldDataFirst().Column;

	std::shared_ptr<TextureComponent> componentTextureCoily{ std::make_shared<TextureComponent>() };
	componentTextureCoily->SetTexture("CoilyEgg.png");
	componentTextureCoily->SetPosition(m_PlayingField->GetPlayerFieldDataFirst().MiddlePosX, m_PlayingField->GetPlayerFieldDataFirst().MiddlePosY);
	std::shared_ptr<Coily> componentCoilyData{ std::make_shared<Coily>(coily ,m_PlayingField,m_pQBerts,1.0f,componentTextureCoily) };
	coily->addComponent(componentTextureCoily);
	componentCoilyData->SetFieldData(CoilyFieldData);
	coily->addComponent(componentCoilyData);
	currentScene.Add(coily);
	coily->SetIsActive(true);
	m_pEnemies.push_back(componentCoilyData);


	LoadMenus(currentScene);
}

void Level::LoadGameVs(dae::Scene& currentScene)
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//qBert->SetIsActive(false);
	LoadGame(currentScene,font);
	auto qBert = std::make_shared<dae::GameObject>();
	FieldDataPlayer QBertFieldData;
	QBertFieldData.Row = m_PlayingField->GetPlayerFieldDataLast().Row;
	QBertFieldData.Column = m_PlayingField->GetPlayerFieldDataLast().Column;

	int playerIndex{ 0 };

	//std::shared_ptr<GameObject> qBertComponent = std::make_shared<GameObject>();
	//qBertComponent->addComponent(scoreComponent);
	//qBertComponent->addComponent(subjectComponent);
	//scene.Add(qBertComponent);

	std::shared_ptr<QBertObserver> pPlayerObserver = std::make_shared<QBertObserver>();
	std::shared_ptr<PlayerIndexComponent> playerIndexComponent = std::make_shared<PlayerIndexComponent>(playerIndex);
	auto scoreDisplay = std::make_shared <dae::GameObject>();
	auto livesDisplay = std::make_shared<TextComponent>("Score: 0", font);
	auto healthDisplay = std::make_shared<TextComponent>("Health: 3", font);
	livesDisplay->SetPosition(200, 0);
	healthDisplay->SetPosition(200, 100);
	//livesDisplay->SetText("Score: 0");

	scoreDisplay->addComponent(livesDisplay);
	scoreDisplay->addComponent(healthDisplay);
	currentScene.Add(scoreDisplay);

	pPlayerObserver->SetScoreComp(livesDisplay);
	pPlayerObserver->SetHealthComp(healthDisplay);
	std::shared_ptr<SubjectComponent> subjectComponent = std::make_shared<SubjectComponent>();
	subjectComponent->addObserver(pPlayerObserver);
	std::shared_ptr<ScoreComponent> scoreComponent = std::make_shared<ScoreComponent>();
	std::shared_ptr<HealthComponent> healtComponent = std::make_shared<HealthComponent>();

	std::shared_ptr<TextureComponent> componentTextureQBert{ std::make_shared<TextureComponent>() };
	componentTextureQBert->SetTexture("QBert.png");
	componentTextureQBert->SetPosition(m_PlayingField->GetPlayerFieldDataLast().MiddlePosX, m_PlayingField->GetPlayerFieldDataLast().MiddlePosY);
	std::shared_ptr<QBertComponent> componentQbertData{ std::make_shared<QBertComponent>(0.5f,componentTextureQBert) };
	m_pQBerts.push_back(componentQbertData);
	qBert->addComponent(componentTextureQBert);
	componentQbertData->SetFieldData(QBertFieldData);
	qBert->addComponent(componentQbertData);
	qBert->addComponent(scoreComponent);
	qBert->addComponent(subjectComponent);
	qBert->addComponent(playerIndexComponent);
	qBert->addComponent(healtComponent);
	currentScene.Add(qBert);

	auto& input = dae::InputManager::GetInstance();

	MoveLeftDownCommand* moveLeft = new MoveLeftDownCommand(qBert, m_PlayingField, "../Data/BackGroundTileYellow.png");
	MoveRightDownCommand* moveRight = new MoveRightDownCommand(qBert, m_PlayingField, "../Data/BackGroundTileYellow.png");
	MoveLeftUpCommand* moveLeftUp = new MoveLeftUpCommand(qBert, m_PlayingField, "../Data/BackGroundTileYellow.png");
	MoveRightUpCommand* moveRightUp = new MoveRightUpCommand(qBert, m_PlayingField, "../Data/BackGroundTileYellow.png");

	input.AddCommand(ControllerButton::LeftDpad, KeyBoardAndMouseButton::ButtonA, WayKeyBoardButton::buttonDown, moveLeft);
	input.AddCommand(ControllerButton::DownDpad, KeyBoardAndMouseButton::ButtonD, WayKeyBoardButton::buttonDown, moveRight);
	input.AddCommand(ControllerButton::UpDpad, KeyBoardAndMouseButton::ButtonQ, WayKeyBoardButton::buttonDown, moveLeftUp);
	input.AddCommand(ControllerButton::RightDpad, KeyBoardAndMouseButton::ButtonE, WayKeyBoardButton::buttonDown, moveRightUp);

	auto coily = std::make_shared<dae::GameObject>();
	FieldDataPlayer CoilyFieldData;
	CoilyFieldData.Row = m_PlayingField->GetPlayerFieldDataFirst().Row;
	CoilyFieldData.Column = m_PlayingField->GetPlayerFieldDataFirst().Column;

	std::shared_ptr<TextureComponent> componentTextureCoily{ std::make_shared<TextureComponent>() };
	componentTextureCoily->SetTexture("CoilyEgg.png");
	componentTextureCoily->SetPosition(m_PlayingField->GetPlayerFieldDataFirst().MiddlePosX, m_PlayingField->GetPlayerFieldDataFirst().MiddlePosY);
	std::shared_ptr<Coily> componentCoilyData{ std::make_shared<Coily>(coily ,m_PlayingField,m_pQBerts,0.6f,componentTextureCoily) };
	coily->addComponent(componentTextureCoily);
	componentCoilyData->SetFieldData(CoilyFieldData);
	coily->addComponent(componentCoilyData);
	currentScene.Add(coily);
	//coily->SetIsActive(true);
	m_pEnemies.push_back(componentCoilyData);

	MoveLeftDownCommand* moveLeft2 = new MoveLeftDownCommand(coily, m_PlayingField, "../Data/BackGroundTileRed.png");
	MoveRightDownCommand* moveRight2 = new MoveRightDownCommand(coily, m_PlayingField, "../Data/BackGroundTileRed.png");
	MoveLeftUpCommand* moveLeftUp2 = new MoveLeftUpCommand(coily, m_PlayingField, "../Data/BackGroundTileRed.png");
	MoveRightUpCommand* moveRightUp2 = new MoveRightUpCommand(coily, m_PlayingField, "../Data/BackGroundTileRed.png");

	input.AddCommand(ControllerButton::ButtonX, KeyBoardAndMouseButton::ButtonArrowLeft, WayKeyBoardButton::buttonDown, moveLeft2);
	input.AddCommand(ControllerButton::ButtonA, KeyBoardAndMouseButton::ButtonArrowDown, WayKeyBoardButton::buttonDown, moveRight2);
	input.AddCommand(ControllerButton::ButtonY, KeyBoardAndMouseButton::ButtonArrowUp, WayKeyBoardButton::buttonDown, moveLeftUp2);
	input.AddCommand(ControllerButton::ButtonB, KeyBoardAndMouseButton::ButtonArrowRight, WayKeyBoardButton::buttonDown, moveRightUp2);
	LoadMenus(currentScene);
}

void Level::LoadGameCoop(dae::Scene& currentScene)
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//qBert->SetIsActive(false);
	LoadGame(currentScene, font);
	auto qBert = std::make_shared<dae::GameObject>();
	FieldDataPlayer QBertFieldData;
	QBertFieldData.Row = m_PlayingField->GetFieldDataLeftBottom().Row;
	QBertFieldData.Column = m_PlayingField->GetFieldDataLeftBottom().Column;

	int playerIndex{ 0 };

	std::shared_ptr<QBertObserver> pPlayerObserver = std::make_shared<QBertObserver>();
	std::shared_ptr<PlayerIndexComponent> playerIndexComponent = std::make_shared<PlayerIndexComponent>(playerIndex);
	auto scoreDisplay = std::make_shared <dae::GameObject>();
	auto livesDisplay = std::make_shared<TextComponent>("Score: 0", font);
	auto healthDisplay = std::make_shared<TextComponent>("Health: 3", font);
	livesDisplay->SetPosition(200, 0);
	healthDisplay->SetPosition(200, 100);
	scoreDisplay->addComponent(livesDisplay);
	scoreDisplay->addComponent(healthDisplay);
	currentScene.Add(scoreDisplay);

	pPlayerObserver->SetScoreComp(livesDisplay);
	pPlayerObserver->SetHealthComp(healthDisplay);
	std::shared_ptr<SubjectComponent> subjectComponent = std::make_shared<SubjectComponent>();
	subjectComponent->addObserver(pPlayerObserver);
	std::shared_ptr<ScoreComponent> scoreComponent = std::make_shared<ScoreComponent>();
	std::shared_ptr<HealthComponent> healtComponent = std::make_shared<HealthComponent>();

	std::shared_ptr<TextureComponent> componentTextureQBert{ std::make_shared<TextureComponent>() };
	componentTextureQBert->SetTexture("QBert.png");
	componentTextureQBert->SetPosition(m_PlayingField->GetFieldDataLeftBottom().MiddlePosX, m_PlayingField->GetFieldDataLeftBottom().MiddlePosY);
	std::shared_ptr<QBertComponent> componentQbertData{ std::make_shared<QBertComponent>(0.5f,componentTextureQBert) };
	m_pQBerts.push_back(componentQbertData);
	qBert->addComponent(componentTextureQBert);
	componentQbertData->SetFieldData(QBertFieldData);
	qBert->addComponent(componentQbertData);
	qBert->addComponent(scoreComponent);
	qBert->addComponent(subjectComponent);
	qBert->addComponent(playerIndexComponent);
	qBert->addComponent(healtComponent);
	currentScene.Add(qBert);

	auto& input = dae::InputManager::GetInstance();

	MoveLeftDownCommand* moveLeft = new MoveLeftDownCommand(qBert, m_PlayingField, "../Data/BackGroundTileYellow.png");
	MoveRightDownCommand* moveRight = new MoveRightDownCommand(qBert, m_PlayingField, "../Data/BackGroundTileYellow.png");
	MoveLeftUpCommand* moveLeftUp = new MoveLeftUpCommand(qBert, m_PlayingField, "../Data/BackGroundTileYellow.png");
	MoveRightUpCommand* moveRightUp = new MoveRightUpCommand(qBert, m_PlayingField, "../Data/BackGroundTileYellow.png");

	input.AddCommand(ControllerButton::LeftDpad, KeyBoardAndMouseButton::ButtonA, WayKeyBoardButton::buttonDown, moveLeft);
	input.AddCommand(ControllerButton::DownDpad, KeyBoardAndMouseButton::ButtonD, WayKeyBoardButton::buttonDown, moveRight);
	input.AddCommand(ControllerButton::UpDpad, KeyBoardAndMouseButton::ButtonQ, WayKeyBoardButton::buttonDown, moveLeftUp);
	input.AddCommand(ControllerButton::RightDpad, KeyBoardAndMouseButton::ButtonE, WayKeyBoardButton::buttonDown, moveRightUp);

	auto qBert2 = std::make_shared<dae::GameObject>();
	FieldDataPlayer QBertFieldData2;
	QBertFieldData2.Row = m_PlayingField->GetPlayerFieldDataLast().Row;
	QBertFieldData2.Column = m_PlayingField->GetPlayerFieldDataLast().Column;

	 playerIndex = 1;

	std::shared_ptr<QBertObserver> pPlayerObserver2 = std::make_shared<QBertObserver>();
	std::shared_ptr<PlayerIndexComponent> playerIndexComponent2 = std::make_shared<PlayerIndexComponent>(playerIndex);
	auto scoreDisplay2 = std::make_shared <dae::GameObject>();
	auto livesDisplay2 = std::make_shared<TextComponent>("Score: 0", font);
	auto healthDisplay2 = std::make_shared<TextComponent>("Health: 3", font);
	livesDisplay2->SetPosition(400, 0);
	healthDisplay2->SetPosition(400, 100);
	scoreDisplay2->addComponent(livesDisplay2);
	scoreDisplay2->addComponent(healthDisplay2);
	currentScene.Add(scoreDisplay2);

	pPlayerObserver2->SetScoreComp(livesDisplay2);
	pPlayerObserver2->SetHealthComp(healthDisplay2);
	std::shared_ptr<SubjectComponent> subjectComponent2 = std::make_shared<SubjectComponent>();
	subjectComponent2->addObserver(pPlayerObserver2);
	std::shared_ptr<ScoreComponent> scoreComponent2 = std::make_shared<ScoreComponent>();
	std::shared_ptr<HealthComponent> healtComponent2 = std::make_shared<HealthComponent>();

	std::shared_ptr<TextureComponent> componentTextureQBert2{ std::make_shared<TextureComponent>() };
	componentTextureQBert2->SetTexture("QBert.png");
	componentTextureQBert2->SetPosition(m_PlayingField->GetPlayerFieldDataLast().MiddlePosX, m_PlayingField->GetPlayerFieldDataLast().MiddlePosY);
	std::shared_ptr<QBertComponent> componentQbertData2{ std::make_shared<QBertComponent>(0.5f,componentTextureQBert2) };
	m_pQBerts.push_back(componentQbertData2);
	qBert2->addComponent(componentTextureQBert2);
	componentQbertData2->SetFieldData(QBertFieldData2);
	qBert2->addComponent(componentQbertData2);
	qBert2->addComponent(scoreComponent2);
	qBert2->addComponent(subjectComponent2);
	qBert2->addComponent(playerIndexComponent2);
	qBert2->addComponent(healtComponent2);
	currentScene.Add(qBert2);

	MoveLeftDownCommand* moveLeft2 = new MoveLeftDownCommand(qBert2, m_PlayingField, "../Data/BackGroundTileRed.png");
	MoveRightDownCommand* moveRight2 = new MoveRightDownCommand(qBert2, m_PlayingField, "../Data/BackGroundTileRed.png");
	MoveLeftUpCommand* moveLeftUp2 = new MoveLeftUpCommand(qBert2, m_PlayingField, "../Data/BackGroundTileRed.png");
	MoveRightUpCommand* moveRightUp2 = new MoveRightUpCommand(qBert2, m_PlayingField, "../Data/BackGroundTileRed.png");

	input.AddCommand(ControllerButton::ButtonX, KeyBoardAndMouseButton::ButtonArrowLeft, WayKeyBoardButton::buttonDown, moveLeft2);
	input.AddCommand(ControllerButton::ButtonA, KeyBoardAndMouseButton::ButtonArrowDown, WayKeyBoardButton::buttonDown, moveRight2);
	input.AddCommand(ControllerButton::ButtonY, KeyBoardAndMouseButton::ButtonArrowUp, WayKeyBoardButton::buttonDown, moveLeftUp2);
	input.AddCommand(ControllerButton::ButtonB, KeyBoardAndMouseButton::ButtonArrowRight, WayKeyBoardButton::buttonDown, moveRightUp2);

	LoadMenus(currentScene);
}

void Level::LoadGame(dae::Scene& currentScene, std::shared_ptr<dae::Font> font)
{
	auto go = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> component{ std::make_shared<dae::TextureComponent>() };
	component->SetTexture("background.jpg");
	go->addComponent(component);

	auto playingField = std::make_shared<dae::GameObject>();
	std::shared_ptr<PlayingField> componentplayingField{ std::make_shared<PlayingField>(250.0f,200.0f,go) };
	playingField->addComponent(componentplayingField);
	currentScene.Add(playingField);

	m_PlayingField = componentplayingField;

	auto component2 = std::make_shared<TextComponent>("Programming 4 Exam Assignment", font);
	component2->SetPosition(80, 20);
	go->addComponent(component2);

	//auto component3 = std::make_shared<FPSComponent>();
	//go->addComponent(component3);
	currentScene.Add(go);

	//init player
	//auto& renderer = dae::Renderer::GetInstance();

	//ugg
	auto UggComponent = std::make_shared<dae::GameObject>();
	FieldDataPlayer UggFieldData;
	UggFieldData.Row = componentplayingField->GetPlayerFieldDataLast().Row;
	UggFieldData.Column = componentplayingField->GetPlayerFieldDataLast().Column;

	std::shared_ptr<TextureComponent> componentTextureUgg{ std::make_shared<TextureComponent>() };
	componentTextureUgg->SetTexture("EnemyUgg.png");
	componentTextureUgg->SetPosition(componentplayingField->GetPlayerFieldDataLast().MiddlePosX, componentplayingField->GetPlayerFieldDataLast().MiddlePosY);
	std::shared_ptr<UggAndWrongway> componentUggData{ std::make_shared<UggAndWrongway>(UggComponent ,componentplayingField,1.0f,componentTextureUgg) };
	UggComponent->addComponent(componentTextureUgg);
	componentUggData->SetFieldData(UggFieldData);
	UggComponent->addComponent(componentUggData);
	currentScene.Add(UggComponent);
	UggComponent->SetIsActive(false);
	m_pEnemies.push_back(componentUggData);

	//slick/sam
	auto SlickGameObject = std::make_shared<dae::GameObject>();
	FieldDataPlayer SlickFieldData;
	SlickFieldData.Row = componentplayingField->GetPlayerFieldDataFirst().Row;
	SlickFieldData.Column = componentplayingField->GetPlayerFieldDataFirst().Column;

	std::shared_ptr<TextureComponent> componentTextureSlick{ std::make_shared<TextureComponent>() };
	componentTextureSlick->SetTexture("SamOrSlick.png");
	componentTextureSlick->SetPosition(componentplayingField->GetPlayerFieldDataFirst().MiddlePosX, componentplayingField->GetPlayerFieldDataFirst().MiddlePosY);
	std::shared_ptr<SlickAndSam> componentSlickData{ std::make_shared<SlickAndSam>(SlickGameObject ,componentplayingField,1.0f,componentTextureSlick) };
	SlickGameObject->addComponent(componentTextureSlick);
	componentSlickData->SetFieldData(SlickFieldData);
	SlickGameObject->addComponent(componentSlickData);
	currentScene.Add(SlickGameObject);
	SlickGameObject->SetIsActive(false);
	m_pEnemies.push_back(componentSlickData);

	//playerIndex++;
	//std::shared_ptr<GameObject> qBert2 = std::make_shared<GameObject>();
	//std::shared_ptr<HealthComponent> healtComponent2 = std::make_shared<HealthComponent>();
	//std::shared_ptr<SubjectComponent> subjectComponent2 = std::make_shared<SubjectComponent>();
	//std::shared_ptr<ScoreComponent> scoreComponent2 = std::make_shared<ScoreComponent>();
	//std::shared_ptr<PlayerIndexComponent> playerIndexComponent2 = std::make_shared<PlayerIndexComponent>(playerIndex);
	//subjectComponent2->addObserver(pPlayerObserver);
	//qBert2->addComponent(healtComponent2);
	//qBert2->addComponent(scoreComponent2);
	//qBert2->addComponent(subjectComponent2);
	//qBert2->addComponent(playerIndexComponent2);
	//scene.Add(qBert2);

	//renderer.InitPlayer(playerIndexComponent2->GetIndexPlayer(), healtComponent2->GetRemainingLives(), scoreComponent2->GetScore());


	//PlaySoundCommand* playSound = new PlaySoundCommand(qBert, "../Data/road.wav");
	//MuteCommand* muteSound = new MuteCommand(qBert);
	//Kill* kill = new Kill(qBert);
	//ColorChange* colorChange = new ColorChange(qBert);
	//CoilyDefeated* defeatedCoily = new CoilyDefeated(qBert);
	//CatchingSlickOrSam* caughtSlickOrSam = new CatchingSlickOrSam(qBert);
	//RemainingDisks* remainingDisks = new RemainingDisks(qBert);

	//Kill* kill2 = new Kill(qBert2);
	//ColorChange* colorChange2 = new ColorChange(qBert2);
	//CoilyDefeated* defeatedCoily2 = new CoilyDefeated(qBert2);
	//CatchingSlickOrSam* caughtSlickOrSam2 = new CatchingSlickOrSam(qBert2);
	//RemainingDisks* remainingDisks2 = new RemainingDisks(qBert2);
//	//ChangeTextureCommand* changeTexture = new ChangeTextureCommand(go, component, "../Data/logo.png");


	//input.AddCommand(ControllerButton::RightBump,KeyBoardAndMouseButton::MouseButtonRight, WayKeyBoardButton::MouseButtonUp,playSound);
	//input.AddCommand(ControllerButton::LeftBump, KeyBoardAndMouseButton::MouseButtonMiddle, WayKeyBoardButton::MouseButtonDown, muteSound);
	//input.AddCommand(ControllerButton::ButtonA, KeyBoardAndMouseButton::ButtonS, WayKeyBoardButton::buttonUp, kill);
	//input.AddCommand(ControllerButton::ButtonB, KeyBoardAndMouseButton::ButtonD, WayKeyBoardButton::buttonUp, colorChange);
	//input.AddCommand(ControllerButton::ButtonX, KeyBoardAndMouseButton::ButtonA, WayKeyBoardButton::buttonUp, defeatedCoily);
	//input.AddCommand(ControllerButton::ButtonY, KeyBoardAndMouseButton::ButtonW, WayKeyBoardButton::buttonUp, caughtSlickOrSam);
	//input.AddCommand(ControllerButton::Start, KeyBoardAndMouseButton::ButtonE, WayKeyBoardButton::buttonUp, remainingDisks);
	//input.AddCommand(ControllerButton::DownDpad, KeyBoardAndMouseButton::ButtonArrowDown, WayKeyBoardButton::buttonDown, kill2);
	//input.AddCommand(ControllerButton::LeftDpad, KeyBoardAndMouseButton::ButtonArrowLeft, WayKeyBoardButton::buttonDown, colorChange2);
	//input.AddCommand(ControllerButton::RightDpad, KeyBoardAndMouseButton::ButtonArrowRight, WayKeyBoardButton::buttonDown, defeatedCoily2);
	//input.AddCommand(ControllerButton::UpDpad, KeyBoardAndMouseButton::ButtonArrowUp, WayKeyBoardButton::buttonDown, caughtSlickOrSam2);
	//input.AddCommand(ControllerButton::Back, KeyBoardAndMouseButton::Button0, WayKeyBoardButton::buttonDown, remainingDisks2);
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

void Level::LoadMenus(dae::Scene& currentScene)
{
	auto& input = dae::InputManager::GetInstance();

	auto pauseScreen = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> pauseScreenComp = { std::make_shared<dae::TextureComponent>("PauseScreen.png") };
	pauseScreenComp->SetPosition(150, 100);
	pauseScreen->addComponent(pauseScreenComp);
	currentScene.Add(pauseScreen);

	auto deathScreen = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> deathScreenComp = { std::make_shared<dae::TextureComponent>("DeadScreen.png") };
	deathScreenComp->SetPosition(150, 100);
	deathScreen->addComponent(deathScreenComp);
	currentScene.Add(deathScreen);

	auto playButton = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> playButtonComp = { std::make_shared<dae::TextureComponent>("Solo.png") };
	playButtonComp->SetPosition(250, 200);
	playButton->addComponent(playButtonComp);
	currentScene.Add(playButton);

	auto exitButton = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> exitButtonComp = { std::make_shared<dae::TextureComponent>("Vs.png") };
	exitButtonComp->SetPosition(250, 250);
	exitButton->addComponent(exitButtonComp);
	currentScene.Add(exitButton);


	auto menu = std::make_shared<dae::GameObject>();
	m_pMenusComp = { std::make_shared<Menus>(playButtonComp,exitButtonComp,pauseScreenComp,deathScreenComp) };
	menu->addComponent(m_pMenusComp);
	currentScene.Add(menu);
	m_pMenusComp->SetPauseScreenInActive();
	menu->SetIsActive(false);

	PauseMenuCommand* pauseMenu = new PauseMenuCommand(m_pMenusComp);
	MouseClickGameMenus* mouseClick = new MouseClickGameMenus(m_pMenusComp->GetInWhatButtonGameMenu(), m_pMenusComp);

	//	qBertComponent
	input.AddCommand(ControllerButton::Start, KeyBoardAndMouseButton::ButtonW, WayKeyBoardButton::buttonDown, pauseMenu);
	input.AddCommand(dae::ControllerButton::None, dae::KeyBoardAndMouseButton::MouseButtonLeft, dae::WayKeyBoardButton::MouseButtonDown, mouseClick);

}

void Level::Update()
{

	m_CurrentRespawnTimer += GameTime::GetInstance().GetDeltaTime();

	if (m_PlayingField->GetLevelIsResetted())
	{
		for (size_t i = 0; i < m_pEnemies.size(); ++i)
		{
			m_pEnemies[i]->GetGameObject()->SetIsActive(false);
		}
		m_CurrentRespawnTimer = 0.0f;
		for (size_t i = 0; i < m_pQBerts.size(); ++i)
		{
			auto fieldData = m_pQBerts[i]->GetFieldDataPlayer();

			m_pQBerts[i]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_PlayingField->GetPlayerFieldDataFirst().MiddlePosX, m_PlayingField->GetPlayerFieldDataFirst().MiddlePosY);
			fieldData.Column = m_PlayingField->GetPlayerFieldDataFirst().Column;
			fieldData.Row = m_PlayingField->GetPlayerFieldDataFirst().Row;
			m_pQBerts[i]->SetThatHeIsAllowedtoMove(false);
			m_pQBerts[i]->SetFieldData(fieldData);
			m_pQBerts[i]->ResetCurrentTime();
			m_pQBerts[i]->GetGameObject()->GetComponent<dae::ScoreComponent>()->AddScore(m_PlayingField->GetColorWheelsRemaining() * 50);
		}
		m_PlayingField->SetLevelIsResetted(false);
		m_PlayingField->ResetColorWheelsRemaining();
	}

	//if (m_CurrentRespawnTimer > m_MaxRespawnTimer)
	//{
	//	int whatCharacter = rand() % 2;
	//	std::cout << "character: " << whatCharacter << std::endl;
	//	auto fieldData = m_pEnemies[whatCharacter]->GetFieldDataPlayer();
	//	if (m_pEnemies[whatCharacter]->GetGameObject()->GetIsActive())
	//	{
	//		for (size_t i = 0; i < m_pEnemies.size(); ++i)
	//		{
	//			if (!m_pEnemies[i]->GetGameObject()->GetIsActive())
	//			{
	//				whatCharacter = i;
	//				break;
	//			}
	//		}
	//	}
	//	m_pEnemies[whatCharacter]->GetGameObject()->SetIsActive(true);

	//	if (m_pEnemies[whatCharacter]->GetGameObject()->HasComponent<SlickAndSam>())
	//	{
	//		m_pEnemies[whatCharacter]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_PlayingField->GetPlayerFieldDataFirst().MiddlePosX, m_PlayingField->GetPlayerFieldDataFirst().MiddlePosY);
	//		fieldData.Column = m_PlayingField->GetPlayerFieldDataFirst().Column;
	//		fieldData.Row = m_PlayingField->GetPlayerFieldDataFirst().Row;
	//		m_pEnemies[whatCharacter]->SetFieldData(fieldData);
	//		m_pEnemies[whatCharacter]->ResetCurrentTime();
	//	}
	//	else if (m_pEnemies[whatCharacter]->GetGameObject()->HasComponent<UggAndWrongway>())
	//	{
	//		//respawn logic
	//		int whatMovement = rand() % 2;
	//		switch (whatMovement)
	//		{
	//		case 0:
	//			//move left
	//			m_pEnemies[whatCharacter]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_PlayingField->GetFieldDataLeftBottom().MiddlePosX, m_PlayingField->GetFieldDataLeftBottom().MiddlePosY);
	//			fieldData.Column = m_PlayingField->GetFieldDataLeftBottom().Column;
	//			fieldData.Row = m_PlayingField->GetFieldDataLeftBottom().Row;
	//			m_pEnemies[whatCharacter]->SetFieldData(fieldData);
	//			m_pEnemies[whatCharacter]->ResetCurrentTime();
	//			break;
	//		case 1:
	//			//move right
	//			m_pEnemies[whatCharacter]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_PlayingField->GetPlayerFieldDataLast().MiddlePosX, m_PlayingField->GetPlayerFieldDataLast().MiddlePosY);
	//			fieldData.Column = m_PlayingField->GetPlayerFieldDataLast().Column;
	//			fieldData.Row = m_PlayingField->GetPlayerFieldDataLast().Row;
	//			m_pEnemies[whatCharacter]->SetFieldData(fieldData);
	//			m_pEnemies[whatCharacter]->ResetCurrentTime();
	//			break;
	//		default:
	//			//nothing
	//			break;
	//		}
	//	}

	//	m_CurrentRespawnTimer = 0.0f;
	//	//random time logic

	//}
	for (size_t i = 0; i < m_pEnemies.size(); ++i)
	{
		if (m_pEnemies[i]->GetGameObject()->HasComponent<Coily>())
		{
			if (m_pEnemies[i]->GetGameObject()->GetComponent<Coily>()->GetIsDead() && 
				!m_pEnemies[i]->GetGameObject()->GetComponent<ControlComponent>()->GetIsAllowedtoMove())
			{
				m_pEnemies[i]->GetGameObject()->GetComponent<Coily>()->SetIsDead(false);
				m_pEnemies[i]->GetGameObject()->SetIsActive(false);
				m_pQBerts[0]->GetGameObject()->GetComponent<dae::ScoreComponent>()->AddScore(500);
			}
		}

		for (size_t j = 0; j < m_pQBerts.size(); ++j)
		{
			if (m_pEnemies[i]->GetFieldDataPlayer().Row == m_pQBerts[j]->GetFieldDataPlayer().Row && m_pEnemies[i]->GetFieldDataPlayer().Column == m_pQBerts[j]->GetFieldDataPlayer().Column)
			{
				if (m_pEnemies[i]->GetGameObject()->GetIsActive())
				{
					if (m_pEnemies[i]->GetGameObject()->HasComponent<SlickAndSam>())
					{
						m_pQBerts[j]->GetGameObject()->GetComponent<dae::ScoreComponent>()->AddScore(300);

						m_pEnemies[i]->GetGameObject()->SetIsActive(false);
					}
					else
					{
						//reset player pos/delete enemy
						std::cout << "player hit";
						//0getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
						m_pQBerts[j]->GetGameObject()->GetComponent<dae::HealthComponent>()->LoseLive();
						//m_pQBert->GetGameObject()->SetPosition(m_PlayingField->GetPlayerFieldDataFirst().MiddlePosX, m_PlayingField->GetPlayerFieldDataFirst().MiddlePosY);
						//m_pQBert->SetFieldData(FieldDataPlayer{ m_PlayingField->GetPlayerFieldDataFirst().Row, m_PlayingField->GetPlayerFieldDataFirst().Column});
						auto fieldData = m_pQBerts[j]->GetFieldDataPlayer();

						m_pQBerts[j]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_PlayingField->GetPlayerFieldDataFirst().MiddlePosX, m_PlayingField->GetPlayerFieldDataFirst().MiddlePosY);
						fieldData.Column = m_PlayingField->GetPlayerFieldDataFirst().Column;
						fieldData.Row = m_PlayingField->GetPlayerFieldDataFirst().Row;
						m_pQBerts[j]->SetFieldData(fieldData);
						m_pQBerts[j]->ResetCurrentTime();
						m_pEnemies[i]->GetGameObject()->SetIsActive(false);

						if (m_pQBerts[j]->GetGameObject()->GetComponent<dae::HealthComponent>()->GetRemainingLives() <= 0)
						{
							//you die
							m_pMenusComp->GetGameObject()->SetIsActive(true);
							m_pMenusComp->SetDeathScreenActive();
							GameTime::GetInstance().SetPaused(true);
						}
					}
				}
			}
		}
	}
}