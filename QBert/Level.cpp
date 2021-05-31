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
using namespace dae;
Level::Level()
{

}

void Level::LoadGame(dae::Scene& currentScene)
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

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto component2 = std::make_shared<TextComponent>("Programming 4 Exam Assignment", font);
	component2->SetPosition(80, 20);
	go->addComponent(component2);

	auto component3 = std::make_shared<FPSComponent>();
	go->addComponent(component3);
	currentScene.Add(go);

	//init player
	int playerIndex{ 0 };
	auto& renderer = dae::Renderer::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	auto qBert = std::make_shared<dae::GameObject>();
	FieldDataPlayer QBertFieldData;
	QBertFieldData.Row = componentplayingField->GetPlayerFieldDataFirst().Row;
	QBertFieldData.Column = componentplayingField->GetPlayerFieldDataFirst().Column;


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
	componentTextureQBert->SetPosition(componentplayingField->GetPlayerFieldDataFirst().MiddlePosX, componentplayingField->GetPlayerFieldDataFirst().MiddlePosY);
	std::shared_ptr<QBertComponent> componentQbertData{ std::make_shared<QBertComponent>() };
	m_pQBert = componentQbertData;
	qBert->addComponent(componentTextureQBert);
	componentQbertData->SetFieldData(QBertFieldData);
	qBert->addComponent(componentQbertData);
	qBert->addComponent(scoreComponent);
	qBert->addComponent(subjectComponent);
	qBert->addComponent(playerIndexComponent);
	qBert->addComponent(healtComponent);
	currentScene.Add(qBert);

	renderer.InitPlayer(playerIndexComponent->GetIndexPlayer(), healtComponent->GetRemainingLives(), scoreComponent->GetScore());




	//ugg
	auto UggComponent = std::make_shared<dae::GameObject>();
	FieldDataPlayer UggFieldData;
	UggFieldData.Row = componentplayingField->GetPlayerFieldDataLast().Row;
	UggFieldData.Column = componentplayingField->GetPlayerFieldDataLast().Column;

	std::shared_ptr<TextureComponent> componentTextureUgg{ std::make_shared<TextureComponent>() };
	componentTextureUgg->SetTexture("EnemyUgg.png");
	componentTextureUgg->SetPosition(componentplayingField->GetPlayerFieldDataLast().MiddlePosX, componentplayingField->GetPlayerFieldDataLast().MiddlePosY);
	std::shared_ptr<UggAndWrongway> componentUggData{ std::make_shared<UggAndWrongway>(UggComponent ,componentplayingField) };
	UggComponent->addComponent(componentTextureUgg);
	componentUggData->SetFieldData(UggFieldData);
	UggComponent->addComponent(componentUggData);
	currentScene.Add(UggComponent);
	m_pEnemies.push_back(componentUggData);

	//slick/sam
	auto SlickGameObject = std::make_shared<dae::GameObject>();
	FieldDataPlayer SlickFieldData;
	SlickFieldData.Row = componentplayingField->GetPlayerFieldDataFirst().Row;
	SlickFieldData.Column = componentplayingField->GetPlayerFieldDataFirst().Column;

	std::shared_ptr<TextureComponent> componentTextureSlick{ std::make_shared<TextureComponent>() };
	componentTextureSlick->SetTexture("SamOrSlick.png");
	componentTextureSlick->SetPosition(componentplayingField->GetPlayerFieldDataFirst().MiddlePosX, componentplayingField->GetPlayerFieldDataFirst().MiddlePosY);
	std::shared_ptr<SlickAndSam> componentSlickData{ std::make_shared<SlickAndSam>(SlickGameObject ,componentplayingField) };
	SlickGameObject->addComponent(componentTextureSlick);
	componentSlickData->SetFieldData(SlickFieldData);
	SlickGameObject->addComponent(componentSlickData);
	currentScene.Add(SlickGameObject);
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
	MoveLeftDownCommand* moveLeft = new MoveLeftDownCommand(qBert, componentplayingField, "../Data/BackGroundTileYellow.png");
	MoveRightDownCommand* moveRight = new MoveRightDownCommand(qBert, componentplayingField, "../Data/BackGroundTileYellow.png");
	MoveLeftUpCommand* moveLeftUp = new MoveLeftUpCommand(qBert, componentplayingField, "../Data/BackGroundTileYellow.png");
	MoveRightUpCommand* moveRightUp = new MoveRightUpCommand(qBert, componentplayingField, "../Data/BackGroundTileYellow.png");
	//	qBertComponent
	input.AddCommand(ControllerButton::ButtonX, KeyBoardAndMouseButton::ButtonA, WayKeyBoardButton::buttonDown, moveLeft);
	input.AddCommand(ControllerButton::ButtonA, KeyBoardAndMouseButton::ButtonD, WayKeyBoardButton::buttonDown, moveRight);
	input.AddCommand(ControllerButton::ButtonY, KeyBoardAndMouseButton::ButtonQ, WayKeyBoardButton::buttonDown, moveLeftUp);
	input.AddCommand(ControllerButton::ButtonB, KeyBoardAndMouseButton::ButtonE, WayKeyBoardButton::buttonDown, moveRightUp);
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
		auto fieldData = m_pQBert->GetFieldDataPlayer();

		m_pQBert->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_PlayingField->GetPlayerFieldDataFirst().MiddlePosX, m_PlayingField->GetPlayerFieldDataFirst().MiddlePosY);
		fieldData.Column = m_PlayingField->GetPlayerFieldDataFirst().Column;
		fieldData.Row = m_PlayingField->GetPlayerFieldDataFirst().Row;
		m_pQBert->SetFieldData(fieldData);
		m_pQBert->ResetCurrentTime();
		m_PlayingField->SetLevelIsResetted(false);
		m_pQBert->GetGameObject()->GetComponent<dae::ScoreComponent>()->AddScore(m_PlayingField->GetColorWheelsRemaining() * 50);
		m_PlayingField->ResetColorWheelsRemaining();
	}

	if (m_CurrentRespawnTimer > m_MaxRespawnTimer)
	{
		int whatCharacter = rand() % 2;
		std::cout << "character: " << whatCharacter << std::endl;
		auto fieldData = m_pEnemies[whatCharacter]->GetFieldDataPlayer();
		if (m_pEnemies[whatCharacter]->GetGameObject()->GetIsActive())
		{
			for (size_t i = 0; i < m_pEnemies.size(); ++i)
			{
				if (!m_pEnemies[i]->GetGameObject()->GetIsActive())
				{
					whatCharacter = i;
					break;
				}
			}
		}
		m_pEnemies[whatCharacter]->GetGameObject()->SetIsActive(true);

		if (m_pEnemies[whatCharacter]->GetGameObject()->HasComponent<SlickAndSam>())
		{
			m_pEnemies[whatCharacter]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_PlayingField->GetPlayerFieldDataFirst().MiddlePosX, m_PlayingField->GetPlayerFieldDataFirst().MiddlePosY);
			fieldData.Column = m_PlayingField->GetPlayerFieldDataFirst().Column;
			fieldData.Row = m_PlayingField->GetPlayerFieldDataFirst().Row;
			m_pEnemies[whatCharacter]->SetFieldData(fieldData);
			m_pEnemies[whatCharacter]->ResetCurrentTime();
		}
		else if (m_pEnemies[whatCharacter]->GetGameObject()->HasComponent<UggAndWrongway>())
		{
			//respawn logic
			int whatMovement = rand() % 2;
			switch (whatMovement)
			{
			case 0:
				//move left
				m_pEnemies[whatCharacter]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_PlayingField->GetFieldDataLeftBottom().MiddlePosX, m_PlayingField->GetFieldDataLeftBottom().MiddlePosY);
				fieldData.Column = m_PlayingField->GetFieldDataLeftBottom().Column;
				fieldData.Row = m_PlayingField->GetFieldDataLeftBottom().Row;
				m_pEnemies[whatCharacter]->SetFieldData(fieldData);
				m_pEnemies[whatCharacter]->ResetCurrentTime();
				break;
			case 1:
				//move right
				m_pEnemies[whatCharacter]->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_PlayingField->GetPlayerFieldDataLast().MiddlePosX, m_PlayingField->GetPlayerFieldDataLast().MiddlePosY);
				fieldData.Column = m_PlayingField->GetPlayerFieldDataLast().Column;
				fieldData.Row = m_PlayingField->GetPlayerFieldDataLast().Row;
				m_pEnemies[whatCharacter]->SetFieldData(fieldData);
				m_pEnemies[whatCharacter]->ResetCurrentTime();
				break;
			default:
				//nothing
				break;
			}
		}

		m_CurrentRespawnTimer = 0.0f;
		//random time logic

	}
	for (size_t i = 0; i < m_pEnemies.size(); ++i)
	{
		if (m_pEnemies[i]->GetFieldDataPlayer().Row == m_pQBert->GetFieldDataPlayer().Row && m_pEnemies[i]->GetFieldDataPlayer().Column == m_pQBert->GetFieldDataPlayer().Column)
		{
			if (m_pEnemies[i]->GetGameObject()->GetIsActive())
			{
				if (m_pEnemies[i]->GetGameObject()->HasComponent<SlickAndSam>())
				{
					m_pQBert->GetGameObject()->GetComponent<dae::ScoreComponent>()->AddScore(300);

					m_pEnemies[i]->GetGameObject()->SetIsActive(false);
				}
				else
				{
					//reset player pos/delete enemy
					std::cout << "player hit";
					//0getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
					m_pQBert->GetGameObject()->GetComponent<dae::HealthComponent>()->LoseLive();
					//m_pQBert->GetGameObject()->SetPosition(m_PlayingField->GetPlayerFieldDataFirst().MiddlePosX, m_PlayingField->GetPlayerFieldDataFirst().MiddlePosY);
					//m_pQBert->SetFieldData(FieldDataPlayer{ m_PlayingField->GetPlayerFieldDataFirst().Row, m_PlayingField->GetPlayerFieldDataFirst().Column});
					auto fieldData = m_pQBert->GetFieldDataPlayer();

					m_pQBert->GetGameObject()->GetComponent<dae::TextureComponent>()->SetPosition(m_PlayingField->GetPlayerFieldDataFirst().MiddlePosX, m_PlayingField->GetPlayerFieldDataFirst().MiddlePosY);
					fieldData.Column = m_PlayingField->GetPlayerFieldDataFirst().Column;
					fieldData.Row = m_PlayingField->GetPlayerFieldDataFirst().Row;
					m_pQBert->SetFieldData(fieldData);
					m_pQBert->ResetCurrentTime();
					m_pEnemies[i]->GetGameObject()->SetIsActive(false);
				}
			}
		}
	}
}