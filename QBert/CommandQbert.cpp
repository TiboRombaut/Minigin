#include "CommandQbert.h"
#include "QBertComponent.h"
#include "AIComponent.h"
//#include <TextureComponent.h>
#include <iostream>
MoveLeftDownCommand::MoveLeftDownCommand(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field, std::string fileNamePath)
	:Command(pObject)
	, m_Field(field)
	,m_FileNameBackgroundTile(fileNamePath)
{

}

void MoveLeftDownCommand::Execute()
{
	auto comp = getActor()->GetComponent<QBertComponent>();
	auto fieldData = comp->GetFieldData();

	for (size_t i = 0; i < m_Field.size(); i++)
	{
		if (m_Field[i].Row == fieldData.Row + 1 && m_Field[i].Column == fieldData.Column)
		{
			if (getActor()->GetComponent<QBertComponent>()->GetCanMove())
			{
				if (m_Field[i].TextureComponent->GetFileName() == "ColorWheel.png")
				{
					getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field[0].MiddlePosX, m_Field[0].MiddlePosY);
					fieldData.Column = m_Field[0].Column;
					fieldData.Row = m_Field[0].Row;
					comp->SetFieldData(fieldData);
					m_Field[i].TextureComponent->GetGameObject()->RemoveComponent(m_Field[i].TextureComponent);
					m_Field.erase(m_Field.begin() + i);
					return;
				}
				getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field[i].MiddlePosX, m_Field[i].MiddlePosY);
				fieldData.Column = m_Field[i].Column;
				fieldData.Row = m_Field[i].Row;
				comp->SetFieldData(fieldData);
				if (m_Field[i].TextureComponent->GetFileName() != m_FileNameBackgroundTile)
				{
					m_Field[i].TextureComponent->SetTexture(m_FileNameBackgroundTile);
					//also give points
					std::cout << "change tile";

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

MoveRightDownCommand::MoveRightDownCommand(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field, std::string fileNamePath)
	:Command(pObject)
	, m_Field(field)
	, m_FileNameBackgroundTile(fileNamePath)
{

}

void MoveRightDownCommand::Execute()
{
	auto comp = getActor()->GetComponent<QBertComponent>();
	auto fieldData = comp->GetFieldData();

	for (size_t i = 0; i < m_Field.size(); i++)
	{
		if (m_Field[i].Row == fieldData.Row + 1 && m_Field[i].Column == fieldData.Column+1)
		{
			if (getActor()->GetComponent<QBertComponent>()->GetCanMove())
			{
				if (m_Field[i].TextureComponent->GetFileName() == "ColorWheel.png")
				{
					getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field[0].MiddlePosX, m_Field[0].MiddlePosY);
					fieldData.Column = m_Field[0].Column;
					fieldData.Row = m_Field[0].Row;
					comp->SetFieldData(fieldData);
					m_Field[i].TextureComponent->GetGameObject()->RemoveComponent(m_Field[i].TextureComponent);
					m_Field.erase(m_Field.begin() + i);
					return;
				}
				getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field[i].MiddlePosX, m_Field[i].MiddlePosY);
				fieldData.Column = m_Field[i].Column;
				fieldData.Row = m_Field[i].Row;
				comp->SetFieldData(fieldData);
				if (m_Field[i].TextureComponent->GetFileName() != m_FileNameBackgroundTile)
				{
					m_Field[i].TextureComponent->SetTexture(m_FileNameBackgroundTile);
					//also give points
					std::cout << "change tile";

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

MoveLeftUpCommand::MoveLeftUpCommand(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field, std::string fileNamePath)
	:Command(pObject)
	, m_Field(field)
	, m_FileNameBackgroundTile(fileNamePath)
{

}
MoveLeftUpCommand::MoveLeftUpCommand(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field)
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
		std::cout << "hasQbert";
	}
	else if (getActor()->HasComponent<AIComponent>())
	{
		comp = getActor()->GetComponent<AIComponent>();
	}
	else
	{
		return;
	}
	auto fieldData = comp->GetFieldData();

	for (size_t i = 0; i < m_Field.size(); i++)
	{
		if (m_Field[i].Row == fieldData.Row - 1 && m_Field[i].Column == fieldData.Column-1)
		{
			if (comp->GetCanMove())
			{
				if (m_Field[i].TextureComponent->GetFileName() == "ColorWheel.png"&&hasQbertComp)
				{
					getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field[0].MiddlePosX, m_Field[0].MiddlePosY);
					fieldData.Column = m_Field[0].Column;
					fieldData.Row = m_Field[0].Row;
					comp->SetFieldData(fieldData);
					m_Field[i].TextureComponent->GetGameObject()->RemoveComponent(m_Field[i].TextureComponent);
					m_Field.erase(m_Field.begin() + i);
					return;
				}
				getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field[i].MiddlePosX, m_Field[i].MiddlePosY);
				fieldData.Column = m_Field[i].Column;
				fieldData.Row = m_Field[i].Row;
				comp->SetFieldData(fieldData);
				comp->ResetCurrentTime();

				if (m_Field[i].TextureComponent->GetFileName() != m_FileNameBackgroundTile && hasQbertComp)
				{
					m_Field[i].TextureComponent->SetTexture(m_FileNameBackgroundTile);
					//also give points
					std::cout << "change tile";

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

MoveRightUpCommand::MoveRightUpCommand(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field, std::string fileNamePath)
	:Command(pObject)
	, m_Field(field)
	, m_FileNameBackgroundTile(fileNamePath)
{

}

MoveRightUpCommand::MoveRightUpCommand(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field)
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

	auto fieldData = comp->GetFieldData();

	for (size_t i = 0; i < m_Field.size(); i++)
	{
		if (m_Field[i].Row == fieldData.Row - 1 && m_Field[i].Column == fieldData.Column)
		{
			if (comp->GetCanMove())
			{
				if (m_Field[i].TextureComponent->GetFileName() == "ColorWheel.png" && hasQbertComp)
				{
					getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field[0].MiddlePosX, m_Field[0].MiddlePosY);
					fieldData.Column = m_Field[0].Column;
					fieldData.Row = m_Field[0].Row;
					comp->SetFieldData(fieldData);
					m_Field[i].TextureComponent->GetGameObject()->RemoveComponent(m_Field[i].TextureComponent);
					m_Field.erase(m_Field.begin() + i);
					return;
				}

				getActor()->GetComponent<dae::TextureComponent>()->SetPosition(m_Field[i].MiddlePosX, m_Field[i].MiddlePosY);
				fieldData.Column = m_Field[i].Column;
				fieldData.Row = m_Field[i].Row;
				comp->SetFieldData(fieldData);
				comp->ResetCurrentTime();
				if (m_Field[i].TextureComponent->GetFileName() != m_FileNameBackgroundTile && hasQbertComp)
				{
					m_Field[i].TextureComponent->SetTexture(m_FileNameBackgroundTile);
					//also give points
					std::cout << "change tile";

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