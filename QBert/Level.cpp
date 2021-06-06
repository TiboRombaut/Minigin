#include "Level.h"
#include <TextureComponent.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include <ScoreComponent.h>
#include <InputManager.h>
#include <Renderer.h>
#include <TextComponent.h>
#include <FPSComponent.h>
#include <SubjectComponent.h>
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

Level::~Level()
{
	std::vector<dae::ButtonCommand> commandsToDelete = {};
	auto commands = dae::InputManager::GetInstance().GetCommands();
	for (size_t i = 0; i < commands.size(); ++i)
	{
		if (dynamic_cast<MouseClickMainMenuCommand*>(commands[i].pCommand) == nullptr)
		{
			commandsToDelete.push_back(commands[i]);
		}
	}
	dae::InputManager::GetInstance().DeleteCommands(commandsToDelete);
	dae::InputManager::GetInstance().GetCommands();
}

void Level::LoadGameSolo(dae::Scene& currentScene)
{
	auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	LoadGame(currentScene);
	auto pQBert = std::make_shared<dae::GameObject>();
	FieldDataPlayer QBertFieldData;
	QBertFieldData.Row = m_pPlayingField->GetFieldDataFirst().Row;
	QBertFieldData.Column = m_pPlayingField->GetFieldDataFirst().Column;

	std::shared_ptr<QBertObserver> pPlayerObserver = std::make_shared<QBertObserver>();
	auto pScoreDisplay = std::make_shared <dae::GameObject>();
	auto pLivesDisplay = std::make_shared<TextComponent>("Score: 0", pFont);
	auto pHealthDisplay = std::make_shared<TextComponent>("Health: 3", pFont);
	pLivesDisplay->SetPosition(10, 10);
	pHealthDisplay->SetPosition(480, 10);

	pScoreDisplay->addComponent(pLivesDisplay);
	pScoreDisplay->addComponent(pHealthDisplay);
	currentScene.Add(pScoreDisplay);

	pPlayerObserver->SetScoreComp(pLivesDisplay);
	pPlayerObserver->SetHealthComp(pHealthDisplay);
	std::shared_ptr<SubjectComponent> pSubjectComponent = std::make_shared<SubjectComponent>();
	pSubjectComponent->AddObserver(pPlayerObserver);
	std::shared_ptr<ScoreComponent> pScoreComponent = std::make_shared<ScoreComponent>();
	std::shared_ptr<HealthComponent> pHealtComponent = std::make_shared<HealthComponent>();

	std::shared_ptr<TextureComponent> pComponentTextureQBert{ std::make_shared<TextureComponent>() };
	pComponentTextureQBert->SetTexture("QBert.png");
	pComponentTextureQBert->SetPosition(m_pPlayingField->GetFieldDataFirst().MiddlePosX, m_pPlayingField->GetFieldDataFirst().MiddlePosY);
	std::shared_ptr<QBertComponent> pComponentQbertData{ std::make_shared<QBertComponent>(0.5f,pComponentTextureQBert) };
	m_pQBerts.push_back(pComponentQbertData);
	pQBert->addComponent(pComponentTextureQBert);
	pComponentQbertData->SetFieldData(QBertFieldData);
	pQBert->addComponent(pComponentQbertData);
	pQBert->addComponent(pScoreComponent);
	pQBert->addComponent(pSubjectComponent);
	pQBert->addComponent(pHealtComponent);
	currentScene.Add(pQBert);
	pComponentQbertData->SetRespawnPoint();

	auto& input = dae::InputManager::GetInstance();

	MoveLeftDownCommand* pMoveLeft = new MoveLeftDownCommand(pQBert, m_pPlayingField);
	MoveRightDownCommand* pMoveRight = new MoveRightDownCommand(pQBert, m_pPlayingField);
	MoveLeftUpCommand* pMoveLeftUp = new MoveLeftUpCommand(pQBert, m_pPlayingField);
	MoveRightUpCommand* pMoveRightUp = new MoveRightUpCommand(pQBert, m_pPlayingField);

	input.AddCommand(ControllerButton::LeftDpad, KeyBoardAndMouseButton::ButtonA, WayKeyBoardButton::buttonDown, pMoveLeft);
	input.AddCommand(ControllerButton::DownDpad, KeyBoardAndMouseButton::ButtonS, WayKeyBoardButton::buttonDown, pMoveRight);
	input.AddCommand(ControllerButton::UpDpad, KeyBoardAndMouseButton::ButtonW, WayKeyBoardButton::buttonDown, pMoveLeftUp);
	input.AddCommand(ControllerButton::RightDpad, KeyBoardAndMouseButton::ButtonD, WayKeyBoardButton::buttonDown, pMoveRightUp);

	auto pCoily = std::make_shared<dae::GameObject>();
	FieldDataPlayer CoilyFieldData;
	CoilyFieldData.Row = m_pPlayingField->GetFieldDataFirst().Row;
	CoilyFieldData.Column = m_pPlayingField->GetFieldDataFirst().Column;

	std::shared_ptr<TextureComponent> pComponentTextureCoily{ std::make_shared<TextureComponent>() };
	pComponentTextureCoily->SetTexture("CoilyEgg.png");
	pComponentTextureCoily->SetPosition(m_pPlayingField->GetFieldDataFirst().MiddlePosX, m_pPlayingField->GetFieldDataFirst().MiddlePosY);
	std::shared_ptr<Coily> pComponentCoilyData{ std::make_shared<Coily>(pCoily ,m_pPlayingField,m_pQBerts,1.0f,pComponentTextureCoily,false) };
	pCoily->addComponent(pComponentTextureCoily);
	pComponentCoilyData->SetFieldData(CoilyFieldData);
	pCoily->addComponent(pComponentCoilyData);
	currentScene.Add(pCoily);
	pCoily->SetIsActive(false);
	m_pEnemies.push_back(pComponentCoilyData);

	LoadMenus(currentScene);
}

void Level::LoadGameVs(dae::Scene& currentScene)
{
	auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	LoadGame(currentScene);
	auto pQBert = std::make_shared<dae::GameObject>();
	FieldDataPlayer QBertFieldData;
	QBertFieldData.Row = m_pPlayingField->GetFieldDataLast().Row;
	QBertFieldData.Column = m_pPlayingField->GetFieldDataLast().Column;

	std::shared_ptr<QBertObserver> pPlayerObserver = std::make_shared<QBertObserver>();
	auto pScoreDisplay = std::make_shared <dae::GameObject>();
	auto pLivesDisplay = std::make_shared<TextComponent>("Score: 0", pFont);
	auto pHealthDisplay = std::make_shared<TextComponent>("Health: 3", pFont);
	pLivesDisplay->SetPosition(10, 10);
	pHealthDisplay->SetPosition(480, 10);

	pScoreDisplay->addComponent(pLivesDisplay);
	pScoreDisplay->addComponent(pHealthDisplay);
	currentScene.Add(pScoreDisplay);

	pPlayerObserver->SetScoreComp(pLivesDisplay);
	pPlayerObserver->SetHealthComp(pHealthDisplay);
	std::shared_ptr<SubjectComponent> pSubjectComponent = std::make_shared<SubjectComponent>();
	pSubjectComponent->AddObserver(pPlayerObserver);
	std::shared_ptr<ScoreComponent> pScoreComponent = std::make_shared<ScoreComponent>();
	std::shared_ptr<HealthComponent> pHealtComponent = std::make_shared<HealthComponent>();

	std::shared_ptr<TextureComponent> pComponentTextureQBert{ std::make_shared<TextureComponent>() };
	pComponentTextureQBert->SetTexture("QBert.png");
	pComponentTextureQBert->SetPosition(m_pPlayingField->GetFieldDataLast().MiddlePosX, m_pPlayingField->GetFieldDataLast().MiddlePosY);
	std::shared_ptr<QBertComponent> pComponentQbertData{ std::make_shared<QBertComponent>(0.5f,pComponentTextureQBert) };
	m_pQBerts.push_back(pComponentQbertData);
	pQBert->addComponent(pComponentTextureQBert);
	pComponentQbertData->SetFieldData(QBertFieldData);
	pQBert->addComponent(pComponentQbertData);
	pQBert->addComponent(pScoreComponent);
	pQBert->addComponent(pSubjectComponent);
	pQBert->addComponent(pHealtComponent);
	currentScene.Add(pQBert);
	pComponentQbertData->SetRespawnPoint();

	auto& input = dae::InputManager::GetInstance();

	MoveLeftDownCommand* pMoveLeft = new MoveLeftDownCommand(pQBert, m_pPlayingField);
	MoveRightDownCommand* pMoveRight = new MoveRightDownCommand(pQBert, m_pPlayingField);
	MoveLeftUpCommand* pMoveLeftUp = new MoveLeftUpCommand(pQBert, m_pPlayingField);
	MoveRightUpCommand* pMoveRightUp = new MoveRightUpCommand(pQBert, m_pPlayingField);

	input.AddCommand(ControllerButton::LeftDpad, KeyBoardAndMouseButton::ButtonA, WayKeyBoardButton::buttonDown, pMoveLeft);
	input.AddCommand(ControllerButton::DownDpad, KeyBoardAndMouseButton::ButtonS, WayKeyBoardButton::buttonDown, pMoveRight);
	input.AddCommand(ControllerButton::UpDpad, KeyBoardAndMouseButton::ButtonW, WayKeyBoardButton::buttonDown, pMoveLeftUp);
	input.AddCommand(ControllerButton::RightDpad, KeyBoardAndMouseButton::ButtonD, WayKeyBoardButton::buttonDown, pMoveRightUp);

	auto pCoily = std::make_shared<dae::GameObject>();
	FieldDataPlayer CoilyFieldData;
	CoilyFieldData.Row = m_pPlayingField->GetFieldDataFirst().Row;
	CoilyFieldData.Column = m_pPlayingField->GetFieldDataFirst().Column;

	std::shared_ptr<TextureComponent> pComponentTextureCoily{ std::make_shared<TextureComponent>() };
	pComponentTextureCoily->SetTexture("CoilyEgg.png");
	pComponentTextureCoily->SetPosition(m_pPlayingField->GetFieldDataFirst().MiddlePosX, m_pPlayingField->GetFieldDataFirst().MiddlePosY);
	std::shared_ptr<Coily> pComponentCoilyData{ std::make_shared<Coily>(pCoily ,m_pPlayingField,m_pQBerts,1.0f,pComponentTextureCoily,true) };
	pCoily->addComponent(pComponentTextureCoily);
	pComponentCoilyData->SetFieldData(CoilyFieldData);
	pCoily->addComponent(pComponentCoilyData);
	currentScene.Add(pCoily);
	m_pEnemies.push_back(pComponentCoilyData);

	input.AddCommand(ControllerButton::ButtonX, KeyBoardAndMouseButton::ButtonArrowLeft, WayKeyBoardButton::buttonDown, pComponentCoilyData->GetCommandDownLeft());
	input.AddCommand(ControllerButton::ButtonA, KeyBoardAndMouseButton::ButtonArrowDown, WayKeyBoardButton::buttonDown, pComponentCoilyData->GetCommandDownRight());
	input.AddCommand(ControllerButton::ButtonY, KeyBoardAndMouseButton::ButtonArrowUp, WayKeyBoardButton::buttonDown, pComponentCoilyData->GetCommandUpLeft());
	input.AddCommand(ControllerButton::ButtonB, KeyBoardAndMouseButton::ButtonArrowRight, WayKeyBoardButton::buttonDown, pComponentCoilyData->GetCommandUpRight());
	LoadMenus(currentScene);
}

void Level::LoadGameCoop(dae::Scene& currentScene)
{
	auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	LoadGame(currentScene);
	auto pQBert = std::make_shared<dae::GameObject>();
	FieldDataPlayer QBertFieldData;
	QBertFieldData.Row = m_pPlayingField->GetFieldDataLeftBottom().Row;
	QBertFieldData.Column = m_pPlayingField->GetFieldDataLeftBottom().Column;

	std::shared_ptr<QBertObserver> pPlayerObserver = std::make_shared<QBertObserver>();
	auto pScoreDisplay = std::make_shared <dae::GameObject>();
	auto pLivesDisplay = std::make_shared<TextComponent>("Score: 0", pFont);
	auto pHealthDisplay = std::make_shared<TextComponent>("Health: 3", pFont);
	pLivesDisplay->SetPosition(10, 10);
	pHealthDisplay->SetPosition(480, 10);
	pScoreDisplay->addComponent(pLivesDisplay);
	pScoreDisplay->addComponent(pHealthDisplay);
	currentScene.Add(pScoreDisplay);

	pPlayerObserver->SetScoreComp(pLivesDisplay);
	pPlayerObserver->SetHealthComp(pHealthDisplay);
	std::shared_ptr<SubjectComponent> pSubjectComponent = std::make_shared<SubjectComponent>();
	pSubjectComponent->AddObserver(pPlayerObserver);
	std::shared_ptr<ScoreComponent> pScoreComponent = std::make_shared<ScoreComponent>();
	std::shared_ptr<HealthComponent> pHealtComponent = std::make_shared<HealthComponent>();

	std::shared_ptr<TextureComponent> pComponentTextureQBert{ std::make_shared<TextureComponent>() };
	pComponentTextureQBert->SetTexture("QBert.png");
	pComponentTextureQBert->SetPosition(m_pPlayingField->GetFieldDataLeftBottom().MiddlePosX, m_pPlayingField->GetFieldDataLeftBottom().MiddlePosY);
	std::shared_ptr<QBertComponent> pComponentQbertData{ std::make_shared<QBertComponent>(0.5f,pComponentTextureQBert) };
	m_pQBerts.push_back(pComponentQbertData);
	pQBert->addComponent(pComponentTextureQBert);
	pComponentQbertData->SetFieldData(QBertFieldData);
	pQBert->addComponent(pComponentQbertData);
	pQBert->addComponent(pScoreComponent);
	pQBert->addComponent(pSubjectComponent);
	pQBert->addComponent(pHealtComponent);
	currentScene.Add(pQBert);
	pComponentQbertData->SetRespawnPoint();

	auto& input = dae::InputManager::GetInstance();

	MoveLeftDownCommand* pMoveLeft = new MoveLeftDownCommand(pQBert, m_pPlayingField);
	MoveRightDownCommand* pMoveRight = new MoveRightDownCommand(pQBert, m_pPlayingField);
	MoveLeftUpCommand* pMoveLeftUp = new MoveLeftUpCommand(pQBert, m_pPlayingField);
	MoveRightUpCommand* pMoveRightUp = new MoveRightUpCommand(pQBert, m_pPlayingField);

	input.AddCommand(ControllerButton::LeftDpad, KeyBoardAndMouseButton::ButtonA, WayKeyBoardButton::buttonDown, pMoveLeft);
	input.AddCommand(ControllerButton::DownDpad, KeyBoardAndMouseButton::ButtonS, WayKeyBoardButton::buttonDown, pMoveRight);
	input.AddCommand(ControllerButton::UpDpad, KeyBoardAndMouseButton::ButtonW, WayKeyBoardButton::buttonDown, pMoveLeftUp);
	input.AddCommand(ControllerButton::RightDpad, KeyBoardAndMouseButton::ButtonD, WayKeyBoardButton::buttonDown, pMoveRightUp);

	auto pQBert2 = std::make_shared<dae::GameObject>();
	FieldDataPlayer QBertFieldData2;
	QBertFieldData2.Row = m_pPlayingField->GetFieldDataLast().Row;
	QBertFieldData2.Column = m_pPlayingField->GetFieldDataLast().Column;

	std::shared_ptr<SubjectComponent> pSubjectComponent2 = std::make_shared<SubjectComponent>();
	pSubjectComponent2->AddObserver(pPlayerObserver);

	std::shared_ptr<TextureComponent> pComponentTextureQBert2{ std::make_shared<TextureComponent>() };
	pComponentTextureQBert2->SetTexture("QBert.png");
	pComponentTextureQBert2->SetPosition(m_pPlayingField->GetFieldDataLast().MiddlePosX, m_pPlayingField->GetFieldDataLast().MiddlePosY);
	std::shared_ptr<QBertComponent> pComponentQbertData2{ std::make_shared<QBertComponent>(0.5f,pComponentTextureQBert2) };
	m_pQBerts.push_back(pComponentQbertData2);
	pQBert2->addComponent(pComponentTextureQBert2);
	pComponentQbertData2->SetFieldData(QBertFieldData2);
	pQBert2->addComponent(pComponentQbertData2);
	pQBert2->addComponent(pScoreComponent);
	pQBert2->addComponent(pSubjectComponent2);
	pQBert2->addComponent(pHealtComponent);
	currentScene.Add(pQBert2);
	pComponentQbertData2->SetRespawnPoint();

	MoveLeftDownCommand* pMoveLeft2 = new MoveLeftDownCommand(pQBert2, m_pPlayingField);
	MoveRightDownCommand* pMoveRight2 = new MoveRightDownCommand(pQBert2, m_pPlayingField);
	MoveLeftUpCommand* pMoveLeftUp2 = new MoveLeftUpCommand(pQBert2, m_pPlayingField);
	MoveRightUpCommand* pMoveRightUp2 = new MoveRightUpCommand(pQBert2, m_pPlayingField);

	input.AddCommand(ControllerButton::ButtonX, KeyBoardAndMouseButton::ButtonArrowLeft, WayKeyBoardButton::buttonDown, pMoveLeft2);
	input.AddCommand(ControllerButton::ButtonA, KeyBoardAndMouseButton::ButtonArrowDown, WayKeyBoardButton::buttonDown, pMoveRight2);
	input.AddCommand(ControllerButton::ButtonY, KeyBoardAndMouseButton::ButtonArrowUp, WayKeyBoardButton::buttonDown, pMoveLeftUp2);
	input.AddCommand(ControllerButton::ButtonB, KeyBoardAndMouseButton::ButtonArrowRight, WayKeyBoardButton::buttonDown, pMoveRightUp2);

	auto pCoily = std::make_shared<dae::GameObject>();
	FieldDataPlayer CoilyFieldData;
	CoilyFieldData.Row = m_pPlayingField->GetFieldDataFirst().Row;
	CoilyFieldData.Column = m_pPlayingField->GetFieldDataFirst().Column;

	std::shared_ptr<TextureComponent> pComponentTextureCoily{ std::make_shared<TextureComponent>() };
	pComponentTextureCoily->SetTexture("CoilyEgg.png");
	pComponentTextureCoily->SetPosition(m_pPlayingField->GetFieldDataFirst().MiddlePosX, m_pPlayingField->GetFieldDataFirst().MiddlePosY);
	std::shared_ptr<Coily> pComponentCoilyData{ std::make_shared<Coily>(pCoily ,m_pPlayingField,m_pQBerts,1.0f,pComponentTextureCoily,false) };
	pCoily->addComponent(pComponentTextureCoily);
	pComponentCoilyData->SetFieldData(CoilyFieldData);
	pCoily->addComponent(pComponentCoilyData);
	currentScene.Add(pCoily);
	pCoily->SetIsActive(false);
	m_pEnemies.push_back(pComponentCoilyData);

	LoadMenus(currentScene);
}

void Level::LoadGame(dae::Scene& currentScene)
{
	auto pFont2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto pBackground = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> pBackgroundComp{ std::make_shared<dae::TextureComponent>() };
	pBackgroundComp->SetTexture("background.jpg");
	pBackground->addComponent(pBackgroundComp);

	auto pTextGoalComp = std::make_shared<TextComponent>("Goal: ", pFont2);
	pTextGoalComp->SetPosition(10, 60);
	pBackground->addComponent(pTextGoalComp);
	currentScene.Add(pBackground);

	auto pGoalTexture = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> pGoalTextureComp{ std::make_shared<dae::TextureComponent>() };
	pGoalTextureComp->SetTexture("BackGroundTileYellow.png");
	pGoalTextureComp->SetPosition(100, 50);
	pGoalTexture->addComponent(pGoalTextureComp);
	currentScene.Add(pGoalTexture);

	auto pPlayingField = std::make_shared<dae::GameObject>();
	std::shared_ptr<PlayingField> pComponentplayingField{ std::make_shared<PlayingField>(pBackground,pGoalTextureComp) };
	pPlayingField->addComponent(pComponentplayingField);
	currentScene.Add(pPlayingField);

	m_pPlayingField = pComponentplayingField;

	//ugg
	auto pUgg = std::make_shared<dae::GameObject>();
	FieldDataPlayer UggFieldData;
	UggFieldData.Row = pComponentplayingField->GetFieldDataLast().Row;
	UggFieldData.Column = pComponentplayingField->GetFieldDataLast().Column;

	std::shared_ptr<TextureComponent> pUggTextureComp{ std::make_shared<TextureComponent>() };
	pUggTextureComp->SetTexture("EnemyUgg.png");
	pUggTextureComp->SetPosition(pComponentplayingField->GetFieldDataLast().MiddlePosX, pComponentplayingField->GetFieldDataLast().MiddlePosY);
	std::shared_ptr<UggAndWrongway> pUggDataComp{ std::make_shared<UggAndWrongway>(pUgg ,pComponentplayingField,1.0f,pUggTextureComp) };
	pUgg->addComponent(pUggTextureComp);
	pUggDataComp->SetFieldData(UggFieldData);
	pUgg->addComponent(pUggDataComp);
	currentScene.Add(pUgg);
	pUgg->SetIsActive(false);
	m_pEnemies.push_back(pUggDataComp);

	//slick/sam
	auto pSlick = std::make_shared<dae::GameObject>();
	FieldDataPlayer SlickFieldData;
	SlickFieldData.Row = pComponentplayingField->GetFieldDataFirst().Row;
	SlickFieldData.Column = pComponentplayingField->GetFieldDataFirst().Column;

	std::shared_ptr<TextureComponent> pSlickTextureComp{ std::make_shared<TextureComponent>() };
	pSlickTextureComp->SetTexture("SamOrSlick.png");
	pSlickTextureComp->SetPosition(pComponentplayingField->GetFieldDataFirst().MiddlePosX, pComponentplayingField->GetFieldDataFirst().MiddlePosY);
	std::shared_ptr<SlickAndSam> pSlickDataComp{ std::make_shared<SlickAndSam>(pSlick ,pComponentplayingField,1.0f,pSlickTextureComp) };
	pSlick->addComponent(pSlickTextureComp);
	pSlickDataComp->SetFieldData(SlickFieldData);
	pSlick->addComponent(pSlickDataComp);
	currentScene.Add(pSlick);
	pSlick->SetIsActive(false);
	m_pEnemies.push_back(pSlickDataComp);

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

	auto pPauseScreen = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> pPauseScreenComp = { std::make_shared<dae::TextureComponent>("PauseScreen.png") };
	pPauseScreenComp->SetPosition(195, 100);
	pPauseScreen->addComponent(pPauseScreenComp);
	currentScene.Add(pPauseScreen);

	auto pDeathScreen = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> pDeathScreenComp = { std::make_shared<dae::TextureComponent>("DeadScreen.png") };
	pDeathScreenComp->SetPosition(195, 100);
	pDeathScreen->addComponent(pDeathScreenComp);
	currentScene.Add(pDeathScreen);

	auto pPlayButton = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> pPlayButtonComp = { std::make_shared<dae::TextureComponent>("Resume.png") };
	pPlayButtonComp->SetPosition(250, 200);
	pPlayButton->addComponent(pPlayButtonComp);
	currentScene.Add(pPlayButton);
	auto pFontFinalScoreText = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);

	auto pFinalScoreText = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextComponent> pFinalScoreTextComp = { std::make_shared<dae::TextComponent>("Score: 0",pFontFinalScoreText) };
	pFinalScoreTextComp->SetPosition(225, 210);
	pFinalScoreText->addComponent(pFinalScoreTextComp);
	currentScene.Add(pFinalScoreText);
	pFinalScoreText->SetIsActive(false);

	auto pMainMenuButton = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> pMainMenuButtonComp = { std::make_shared<dae::TextureComponent>("MainMenu.png") };
	pMainMenuButtonComp->SetPosition(250, 250);
	pMainMenuButton->addComponent(pMainMenuButtonComp);
	currentScene.Add(pMainMenuButton);

	auto pRestartButton = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> pRestartButtonComp = { std::make_shared<dae::TextureComponent>("Restart.png") };
	pRestartButtonComp->SetPosition(250, 300);
	pRestartButton->addComponent(pRestartButtonComp);
	currentScene.Add(pRestartButton);

	auto pExitButton = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> pExitButtonComp = { std::make_shared<dae::TextureComponent>("Exit.png") };
	pExitButtonComp->SetPosition(250, 350);
	pExitButton->addComponent(pExitButtonComp);
	currentScene.Add(pExitButton);


	auto pMenu = std::make_shared<dae::GameObject>();
	m_pMenusComp = { std::make_shared<Menus>(pPlayButtonComp,pExitButtonComp,pRestartButtonComp,pMainMenuButtonComp,pPauseScreenComp,pDeathScreenComp,pFinalScoreTextComp) };
	pMenu->addComponent(m_pMenusComp);
	currentScene.Add(pMenu);
	m_pMenusComp->SetPauseScreenInActive();
	pMenu->SetIsActive(false);

	PauseMenuCommand* pPauseMenuCommand = new PauseMenuCommand(m_pMenusComp);
	MouseClickGameMenus* pMouseClickCommand = new MouseClickGameMenus(m_pMenusComp->GetInWhatButtonGameMenu(), m_pMenusComp);

	input.AddCommand(ControllerButton::Start, KeyBoardAndMouseButton::ButtonEscape, WayKeyBoardButton::buttonDown, pPauseMenuCommand);
	input.AddCommand(dae::ControllerButton::None, dae::KeyBoardAndMouseButton::MouseButtonLeft, dae::WayKeyBoardButton::MouseButtonDown, pMouseClickCommand);

}

void Level::Update()
{
	m_CurrentRespawnTimer += GameTime::GetInstance().GetDeltaTime();

	UpdateLevel();

	UpdateRespawning();

	UpdatePlayerCollsionWithEnemy();
}

void Level::UpdateRespawning()
{
	if (m_CurrentRespawnTimer > m_MaxRespawnTimer)
	{
		int whatCharacter = rand() % 3;
		auto fieldData = m_pEnemies[whatCharacter]->GetFieldDataPlayer();
		if (m_pEnemies[whatCharacter]->GetGameObject()->GetIsActive())
		{
			for (size_t i = 0; i < m_pEnemies.size(); ++i)
			{
				if (!m_pEnemies[i]->GetGameObject()->GetIsActive())
				{
					whatCharacter = int(i);
					break;
				}
			}
		}
		m_pEnemies[whatCharacter]->GetGameObject()->SetIsActive(true);

		if (m_pEnemies[whatCharacter]->GetGameObject()->HasComponent<SlickAndSam>())
		{
			m_pEnemies[whatCharacter]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_pPlayingField->GetFieldDataFirst().MiddlePosX, m_pPlayingField->GetFieldDataFirst().MiddlePosY);
			m_pEnemies[whatCharacter]->SetMoveToTarget(glm::vec2(m_pPlayingField->GetFieldDataFirst().MiddlePosX, m_pPlayingField->GetFieldDataFirst().MiddlePosY));
			m_pEnemies[whatCharacter]->SetThatHeIsAllowedtoMove(false);
			fieldData.Column = m_pPlayingField->GetFieldDataFirst().Column;
			fieldData.Row = m_pPlayingField->GetFieldDataFirst().Row;
			m_pEnemies[whatCharacter]->SetFieldData(fieldData);
			m_pEnemies[whatCharacter]->ResetCurrentTime();
		}
		else if (m_pEnemies[whatCharacter]->GetGameObject()->HasComponent<UggAndWrongway>())
		{
			int whatMovement = rand() % 2;
			switch (whatMovement)
			{
			case 0:
				m_pEnemies[whatCharacter]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_pPlayingField->GetFieldDataLeftBottom().MiddlePosX, m_pPlayingField->GetFieldDataLeftBottom().MiddlePosY);
				m_pEnemies[whatCharacter]->SetMoveToTarget(glm::vec2(m_pPlayingField->GetFieldDataLeftBottom().MiddlePosX, m_pPlayingField->GetFieldDataLeftBottom().MiddlePosY));
				m_pEnemies[whatCharacter]->SetThatHeIsAllowedtoMove(false);
				fieldData.Column = m_pPlayingField->GetFieldDataLeftBottom().Column;
				fieldData.Row = m_pPlayingField->GetFieldDataLeftBottom().Row;
				m_pEnemies[whatCharacter]->SetFieldData(fieldData);
				m_pEnemies[whatCharacter]->ResetCurrentTime();
				break;
			case 1:
				m_pEnemies[whatCharacter]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_pPlayingField->GetFieldDataLast().MiddlePosX, m_pPlayingField->GetFieldDataLast().MiddlePosY);
				m_pEnemies[whatCharacter]->SetMoveToTarget(glm::vec2(m_pPlayingField->GetFieldDataLast().MiddlePosX, m_pPlayingField->GetFieldDataLast().MiddlePosY));
				m_pEnemies[whatCharacter]->SetThatHeIsAllowedtoMove(false);
				fieldData.Column = m_pPlayingField->GetFieldDataLast().Column;
				fieldData.Row = m_pPlayingField->GetFieldDataLast().Row;
				m_pEnemies[whatCharacter]->SetFieldData(fieldData);
				m_pEnemies[whatCharacter]->ResetCurrentTime();
				break;
			default:
				break;
			}
		}
		else if (m_pEnemies[whatCharacter]->GetGameObject()->HasComponent<Coily>())
		{
			m_pEnemies[whatCharacter]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_pPlayingField->GetFieldDataFirst().MiddlePosX, m_pPlayingField->GetFieldDataFirst().MiddlePosY);
			m_pEnemies[whatCharacter]->SetMoveToTarget(glm::vec2(m_pPlayingField->GetFieldDataFirst().MiddlePosX, m_pPlayingField->GetFieldDataFirst().MiddlePosY));
			m_pEnemies[whatCharacter]->SetThatHeIsAllowedtoMove(false);
			m_pEnemies[whatCharacter]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetTexture("CoilyEgg.png");
			m_pEnemies[whatCharacter]->GetGameObject()->GetComponent<Coily>()->SetIsEgg(true);
			fieldData.Column = m_pPlayingField->GetFieldDataFirst().Column;
			fieldData.Row = m_pPlayingField->GetFieldDataFirst().Row;
			m_pEnemies[whatCharacter]->SetFieldData(fieldData);
			m_pEnemies[whatCharacter]->ResetCurrentTime();
		}

		m_CurrentRespawnTimer = 0.0f;
	}
}

void Level::UpdatePlayerCollsionWithEnemy()
{
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
						m_pQBerts[j]->GetGameObject()->GetComponent<dae::HealthComponent>()->LoseLive();
						m_pQBerts[j]->RespawnQBert();
						m_pEnemies[i]->GetGameObject()->SetIsActive(false);
					}
				}
			}
			if (m_pQBerts[j]->GetGameObject()->GetComponent<dae::HealthComponent>()->GetRemainingLives() <= 0)
			{
				m_pMenusComp->GetGameObject()->SetIsActive(true);
				m_pMenusComp->SetDeathScreenActive(m_pQBerts[j]->GetGameObject()->GetComponent<dae::ScoreComponent>()->GetScore());
				GameTime::GetInstance().SetPaused(true);
			}
		}
	}
}

void Level::UpdateLevel()
{
	if (m_pPlayingField->GetLevelIsResetted())
	{
		for (size_t i = 0; i < m_pEnemies.size(); ++i)
		{
			m_pEnemies[i]->GetGameObject()->SetIsActive(false);
		}
		m_CurrentRespawnTimer = 0.0f;
		for (size_t i = 0; i < m_pQBerts.size(); ++i)
		{
			m_pQBerts[i]->RespawnQBert();
		}
		m_pQBerts[0]->GetGameObject()->GetComponent<dae::ScoreComponent>()->AddScore(m_pPlayingField->GetColorWheelsRemaining() * 50);

		m_pPlayingField->SetLevelIsResetted(false);
		m_pPlayingField->ResetColorWheelsRemaining();
	}
}