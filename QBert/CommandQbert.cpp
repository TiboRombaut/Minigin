#include "CommandQbert.h"
#include "QBertComponent.h"
#include "AIComponent.h"
//#include <TextureComponent.h>
#include "ScoreComponent.h"
#include <iostream>
#include "SlickAndSam.h"
MoveLeftDownCommand::MoveLeftDownCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field, std::string fileNamePath)
	:Command(pObject)
	, m_Field(field)
	,m_FileNameBackgroundTile(fileNamePath)
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