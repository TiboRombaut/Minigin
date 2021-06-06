#include "CommandQbert.h"
#include "QBertComponent.h"
#include "AIComponent.h"
#include "ScoreComponent.h"
#include <iostream>
#include "SlickAndSam.h"
#include "GameTime.h"
#include <InputManager.h>
#include "Level.h"
#include <memory>
#include "SceneManager.h"
#include "Scene.h"
#include "Coily.h"
#include <ServiceLocator.h>
#include <SceneManager.h>

MoveLeftDownCommand::MoveLeftDownCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField)
	: Command(pObject)
	, m_pField(pField)
{

}

void MoveLeftDownCommand::Execute()
{
	bool hasQbertComp = false;
	ControlComponent* comp = nullptr;
	if (getActor()->HasComponent<QBertComponent>())
	{
		comp = getActor()->GetComponent<QBertComponent>();
		hasQbertComp = true;
	}
	else if (getActor()->HasComponent<AIComponent>())
	{
		comp = getActor()->GetComponent<AIComponent>();
	}
	else
	{
		return;
	}	
	auto fieldData = comp->GetFieldDataPlayer();
	auto field = m_pField->GetField();
	for (size_t i = 0; i < m_pField->GetField().size(); i++)
	{
		if (field[i].Row == fieldData.Row + 1 && field[i].Column == fieldData.Column)
		{
			if (comp->GetCanMove())
			{
				getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(field[i].MiddlePosX, field[i].MiddlePosY));
				fieldData.Column = field[i].Column;
				fieldData.Row = field[i].Row;
				comp->SetFieldData(fieldData);
				comp->ResetCurrentTime();
			

				if (hasQbertComp)
				{
					dae::ServiceLocator::Get_Sound_System().Play(0, 1, "../Data/QbertHop.wav");

					if (m_pField->ChangeTileColor(i, true))
					{
						int value{ 25 };
						getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
					}
				}
				else if (comp->GetGameObject()->HasComponent<SlickAndSam>())
				{
					m_pField->ChangeTileColor(i, false);
				}
				return;
			}
			else
			{
				std::cout << "Wait A little bit\n";
				return;
			}
		}
	}
	if (hasQbertComp)
	{
		if (comp->GetCanMove())
		{
			getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().x - field[0].pTextureComponent->GetWidth(),
				getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().y + field[0].pTextureComponent->GetHeight()));
			fieldData.Column = -1;
			fieldData.Row = -1;
			comp->SetFieldData(fieldData);
			comp->ResetCurrentTime();
			dae::ServiceLocator::Get_Sound_System().Play(0, 1, "../Data/QBertFall.wav");
		}
	}
};

MoveRightDownCommand::MoveRightDownCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField)
	: Command(pObject)
	, m_pField(pField)
{

}

void MoveRightDownCommand::Execute()
{

	bool hasQbertComp = false;
	ControlComponent* comp = nullptr;
	if (getActor()->HasComponent<QBertComponent>())
	{
		comp = getActor()->GetComponent<QBertComponent>();
		hasQbertComp = true;
	}
	else if (getActor()->HasComponent<AIComponent>())
	{
		comp = getActor()->GetComponent<AIComponent>();
	}
	else
	{
		return;
	}	

	auto fieldData = comp->GetFieldDataPlayer();
	auto field = m_pField->GetField();
	for (size_t i = 0; i < field.size(); i++)
	{
		if (field[i].Row == fieldData.Row + 1 && field[i].Column == fieldData.Column+1)
		{
			if (comp->GetCanMove())
			{
				 getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(field[i].MiddlePosX, field[i].MiddlePosY));
				fieldData.Column = field[i].Column;
				fieldData.Row = field[i].Row;
				comp->SetFieldData(fieldData);
				comp->ResetCurrentTime();

				if (hasQbertComp)
				{
					dae::ServiceLocator::Get_Sound_System().Play(0, 1, "../Data/QbertHop.wav");
					if (m_pField->ChangeTileColor(i, true))
					{
						int value{ 25 };
						getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
					}
				}
				else if (comp->GetGameObject()->HasComponent<SlickAndSam>())
				{
					m_pField->ChangeTileColor(i, false);
				}

				return;
			}
			else
			{
				std::cout << "Wait A little bit\n";
				return;
			}
		}
	}
	if (hasQbertComp)
	{
		if (comp->GetCanMove())
		{
			getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().x + field[0].pTextureComponent->GetWidth(),
				getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().y + field[0].pTextureComponent->GetHeight()));
			fieldData.Column = -1;
			fieldData.Row = -1;
			comp->SetFieldData(fieldData);
			comp->ResetCurrentTime();
			dae::ServiceLocator::Get_Sound_System().Play(0, 1, "../Data/QBertFall.wav");
		}
	}
};

MoveLeftUpCommand::MoveLeftUpCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField)
	:Command(pObject)
	, m_pField(pField)
{

}
void MoveLeftUpCommand::Execute()
{
	bool hasQbertComp = false;
	ControlComponent* comp = nullptr;
	if (getActor()->HasComponent<QBertComponent>())
	{
		comp = getActor()->GetComponent<QBertComponent>();
		hasQbertComp = true;
	}
	else if (getActor()->HasComponent<AIComponent>())
	{
		comp = getActor()->GetComponent<AIComponent>();
	}
	else
	{
		return;
	}
	auto fieldData = comp->GetFieldDataPlayer();
	auto field = m_pField->GetField();

	for (size_t i = 0; i < field.size(); i++)
	{
		if (field[i].Row == fieldData.Row - 1 && field[i].Column == fieldData.Column-1)
		{
			if (comp->GetCanMove())
			{
				if (field[i].pTextureComponent->GetFileName() == "ColorWheel.png" )
				{
					if (hasQbertComp)
					{
						glm::vec2 sizeQbert{ getActor()->GetComponent<dae::TextureComponent>()->GetWidth(),getActor()->GetComponent<dae::TextureComponent>()->GetHeight() };
						getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(field[i].MiddlePosX - sizeQbert.x, field[i].MiddlePosY - sizeQbert.y));
						getActor()->GetComponent<QBertComponent>()->ColorWheelNeedsToMovetoTop(field[i].pTextureComponent, glm::vec2(field[0].MiddlePosX, field[0].MiddlePosY));

						fieldData.Column = field[i].Column;
						fieldData.Row = field[i].Row;
						comp->SetFieldData(fieldData);
						comp->ResetCurrentTime();
					}
					else if (comp->GetGameObject()->HasComponent<Coily>())
					{
						if (!getActor()->GetComponent<Coily>()->GetIsDead())
						{		
							getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(field[i].MiddlePosX, field[i].MiddlePosY));
							getActor()->GetComponent<Coily>()->SetIsDead(true);
							dae::ServiceLocator::Get_Sound_System().Play(0, 1, "../Data/SnakeFall.wav");
						}
					}
					return;
				}
				getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(field[i].MiddlePosX, field[i].MiddlePosY));
				fieldData.Column = field[i].Column;
				fieldData.Row = field[i].Row;
				comp->SetFieldData(fieldData);
				comp->ResetCurrentTime();

				if (hasQbertComp)
				{
					dae::ServiceLocator::Get_Sound_System().Play(0, 1, "../Data/QbertHop.wav");
					if (m_pField->ChangeTileColor(i, true))
					{
						int value{ 25 };
						getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
					}
				}
				else if (comp->GetGameObject()->HasComponent<SlickAndSam>())
				{
					m_pField->ChangeTileColor(i, false);
				}		
				return;
			}
			else
			{
				std::cout << "Wait A little bit\n";
				return;
			}
		}
	}

	if (hasQbertComp)
	{
		if (comp->GetCanMove())
		{
			getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().x - field[0].pTextureComponent->GetWidth(),
				getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().y - field[0].pTextureComponent->GetHeight()));
			fieldData.Column = -1;
			fieldData.Row = -1;
			comp->SetFieldData(fieldData);
			comp->ResetCurrentTime();
			dae::ServiceLocator::Get_Sound_System().Play(0, 1, "../Data/QBertFall.wav");
		}
	}
};

MoveRightUpCommand::MoveRightUpCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField)
	: Command(pObject)
	, m_pField(pField)
{

}


void MoveRightUpCommand::Execute()
{
	bool hasQbertComp = false;
	ControlComponent* comp = nullptr;
	if (getActor()->HasComponent<QBertComponent>())
	{
		comp = getActor()->GetComponent<QBertComponent>();
		hasQbertComp = true;
	}
	else if (getActor()->HasComponent<AIComponent>())
	{
		comp = getActor()->GetComponent<AIComponent>();
	}
	else
	{
		return;
	}

	auto fieldData = comp->GetFieldDataPlayer();
	auto field = m_pField->GetField();

	for (size_t i = 0; i < field.size(); i++)
	{
	if (field[i].Row == fieldData.Row - 1 && field[i].Column == fieldData.Column)
	{
		if (comp->GetCanMove())
		{
			if (field[i].pTextureComponent->GetFileName() == "ColorWheel.png")
			{
				if (hasQbertComp)
				{
					glm::vec2 sizeQbert{ getActor()->GetComponent<dae::TextureComponent>()->GetWidth(),getActor()->GetComponent<dae::TextureComponent>()->GetHeight() };
					getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(field[i].MiddlePosX - sizeQbert.x, field[i].MiddlePosY - sizeQbert.y));
					getActor()->GetComponent<QBertComponent>()->ColorWheelNeedsToMovetoTop(field[i].pTextureComponent, glm::vec2(field[0].MiddlePosX, field[0].MiddlePosY));

					fieldData.Column = field[i].Column;
					fieldData.Row = field[i].Row;
					comp->SetFieldData(fieldData);
					comp->ResetCurrentTime();
				}
				else if (comp->GetGameObject()->HasComponent<Coily>())
				{
					if (!getActor()->GetComponent<Coily>()->GetIsDead())
					{
						getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(field[i].MiddlePosX, field[i].MiddlePosY));
						getActor()->GetComponent<Coily>()->SetIsDead(true);
						dae::ServiceLocator::Get_Sound_System().Play(0, 1.0f, "../Data/SnakeFall.wav");
					}
				}
				return;
			}
			getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(field[i].MiddlePosX, field[i].MiddlePosY));
			fieldData.Column = field[i].Column;
			fieldData.Row = field[i].Row;
			comp->SetFieldData(fieldData);
			comp->ResetCurrentTime();
	
			if (hasQbertComp)
			{
				dae::ServiceLocator::Get_Sound_System().Play(0, 1, "../Data/QbertHop.wav");
				if (m_pField->ChangeTileColor(i, true))
				{
					int value{ 25 };
					getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
				}
			}
			else if (comp->GetGameObject()->HasComponent<SlickAndSam>())
			{
				m_pField->ChangeTileColor(i, false);
			}
			return;
		}
		else
		{
			std::cout << "Wait A little bit\n";
			return;
		}
	}
	}
	if (hasQbertComp)
	{
		if (comp->GetCanMove())
		{
			getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().x + field[0].pTextureComponent->GetWidth(),
				getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().y - field[0].pTextureComponent->GetHeight()));
			fieldData.Column = -1;
			fieldData.Row = -1;
			comp->SetFieldData(fieldData);
			comp->ResetCurrentTime();
			dae::ServiceLocator::Get_Sound_System().Play(0, 1, "../Data/QBertFall.wav");
		}
	}
};

MouseClickMainMenuCommand::MouseClickMainMenuCommand(InWhatButtonMainMenu& clickHappened)
	:Command(nullptr)
	, m_InWhatButton(clickHappened)
{

}
void MouseClickMainMenuCommand::Execute()
{
	switch (m_InWhatButton)
	{
	case InWhatButtonMainMenu::Solo:
	{
		if (dae::SceneManager::GetInstance().GetActiveScene()->GetName() == "Menu")
		{
			auto& scene = dae::SceneManager::GetInstance().CreateScene("Solo");

			std::shared_ptr<dae::GameObject> obj = std::make_shared<dae::GameObject>();
			std::shared_ptr<Level> level = std::make_shared<Level>();
			level->LoadGameSolo(scene);
			obj->addComponent(level);
			scene.Add(obj);

			dae::SceneManager::GetInstance().SetActiveScene("Solo");
		}
		break;
	}
	case InWhatButtonMainMenu::Coop:
	{
		if (dae::SceneManager::GetInstance().GetActiveScene()->GetName() == "Menu")
		{
			auto& scene = dae::SceneManager::GetInstance().CreateScene("Coop");

			std::shared_ptr<dae::GameObject> obj = std::make_shared<dae::GameObject>();
			std::shared_ptr<Level> level = std::make_shared<Level>();
			level->LoadGameCoop(scene);
			obj->addComponent(level);
			scene.Add(obj);

			dae::SceneManager::GetInstance().SetActiveScene("Coop");
		}
		break;
	}
	case InWhatButtonMainMenu::Vs:
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("Vs");

		std::shared_ptr<dae::GameObject> obj = std::make_shared<dae::GameObject>();
		std::shared_ptr<Level> level = std::make_shared<Level>();
		level->LoadGameVs(scene);
		obj->addComponent(level);
		scene.Add(obj);

		dae::SceneManager::GetInstance().SetActiveScene("Vs");
		break;
	}
	case InWhatButtonMainMenu::None:
		break;
	default:
		break;
	}
}

MouseClickGameMenus::MouseClickGameMenus(InWhatButtonGameMenu& clickHappened, std::shared_ptr<Menus> pMenus)
	:Command(nullptr)
	, m_InWhatButton(clickHappened)
	,m_pMenus(pMenus)
{

}
void MouseClickGameMenus::Execute()
{
	switch (m_InWhatButton)
	{
	case InWhatButtonGameMenu::Play:
	{
		if (dae::SceneManager::GetInstance().GetActiveScene()->GetName() != "Menu")
		{
			if (GameTime::GetInstance().GetPaused())
			{
				if (m_pMenus->GetGameObject()->GetIsActive())
				{
					m_pMenus->SetPauseScreenInActive();
					m_pMenus->GetGameObject()->SetIsActive(false);
					GameTime::GetInstance().SetPaused(false);
				}
			}
		}


	}
	break;
	case InWhatButtonGameMenu::MainMenu:
		if (dae::SceneManager::GetInstance().GetActiveScene()->GetName() != "Menu")
		{
			if (GameTime::GetInstance().GetPaused())
			{
				dae::SceneManager::GetInstance().DeleteScene(dae::SceneManager::GetInstance().GetActiveScene()->GetName());
				dae::SceneManager::GetInstance().SetActiveScene("Menu");
				GameTime::GetInstance().SetPaused(false);
			}
		}
		break;

	case InWhatButtonGameMenu::Restart:
	{
		std::string nameScene = dae::SceneManager::GetInstance().GetActiveScene()->GetName();
		if (nameScene != "Menu")
		{
			if (GameTime::GetInstance().GetPaused())
			{
				dae::SceneManager::GetInstance().DeleteScene(nameScene);

				if (nameScene == "Solo" || nameScene == "solo")
				{
					auto& scene = dae::SceneManager::GetInstance().CreateScene("Solo");

					std::shared_ptr<dae::GameObject> pObj = std::make_shared<dae::GameObject>();
					std::shared_ptr<Level> pLevel = std::make_shared<Level>();
					pLevel->LoadGameSolo(scene);
					pObj->addComponent(pLevel);
					scene.Add(pObj);
					GameTime::GetInstance().SetPaused(false);
					dae::SceneManager::GetInstance().SetActiveScene("Solo");
				}
				else if (nameScene == "Coop" || nameScene == "coop")
				{
					auto& scene = dae::SceneManager::GetInstance().CreateScene("Coop");

					std::shared_ptr<dae::GameObject> obj = std::make_shared<dae::GameObject>();
					std::shared_ptr<Level> pLevel = std::make_shared<Level>();
					pLevel->LoadGameCoop(scene);
					obj->addComponent(pLevel);
					scene.Add(obj);
					GameTime::GetInstance().SetPaused(false);

					dae::SceneManager::GetInstance().SetActiveScene("Coop");
				}
				else if (nameScene == "Vs" || nameScene == "vs")
				{
					auto& scene = dae::SceneManager::GetInstance().CreateScene("Vs");

					std::shared_ptr<dae::GameObject> pObj = std::make_shared<dae::GameObject>();
					std::shared_ptr<Level> pLevel = std::make_shared<Level>();
					pLevel->LoadGameVs(scene);
					pObj->addComponent(pLevel);
					scene.Add(pObj);
					GameTime::GetInstance().SetPaused(false);

					dae::SceneManager::GetInstance().SetActiveScene("Vs");
				}
			}
		}
		break;
	}
	case InWhatButtonGameMenu::Exit:
		if (dae::SceneManager::GetInstance().GetActiveScene()->GetName() != "Menu")
		{
			if (GameTime::GetInstance().GetPaused())
			{
				dae::InputManager::GetInstance().EndGame();
			}
		}
		break;
	case InWhatButtonGameMenu::None:
		break;
	default:
		break;
	}
}

PauseMenuCommand::PauseMenuCommand(std::shared_ptr<Menus> pMenus)
	:Command(nullptr)
	, m_pMenus(pMenus)
{

}
void PauseMenuCommand::Execute()
{
	auto menuGameObject = m_pMenus->GetGameObject();
	if (menuGameObject->GetIsActive())
	{
		m_pMenus->SetPauseScreenInActive();
		menuGameObject->SetIsActive(false);
		GameTime::GetInstance().SetPaused(false);
	}
	else
	{
		m_pMenus->SetPauseScreenActive();
		menuGameObject->SetIsActive(true);
		GameTime::GetInstance().SetPaused(true);
	}
}