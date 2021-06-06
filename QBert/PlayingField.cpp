#include "PlayingField.h"
#include <TextureComponent.h>
#include <iostream>
#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 33010)
#pragma warning(disable: 26812)
#pragma warning(disable: 26451)
#include <rapidjson.h>
#include <document.h>
#include <stream.h>
#include <filereadstream.h>
#pragma warning(pop)

using rapidjson::Value;

PlayingField::PlayingField(std::shared_ptr<dae::GameObject> pField, std::shared_ptr<dae::TextureComponent> pGoalComp)
{
	std::wstring fileName = L"../Data/PlayingFieldLayout.json";
	rapidjson::Document jsonDocumentQbert;
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, fileName.c_str(), L"rb");

	if (pFile != nullptr)
	{

		fseek(pFile, 0, SEEK_END);
		const size_t size = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);
		char* readBuffer = new char[size];
		rapidjson::FileReadStream inputStream(pFile, readBuffer, sizeof(readBuffer));
		jsonDocumentQbert.ParseStream(inputStream);
		delete[] readBuffer;
		fclose(pFile);

	}

	const Value& rows = jsonDocumentQbert["Rows"];
	const Value& colorWheelRow = jsonDocumentQbert["ColorWheelRow"];
	const Value& startingPosX = jsonDocumentQbert["StartingPosX"];
	const Value& startingPosY = jsonDocumentQbert["StartingPosY"];
	const Value& firstTile = jsonDocumentQbert["FirstTile"];
	const Value& secondTile = jsonDocumentQbert["SecondTile"];
	const Value& thirthTile = jsonDocumentQbert["ThirthTile"];

	m_FirstTileName = firstTile.GetString();
	m_SecondTileName = secondTile.GetString();
	m_ThirthTileName = thirthTile.GetString();

	m_pTextureCompGoalIndication = pGoalComp;
	m_pTextureCompGoalIndication->SetTexture(m_SecondTileName);

	float widthStartPos = startingPosX.GetFloat();
	float HeightStartPos = startingPosY.GetFloat();
	float textureWidth = 0;
	float textureHeight = 0;
	for (int row = 0; row < rows.GetInt(); ++row)
	{
		int temp = row + 1;
		for (int column = 0; column < temp; ++column)
		{
			if (row == colorWheelRow && column == 0)
			{
				std::shared_ptr<dae::TextureComponent> componentTextureColorWheel{ std::make_shared<dae::TextureComponent>() };
				componentTextureColorWheel->SetTexture("ColorWheel.png");
				float posXColorWheel = widthStartPos - (textureWidth / 3);

				componentTextureColorWheel->SetPosition(posXColorWheel, HeightStartPos - textureHeight / 3);
				FieldData currentDataColorWheel;
				currentDataColorWheel.Row = row - 1;
				currentDataColorWheel.Column = column - 1;
				currentDataColorWheel.MiddlePosX = posXColorWheel + textureWidth / 4;
				currentDataColorWheel.MiddlePosY = HeightStartPos;
				currentDataColorWheel.pTextureComponent = componentTextureColorWheel;

				m_Field.push_back(currentDataColorWheel);
				pField->addComponent(componentTextureColorWheel);
			}
			else if (row == colorWheelRow && column == temp - 1)
			{
				std::shared_ptr<dae::TextureComponent> componentTextureColorWheel{ std::make_shared<dae::TextureComponent>() };
				componentTextureColorWheel->SetTexture("ColorWheel.png");
				float posXColorWheel = widthStartPos + (column * textureWidth) + textureWidth;

				componentTextureColorWheel->SetPosition(posXColorWheel, HeightStartPos - textureHeight / 3);
				FieldData currentDataColorWheel;
				currentDataColorWheel.Row = row - 1;
				currentDataColorWheel.Column = column;
				currentDataColorWheel.MiddlePosX = posXColorWheel + textureWidth / 4;
				currentDataColorWheel.MiddlePosY = HeightStartPos;
				currentDataColorWheel.pTextureComponent = componentTextureColorWheel;

				m_Field.push_back(currentDataColorWheel);
				pField->addComponent(componentTextureColorWheel);
			}

			std::shared_ptr<dae::TextureComponent> componentTexture{ std::make_shared<dae::TextureComponent>() };
			componentTexture->SetTexture("../Data/BackGroundTileRed.png");
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
			currentData.pTextureComponent = componentTexture;

			m_Field.push_back(currentData);
			pField->addComponent(componentTexture);
		}
		widthStartPos -= textureWidth / 2;
		HeightStartPos += textureHeight / 4 * 3;
	}
	m_BottomLeftIndex = int(m_Field.size()) - 7;
}

std::vector<FieldData> PlayingField::GetField()const
{
	return m_Field;
}

bool  PlayingField::ChangeTileLevel1(int whatTile, int isQBert)
{
	if (m_Field[whatTile].pTextureComponent->GetFileName() == m_FirstTileName && isQBert)
	{
		m_Field[whatTile].pTextureComponent->SetTexture(m_SecondTileName);
		return true;
	}
	else if (!isQBert)
	{
		if (m_Field[whatTile].pTextureComponent->GetFileName() == m_SecondTileName)
		{
			m_Field[whatTile].pTextureComponent->SetTexture(m_FirstTileName);
		}
		else if (m_Field[whatTile].pTextureComponent->GetFileName() == m_ThirthTileName)
		{
			m_Field[whatTile].pTextureComponent->SetTexture(m_SecondTileName);
		}
		return false;
	}
	return false;
}

bool  PlayingField::ChangeTileLevel2(int whatTile, int isQBert)
{
	if (m_Field[whatTile].pTextureComponent->GetFileName() == m_FirstTileName  && isQBert)
	{
		m_Field[whatTile].pTextureComponent->SetTexture(m_SecondTileName);
		return true;
	}
	else if (m_Field[whatTile].pTextureComponent->GetFileName() == m_SecondTileName && isQBert)
	{
		m_Field[whatTile].pTextureComponent->SetTexture(m_ThirthTileName);
		return true;
	}
	else if (!isQBert)
	{
		if (m_Field[whatTile].pTextureComponent->GetFileName() == m_SecondTileName)
		{
			m_Field[whatTile].pTextureComponent->SetTexture(m_FirstTileName);
		}
		else if (m_Field[whatTile].pTextureComponent->GetFileName() == m_ThirthTileName)
		{
			m_Field[whatTile].pTextureComponent->SetTexture(m_SecondTileName);
		}
		return false;
	}
	return false;
}

bool  PlayingField::ChangeTileLevel3(int whatTile, int isQBert)
{
	if (m_Field[whatTile].pTextureComponent->GetFileName() == m_FirstTileName && isQBert)
	{
		m_Field[whatTile].pTextureComponent->SetTexture(m_SecondTileName);
		return true;
	}
	else if (m_Field[whatTile].pTextureComponent->GetFileName() == m_SecondTileName && isQBert)
	{
		m_Field[whatTile].pTextureComponent->SetTexture(m_FirstTileName);
		return false;
	}
	else if (!isQBert)
	{
		if (m_Field[whatTile].pTextureComponent->GetFileName() == m_SecondTileName)
		{
			m_Field[whatTile].pTextureComponent->SetTexture(m_FirstTileName);
		}
		else if (m_Field[whatTile].pTextureComponent->GetFileName() == m_ThirthTileName)
		{
			m_Field[whatTile].pTextureComponent->SetTexture(m_SecondTileName);
		}
		return false;
	}
	return false;
}

bool PlayingField::ChangeTileColor(int whatTile, bool isQBert)
{
	bool result{ false };
	//level 1 = 2
	//level 2 = 1
	//level 3 = 0
	int currentLevel{ m_CurrentLevel % 3 };
	switch (currentLevel)
	{
	case 1:
		result = ChangeTileLevel1(whatTile, isQBert);
		LevelFinished(m_SecondTileName);
		return result;
		break;
	case 2:
		result = ChangeTileLevel2(whatTile, isQBert);
		LevelFinished(m_ThirthTileName);
		return result;
		break;
	case 0:
		result = ChangeTileLevel3(whatTile, isQBert);
		LevelFinished(m_SecondTileName);
		return result;
		break;
	}
	return false;
}

bool PlayingField::GetLevelIsResetted()const
{
	return m_LevelIsResetted;
}

void PlayingField::SetLevelIsResetted(bool resetLevel)
{
	m_LevelIsResetted = resetLevel;
}

bool PlayingField::GetColorWheelsRemaining()const
{
	return m_ColorWheelsRemaining;
}

void PlayingField::ResetColorWheelsRemaining()
{
	m_ColorWheelsRemaining = 0;
}

void PlayingField::ResetLevel()
{
	for (size_t i = 0; i < m_Field.size(); ++i)
	{
		//respawn colorwheels insert save there positions
		if (m_Field[i].pTextureComponent->GetFileName() != "ColorWheel.png")
		{
			m_Field[i].pTextureComponent->SetTexture(m_FirstTileName);
		}
		else
		{
			m_Field[i].pTextureComponent->SetIsActiveComponent(true);
			m_Field[i].pTextureComponent->SetPosition(m_Field[i].MiddlePosX - m_Field[i].pTextureComponent->GetWidth()/2, m_Field[i].MiddlePosY - m_Field[i].pTextureComponent->GetWidth() / 2);
		}
	}
	m_LevelIsResetted = true;

}

bool PlayingField::LevelFinished(std::string goalName)
{
	for (size_t i = 0; i < m_Field.size(); ++i)
	{
		if (m_Field[i].pTextureComponent->GetFileName() != "ColorWheel.png")
		{
			if (m_Field[i].pTextureComponent->GetFileName() != goalName)
			{
				return false;
			}
		}
		else
		{
			m_ColorWheelsRemaining++;
		}
	}
	ResetLevel();
	m_CurrentLevel++;

	int currentLevel = m_CurrentLevel % 3;
	switch (currentLevel)
	{
	case 1:
		m_pTextureCompGoalIndication->SetTexture(m_SecondTileName);
		break;
	case 2:
		m_pTextureCompGoalIndication->SetTexture(m_ThirthTileName);
		break;
	case 0:
		m_pTextureCompGoalIndication->SetTexture(m_SecondTileName);
		break;
	}
	return true;
}

FieldData PlayingField::GetFieldDataFirst()const
{
	return m_Field[0];
}

FieldData PlayingField::GetFieldDataLast()const
{
	return m_Field[m_Field.size()-1];
}

FieldData PlayingField::GetFieldDataLeftBottom()const
{
	return m_Field[m_BottomLeftIndex];
}

void PlayingField::Update()
{
}