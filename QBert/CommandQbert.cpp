#include "CommandQbert.h"
#include "QBertComponent.h"
#include "AIComponent.h"
//#include <TextureComponent.h>
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

MoveLeftDownCommand::MoveLeftDownCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field, std::string fileNamePath)
	:Command(pObject)
	, m_Field(field)
	,m_FileNameBackgroundTile(fileNamePath)
{

}

void MoveLeftDownCommand::Execute()
{
	//if (getActor()->HasComponent<Coily>())
	//{
	//	if (!getActor()->GetComponent<Coily>()->HasReachedBottom())
	//	{
	//		return;
	//	}
	//}

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

	for (size_t i = 0; i < m_Field->GetField().size(); i++)
	{
		if (m_Field->GetField()[i].Row == fieldData.Row + 1 && m_Field->GetField()[i].Column == fieldData.Column)
		{
			if (comp->GetCanMove())
			{
				if (m_Field->GetField()[i].TextureComponent->GetFileName() == "ColorWheel.png")
				{
					if (hasQbertComp)
					{
						getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[0].MiddlePosX, m_Field->GetField()[0].MiddlePosY);
						fieldData.Column = m_Field->GetField()[0].Column;
						fieldData.Row = m_Field->GetField()[0].Row;
						comp->SetFieldData(fieldData);
						m_Field->GetField()[i].TextureComponent->GetGameObject()->RemoveComponent(m_Field->GetField()[i].TextureComponent);
						m_Field->GetField().erase(m_Field->GetField().begin() + i);
					}
					return;
				}
				getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY);
				fieldData.Column = m_Field->GetField()[i].Column;
				fieldData.Row = m_Field->GetField()[i].Row;
				comp->SetFieldData(fieldData);
				comp->ResetCurrentTime();

				if (hasQbertComp)
				{
					if (m_Field->ChangeTileColor(i, true))
					{
						int value{ 25 };
						getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
					}
				}
				else if (comp->GetGameObject()->HasComponent<SlickAndSam>())
				{
					m_Field->ChangeTileColor(i, false);
				}

				//if (m_Field->GetField()[i].TextureComponent->GetFileName() != m_FileNameBackgroundTile && hasQbertComp)
				//{
				//	m_Field->GetField()[i].TextureComponent->SetTexture(m_FileNameBackgroundTile);
				//	//also give points
				//	int value{ 25 };
				//	getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
				//}
				//else if(comp->GetGameObject()->HasComponent<SlickAndSam>())
				//{
				//	if (m_Field->GetField()[i].TextureComponent->GetFileName() == m_Field->GetSecondTileName())
				//	{
				//		m_Field->GetField()[i].TextureComponent->SetTexture(m_Field->GetFirstTileName());
				//	}
				//	else if (m_Field->GetField()[i].TextureComponent->GetFileName() == m_Field->GetThirthTileName())
				//	{
				//		m_Field->GetField()[i].TextureComponent->SetTexture(m_Field->GetSecondTileName());
				//	}
				//}
				return;
			}
			else
			{
				std::cout << "Wait A little bit\n";
			}
		}
	}
};

MoveRightDownCommand::MoveRightDownCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field, std::string fileNamePath)
	:Command(pObject)
	, m_Field(field)
	, m_FileNameBackgroundTile(fileNamePath)
{

}

void MoveRightDownCommand::Execute()
{
	//if (getActor()->HasComponent<Coily>())
	//{
	//	if (!getActor()->GetComponent<Coily>()->HasReachedBottom())
	//	{
	//		return;
	//	}
	//}

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

	for (size_t i = 0; i < m_Field->GetField().size(); i++)
	{
		if (m_Field->GetField()[i].Row == fieldData.Row + 1 && m_Field->GetField()[i].Column == fieldData.Column+1)
		{
			if (comp->GetCanMove())
			{
				//colorwheen logic => you go on it and teleport to spawn
				if (m_Field->GetField()[i].TextureComponent->GetFileName() == "ColorWheel.png")
				{
					if (hasQbertComp)
					{
						getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[0].MiddlePosX, m_Field->GetField()[0].MiddlePosY);
						fieldData.Column = m_Field->GetField()[0].Column;
						fieldData.Row = m_Field->GetField()[0].Row;
						comp->SetFieldData(fieldData);
						m_Field->GetField()[i].TextureComponent->GetGameObject()->RemoveComponent(m_Field->GetField()[i].TextureComponent);
						m_Field->GetField().erase(m_Field->GetField().begin() + i);
					}
					return;
				}

				//move logic
				getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY);
				fieldData.Column = m_Field->GetField()[i].Column;
				fieldData.Row = m_Field->GetField()[i].Row;
				comp->SetFieldData(fieldData);
				comp->ResetCurrentTime();

				//changing tile Logic
				if (hasQbertComp)
				{
					if (m_Field->ChangeTileColor(i, true))
					{
						int value{ 25 };
						getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
					}
				}
				else if (comp->GetGameObject()->HasComponent<SlickAndSam>())
				{
					m_Field->ChangeTileColor(i, false);
				}
				
				//if (m_Field->GetField()[i].TextureComponent->GetFileName() != m_FileNameBackgroundTile && hasQbertComp)
				//{
				//	m_Field->GetField()[i].TextureComponent->SetTexture(m_FileNameBackgroundTile);
				//	//also give points
				//	int value{ 25 };
				//	getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
				//}
				//else if (comp->GetGameObject()->HasComponent<SlickAndSam>())
				//{
				//	if (m_Field->GetField()[i].TextureComponent->GetFileName() == m_Field->GetSecondTileName())
				//	{
				//		m_Field->GetField()[i].TextureComponent->SetTexture(m_Field->GetFirstTileName());
				//	}
				//	else if (m_Field->GetField()[i].TextureComponent->GetFileName() == m_Field->GetThirthTileName())
				//	{
				//		m_Field->GetField()[i].TextureComponent->SetTexture(m_Field->GetSecondTileName());
				//	}
				//}
				return;
			}
			else
			{
				std::cout << "Wait A little bit\n";
			}
		}
	}
};

MoveLeftUpCommand::MoveLeftUpCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field, std::string fileNamePath)
	:Command(pObject)
	, m_Field(field)
	, m_FileNameBackgroundTile(fileNamePath)
{

}
MoveLeftUpCommand::MoveLeftUpCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field)
	:Command(pObject)
	, m_Field(field)
{

}
void MoveLeftUpCommand::Execute()
{
	//if (getActor()->HasComponent<Coily>())
	//{
	//	if (!getActor()->GetComponent<Coily>()->HasReachedBottom())
	//	{
	//		return;
	//	}
	//}

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

	for (size_t i = 0; i < m_Field->GetField().size(); i++)
	{
		if (m_Field->GetField()[i].Row == fieldData.Row - 1 && m_Field->GetField()[i].Column == fieldData.Column-1)
		{
			if (comp->GetCanMove())
			{
				if (m_Field->GetField()[i].TextureComponent->GetFileName() == "ColorWheel.png" )
				{
					if (hasQbertComp)
					{
						getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[0].MiddlePosX, m_Field->GetField()[0].MiddlePosY);
						fieldData.Column = m_Field->GetField()[0].Column;
						fieldData.Row = m_Field->GetField()[0].Row;
						comp->SetFieldData(fieldData);
						m_Field->GetField()[i].TextureComponent->GetGameObject()->RemoveComponent(m_Field->GetField()[i].TextureComponent);
						m_Field->GetField().erase(m_Field->GetField().begin() + i);
					}
					return;
				}
				getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY);
				fieldData.Column = m_Field->GetField()[i].Column;
				fieldData.Row = m_Field->GetField()[i].Row;
				comp->SetFieldData(fieldData);
				comp->ResetCurrentTime();

				if (hasQbertComp)
				{
					if (m_Field->ChangeTileColor(i, true))
					{
						int value{ 25 };
						getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
					}
				}
				else if (comp->GetGameObject()->HasComponent<SlickAndSam>())
				{
					m_Field->ChangeTileColor(i, false);
				}

				//if (m_Field->GetField()[i].TextureComponent->GetFileName() != m_FileNameBackgroundTile && hasQbertComp)
				//{
				//	m_Field->GetField()[i].TextureComponent->SetTexture(m_FileNameBackgroundTile);
				//	//also give points
				//	int value{ 25 };
				//	getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
				//}				
				return;
			}
			else
			{
				std::cout << "Wait A little bit\n";
			}
		}
	}
};

MoveRightUpCommand::MoveRightUpCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field, std::string fileNamePath)
	:Command(pObject)
	, m_Field(field)
	, m_FileNameBackgroundTile(fileNamePath)
{

}

MoveRightUpCommand::MoveRightUpCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field)
	:Command(pObject)
	, m_Field(field)
{

}


void MoveRightUpCommand::Execute()
{
	//if (getActor()->HasComponent<Coily>())
	//{
	//	if (!getActor()->GetComponent<Coily>()->HasReachedBottom())
	//	{
	//		return;
	//	}
	//}

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
//	auto comp = getActor()->GetComponent<AIComponent>();

	auto fieldData = comp->GetFieldDataPlayer();

	for (size_t i = 0; i < m_Field->GetField().size(); i++)
	{
		if (m_Field->GetField()[i].Row == fieldData.Row - 1 && m_Field->GetField()[i].Column == fieldData.Column)
		{
			if (comp->GetCanMove())
			{
				if (m_Field->GetField()[i].TextureComponent->GetFileName() == "ColorWheel.png" )
				{
					if (hasQbertComp)
					{
						std::cout << "colorwheel rightup";
						getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[0].MiddlePosX, m_Field->GetField()[0].MiddlePosY);
						fieldData.Column = m_Field->GetField()[0].Column;
						fieldData.Row = m_Field->GetField()[0].Row;
						comp->SetFieldData(fieldData);
						m_Field->GetField()[i].TextureComponent->GetGameObject()->RemoveComponent(m_Field->GetField()[i].TextureComponent);
						m_Field->GetField().erase(m_Field->GetField().begin() + i);
					}
					return;
				}

				getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY);
				fieldData.Column = m_Field->GetField()[i].Column;
				fieldData.Row = m_Field->GetField()[i].Row;
				comp->SetFieldData(fieldData);
				comp->ResetCurrentTime();
				//if (m_Field->GetField()[i].TextureComponent->GetFileName() != m_FileNameBackgroundTile && hasQbertComp)
				//{
				//	m_Field->GetField()[i].TextureComponent->SetTexture(m_FileNameBackgroundTile);
				//	//also give points
				//	int value{ 25 };
				//	getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
				//}		
				if (hasQbertComp)
				{
					if (m_Field->ChangeTileColor(i, true))
					{
						int value{ 25 };
						getActor()->GetComponent<dae::ScoreComponent>()->AddScore(value);
					}
				}
				else if (comp->GetGameObject()->HasComponent<SlickAndSam>())
				{
					m_Field->ChangeTileColor(i, false);
				}
				return;
			}
			else
			{
				std::cout << "Wait A little bit\n";
			}
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
		//start solo game
		auto& scene = dae::SceneManager::GetInstance().CreateScene("Solo");

		std::shared_ptr<dae::GameObject> obj = std::make_shared<dae::GameObject>();
		std::shared_ptr<Level> level = std::make_shared<Level>();
		level->LoadGameSolo(scene);
		obj->addComponent(level);
		scene.Add(obj);

		dae::SceneManager::GetInstance().SetActiveScene("Solo");
		break;
	}
	case InWhatButtonMainMenu::Coop:
	{
		//start coop game
		auto& scene = dae::SceneManager::GetInstance().CreateScene("Coop");

		std::shared_ptr<dae::GameObject> obj = std::make_shared<dae::GameObject>();
		std::shared_ptr<Level> level = std::make_shared<Level>();
		level->LoadGameCoop(scene);
		obj->addComponent(level);
		scene.Add(obj);

		dae::SceneManager::GetInstance().SetActiveScene("Coop");
		break;
	}
	case InWhatButtonMainMenu::Vs:
	{
		//start vs game
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

MouseClickGameMenus::MouseClickGameMenus(InWhatButtonGameMenu& clickHappened, std::shared_ptr<Menus> menus)
	:Command(nullptr)
	, m_InWhatButton(clickHappened)
	,m_Menus(menus)
{

}
void MouseClickGameMenus::Execute()
{
	switch (m_InWhatButton)
	{
	case InWhatButtonGameMenu::Play:
		//start solo game
		if (m_Menus->GetGameObject()->GetIsActive())
		{
			m_Menus->SetPauseScreenInActive();
			m_Menus->GetGameObject()->SetIsActive(false);
			GameTime::GetInstance().SetPaused(false);
		}

		break;
	case InWhatButtonGameMenu::Exit:
		//start coop game
		dae::InputManager::GetInstance().EndGame();
		break;
	case InWhatButtonGameMenu::None:
		break;
	default:
		break;
	}
}

PauseMenuCommand::PauseMenuCommand(std::shared_ptr<Menus> menus)
	:Command(nullptr)
	, m_Menus(menus)
{

}
void PauseMenuCommand::Execute()
{
	auto menuGameObject = m_Menus->GetGameObject();
	if (menuGameObject->GetIsActive())
	{
		m_Menus->SetPauseScreenInActive();
		menuGameObject->SetIsActive(false);
		GameTime::GetInstance().SetPaused(false);
	}
	else
	{
		m_Menus->SetPauseScreenActive();
		menuGameObject->SetIsActive(true);
		GameTime::GetInstance().SetPaused(true);
	}
}