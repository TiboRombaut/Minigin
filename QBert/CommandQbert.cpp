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
#include <ServiceLocator.h>
#include <SceneManager.h>

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
		std::cout << "leftDown\n";
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
				//getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY);
				getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY));
				fieldData.Column = m_Field->GetField()[i].Column;
				fieldData.Row = m_Field->GetField()[i].Row;
				comp->SetFieldData(fieldData);
				comp->ResetCurrentTime();
			

				if (hasQbertComp)
				{
					dae::ServiceLocator::get_sound_system().Play(0, 1, "../Data/QbertHop.wav");

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
				return;
			}
		}
	}
	if (hasQbertComp)
	{
		if (comp->GetCanMove())
		{
			getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().x - m_Field->GetField()[0].TextureComponent->GetWidth(),
				getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().y + m_Field->GetField()[0].TextureComponent->GetHeight()));
			fieldData.Column = -1;
			fieldData.Row = -1;
			comp->SetFieldData(fieldData);
			comp->ResetCurrentTime();
			dae::ServiceLocator::get_sound_system().Play(0, 1, "../Data/QBertFall.wav");
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
		std::cout << "leftUp\n";
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
					else if (comp->GetGameObject()->HasComponent<Coily>())
					{
						std::cout << "coily dead";
					}
					return;
				}

				//move logic
				 getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY));
				//getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY);
				fieldData.Column = m_Field->GetField()[i].Column;
				fieldData.Row = m_Field->GetField()[i].Row;
				comp->SetFieldData(fieldData);
				comp->ResetCurrentTime();

				//changing tile Logic
				if (hasQbertComp)
				{
					dae::ServiceLocator::get_sound_system().Play(0, 1, "../Data/QbertHop.wav");
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
				return;
			}
		}
	}
	if (hasQbertComp)
	{
		if (comp->GetCanMove())
		{
			std::cout << "has reached end";
			getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().x + m_Field->GetField()[0].TextureComponent->GetWidth(),
				getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().y + m_Field->GetField()[0].TextureComponent->GetHeight()));
			fieldData.Column = -1;
			fieldData.Row = -1;
			comp->SetFieldData(fieldData);
			comp->ResetCurrentTime();
			dae::ServiceLocator::get_sound_system().Play(0, 1, "../Data/QBertFall.wav");
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
		std::cout << "leftUp\n";
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

						std::cout << "moving to color wheel";
						glm::vec2 sizeQbert{ getActor()->GetComponent<dae::TextureComponent>()->GetWidth(),getActor()->GetComponent<dae::TextureComponent>()->GetHeight() };
						getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(m_Field->GetField()[i].MiddlePosX - sizeQbert.x, m_Field->GetField()[i].MiddlePosY - sizeQbert.y));
						getActor()->GetComponent<QBertComponent>()->ColorWheelNeedsToMovetoTop(m_Field->GetField()[i].TextureComponent, glm::vec2(m_Field->GetField()[0].MiddlePosX, m_Field->GetField()[0].MiddlePosY));

						//getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[0].MiddlePosX, m_Field->GetField()[0].MiddlePosY);
						fieldData.Column = m_Field->GetField()[i].Column;
						fieldData.Row = m_Field->GetField()[i].Row;
						comp->SetFieldData(fieldData);
						comp->ResetCurrentTime();

						//getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[0].MiddlePosX, m_Field->GetField()[0].MiddlePosY);
						//fieldData.Column = m_Field->GetField()[0].Column;
						//fieldData.Row = m_Field->GetField()[0].Row;
						//comp->SetFieldData(fieldData);
						//m_Field->GetField()[i].TextureComponent->GetGameObject()->RemoveComponent(m_Field->GetField()[i].TextureComponent);
						//m_Field->GetField().erase(m_Field->GetField().begin() + i);
					}
					else if (comp->GetGameObject()->HasComponent<Coily>())
					{
						if (!getActor()->GetComponent<Coily>()->GetIsDead())
						{
							//std::cout << "dead";
							getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY));
							getActor()->GetComponent<Coily>()->SetIsDead(true);
							//getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY);
							//fieldData.Column = m_Field->GetField()[i].Column;
							//fieldData.Row = m_Field->GetField()[i].Row;
							dae::ServiceLocator::get_sound_system().Play(0, 1, "../Data/SnakeFall.wav");
						}
					}
					return;
				}
				std::cout << "moving to " << m_Field->GetField()[i].Row << " , " << m_Field->GetField()[i].Column << std::endl;
				std::cout << "moving to " << m_Field->GetField()[i].MiddlePosX << " , " << m_Field->GetField()[i].MiddlePosY << std::endl;
				getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY));
				//getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY);
				fieldData.Column = m_Field->GetField()[i].Column;
				fieldData.Row = m_Field->GetField()[i].Row;
				comp->SetFieldData(fieldData);
				comp->ResetCurrentTime();

				if (hasQbertComp)
				{
					std::cout << "moved to shit";
					dae::ServiceLocator::get_sound_system().Play(0, 1, "../Data/QbertHop.wav");
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
				return;
			}
		}
	}
	//if he gets here check whether he is Qbert then move away and respawn
	if (hasQbertComp)
	{
		if (comp->GetCanMove())
		{
			getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().x - m_Field->GetField()[0].TextureComponent->GetWidth(),
				getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().y - m_Field->GetField()[0].TextureComponent->GetHeight()));
			fieldData.Column = -1;
			fieldData.Row = -1;
			comp->SetFieldData(fieldData);
			comp->ResetCurrentTime();
			dae::ServiceLocator::get_sound_system().Play(0, 1, "../Data/QBertFall.wav");
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
		std::cout << "rightDown\n";
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
			if (m_Field->GetField()[i].TextureComponent->GetFileName() == "ColorWheel.png")
			{
				if (hasQbertComp)
				{
					glm::vec2 sizeQbert{ getActor()->GetComponent<dae::TextureComponent>()->GetWidth(),getActor()->GetComponent<dae::TextureComponent>()->GetHeight() };
					getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(m_Field->GetField()[i].MiddlePosX - sizeQbert.x, m_Field->GetField()[i].MiddlePosY - sizeQbert.y));
					getActor()->GetComponent<QBertComponent>()->ColorWheelNeedsToMovetoTop(m_Field->GetField()[i].TextureComponent, glm::vec2(m_Field->GetField()[0].MiddlePosX, m_Field->GetField()[0].MiddlePosY));

					//getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[0].MiddlePosX, m_Field->GetField()[0].MiddlePosY);
					fieldData.Column = m_Field->GetField()[i].Column;
					fieldData.Row = m_Field->GetField()[i].Row;
					comp->SetFieldData(fieldData);
					comp->ResetCurrentTime();

					//m_Field->GetField()[i].TextureComponent->SetIsActiveComponent(false);
					//m_Field->GetField()[i].TextureComponent->GetGameObject()->RemoveComponent(m_Field->GetField()[i].TextureComponent);
					//m_Field->GetField().erase(m_Field->GetField().begin() + i);
				}
				else if (comp->GetGameObject()->HasComponent<Coily>())
				{
					if (!getActor()->GetComponent<Coily>()->GetIsDead())
					{
						//std::cout << "dead";
						getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY));
						getActor()->GetComponent<Coily>()->SetIsDead(true);
						//getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY);
						//fieldData.Column = m_Field->GetField()[i].Column;
						//fieldData.Row = m_Field->GetField()[i].Row;
						dae::ServiceLocator::get_sound_system().Play(0, 1.0f, "../Data/SnakeFall.wav");
					}
				}
				return;
			}
			getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY));
			//getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field->GetField()[i].MiddlePosX, m_Field->GetField()[i].MiddlePosY);
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
				dae::ServiceLocator::get_sound_system().Play(0, 1, "../Data/QbertHop.wav");
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
			return;
		}
	}
	}
	if (hasQbertComp)
	{
		if (comp->GetCanMove())
		{
			getActor()->GetComponent<ControlComponent>()->SetMoveToTarget(glm::vec2(getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().x + m_Field->GetField()[0].TextureComponent->GetWidth(),
				getActor()->GetComponent<dae::TextureComponent>()->GetTransform().GetPosition().y - m_Field->GetField()[0].TextureComponent->GetHeight()));
			fieldData.Column = -1;
			fieldData.Row = -1;
			comp->SetFieldData(fieldData);
			comp->ResetCurrentTime();
			dae::ServiceLocator::get_sound_system().Play(0, 1, "../Data/QBertFall.wav");
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
			//start coop game
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
	{
		if (dae::SceneManager::GetInstance().GetActiveScene()->GetName() != "Menu")
		{
			if (GameTime::GetInstance().GetPaused())
			{
				if (m_Menus->GetGameObject()->GetIsActive())
				{
					m_Menus->SetPauseScreenInActive();
					m_Menus->GetGameObject()->SetIsActive(false);
					GameTime::GetInstance().SetPaused(false);
				}
			}
		}


	}
	break;
	case InWhatButtonGameMenu::MainMenu:
		std::cout << "mainmenu";
		if (dae::SceneManager::GetInstance().GetActiveScene()->GetName() != "Menu")
		{
			if (GameTime::GetInstance().GetPaused())
			{
				std::cout << "delete scene";
				dae::SceneManager::GetInstance().DeleteScene(dae::SceneManager::GetInstance().GetActiveScene()->GetName());
				dae::SceneManager::GetInstance().SetActiveScene("Menu");
				GameTime::GetInstance().SetPaused(false);
			}
		}
		break;

	case InWhatButtonGameMenu::Restart:
	{
		std::cout << "restart";
		std::string nameScene = dae::SceneManager::GetInstance().GetActiveScene()->GetName();
		if (nameScene != "Menu")
		{
			if (GameTime::GetInstance().GetPaused())
			{
				dae::SceneManager::GetInstance().DeleteScene(nameScene);

				if (nameScene == "Solo" || nameScene == "solo")
				{
					//start solo game
					std::cout << "createSOlo\n";
					auto& scene = dae::SceneManager::GetInstance().CreateScene("Solo");

					std::shared_ptr<dae::GameObject> obj = std::make_shared<dae::GameObject>();
					std::shared_ptr<Level> level = std::make_shared<Level>();
					level->LoadGameSolo(scene);
					obj->addComponent(level);
					scene.Add(obj);
					GameTime::GetInstance().SetPaused(false);
					dae::SceneManager::GetInstance().SetActiveScene("Solo");
				}
				else if (nameScene == "Coop" || nameScene == "coop")
				{
					auto& scene = dae::SceneManager::GetInstance().CreateScene("Coop");

					std::shared_ptr<dae::GameObject> obj = std::make_shared<dae::GameObject>();
					std::shared_ptr<Level> level = std::make_shared<Level>();
					level->LoadGameCoop(scene);
					obj->addComponent(level);
					scene.Add(obj);
					GameTime::GetInstance().SetPaused(false);

					dae::SceneManager::GetInstance().SetActiveScene("Coop");
				}
				else if (nameScene == "Vs" || nameScene == "vs")
				{
					auto& scene = dae::SceneManager::GetInstance().CreateScene("Vs");

					std::shared_ptr<dae::GameObject> obj = std::make_shared<dae::GameObject>();
					std::shared_ptr<Level> level = std::make_shared<Level>();
					level->LoadGameVs(scene);
					obj->addComponent(level);
					scene.Add(obj);
					GameTime::GetInstance().SetPaused(false);

					dae::SceneManager::GetInstance().SetActiveScene("Vs");
				}
			}
		}
		break;
	}
	case InWhatButtonGameMenu::Exit:
		std::cout << "exit";
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