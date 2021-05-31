#include "PlayingField.h"
#include <TextureComponent.h>
#include <iostream>
PlayingField::PlayingField(float widthStartPos, float HeightStartPos, std::shared_ptr<dae::GameObject> field)
{

	//float widthStartPos = 250;
	//float HeightStartPos = 200;
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
				std::shared_ptr<dae::TextureComponent> componentTextureColorWheel{ std::make_shared<dae::TextureComponent>() };
				componentTextureColorWheel->SetTexture("ColorWheel.png");
				float posXColorWheel = widthStartPos - (textureWidth / 3);

				componentTextureColorWheel->SetPosition(posXColorWheel, HeightStartPos - textureHeight / 3);
				FieldData currentDataColorWheel;
				currentDataColorWheel.Row = row - 1;
				currentDataColorWheel.Column = column - 1;
				currentDataColorWheel.MiddlePosX = posXColorWheel + textureWidth / 4;
				currentDataColorWheel.MiddlePosY = HeightStartPos;
				currentDataColorWheel.TextureComponent = componentTextureColorWheel;

				m_Field.push_back(currentDataColorWheel);
				field->addComponent(componentTextureColorWheel);
			}
			else if (row == 4 && column == temp - 1)
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
				currentDataColorWheel.TextureComponent = componentTextureColorWheel;

				m_Field.push_back(currentDataColorWheel);
				field->addComponent(componentTextureColorWheel);
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
			currentData.TextureComponent = componentTexture;

			m_Field.push_back(currentData);
			field->addComponent(componentTexture);
		}
		widthStartPos -= textureWidth / 2;
		HeightStartPos += textureHeight / 4 * 3;
	}
	m_BottomLeftIndex = m_Field.size() - 7;
}
std::vector<FieldData> PlayingField::GetField()const
{
	return m_Field;
}

bool  PlayingField::ChangeTileLevel1(int whatTile, int isQBert)
{
	if (m_Field[whatTile].TextureComponent->GetFileName() == m_FirstTileName && isQBert)
	{
		m_Field[whatTile].TextureComponent->SetTexture(m_SecondTileName);
		return true;
	}
	else if (!isQBert)
	{
		if (m_Field[whatTile].TextureComponent->GetFileName() == m_SecondTileName)
		{
			m_Field[whatTile].TextureComponent->SetTexture(m_FirstTileName);
		}
		else if (m_Field[whatTile].TextureComponent->GetFileName() == m_ThirthTileName)
		{
			m_Field[whatTile].TextureComponent->SetTexture(m_SecondTileName);
		}
		return false;
	}
	return false;
}

bool  PlayingField::ChangeTileLevel2(int whatTile, int isQBert)
{
	if (m_Field[whatTile].TextureComponent->GetFileName() == m_FirstTileName  && isQBert)
	{
		m_Field[whatTile].TextureComponent->SetTexture(m_SecondTileName);
		return true;
	}
	else if (m_Field[whatTile].TextureComponent->GetFileName() == m_SecondTileName && isQBert)
	{
		m_Field[whatTile].TextureComponent->SetTexture(m_ThirthTileName);
		return true;
	}
	else if (!isQBert)
	{
		if (m_Field[whatTile].TextureComponent->GetFileName() == m_SecondTileName)
		{
			m_Field[whatTile].TextureComponent->SetTexture(m_FirstTileName);
		}
		else if (m_Field[whatTile].TextureComponent->GetFileName() == m_ThirthTileName)
		{
			m_Field[whatTile].TextureComponent->SetTexture(m_SecondTileName);
		}
		return false;
	}
	return false;
}

bool  PlayingField::ChangeTileLevel3(int whatTile, int isQBert)
{
	if (m_Field[whatTile].TextureComponent->GetFileName() == m_FirstTileName && isQBert)
	{
		m_Field[whatTile].TextureComponent->SetTexture(m_SecondTileName);
		return true;
	}
	else if (m_Field[whatTile].TextureComponent->GetFileName() == m_SecondTileName && isQBert)
	{
		m_Field[whatTile].TextureComponent->SetTexture(m_FirstTileName);
		return false;
	}
	else if (!isQBert)
	{
		if (m_Field[whatTile].TextureComponent->GetFileName() == m_SecondTileName)
		{
			m_Field[whatTile].TextureComponent->SetTexture(m_FirstTileName);
		}
		else if (m_Field[whatTile].TextureComponent->GetFileName() == m_ThirthTileName)
		{
			m_Field[whatTile].TextureComponent->SetTexture(m_SecondTileName);
		}
		return false;
	}
	return false;
}

bool PlayingField::ChangeTileColor(int whatTile, bool isQBert)
{
	bool result{ false };
	switch (m_CurrentLevel)
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
	case 3:
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
		if (m_Field[i].TextureComponent->GetFileName() != "ColorWheel.png")
		{
			m_Field[i].TextureComponent->SetTexture(m_FirstTileName);
		}
	}
	m_LevelIsResetted = true;
}

bool PlayingField::LevelFinished(std::string goalName)
{
	for (size_t i = 0; i < m_Field.size(); ++i)
	{
		if (m_Field[i].TextureComponent->GetFileName() != "ColorWheel.png")
		{
			if (m_Field[i].TextureComponent->GetFileName() != goalName)
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
	return true;
}


FieldData PlayingField::GetPlayerFieldDataFirst()const
{
	//return FieldDataPlayer{ m_Field[0].Row,m_Field[0].Column };
	return m_Field[0];
}

FieldData PlayingField::GetPlayerFieldDataLast()const
{
	//return FieldDataPlayer{ m_Field[0].Row,m_Field[0].Column };
	return m_Field[m_Field.size()-1];
}

FieldData PlayingField::GetFieldDataLeftBottom()const
{
	//return FieldDataPlayer{ m_Field[0].Row,m_Field[0].Column };
	return m_Field[m_BottomLeftIndex];
}

void PlayingField::Update()
{
}

//float widthStartPos = 250;
//float HeightStartPos = 200;
//float textureWidth = 0;
//float textureHeight = 0;
//for (int row = 0; row < 7; ++row)
//{
//	//The row we are on determines how many colums we have
//	int temp = row + 1;
//	for (int column = 0; column < temp; ++column)
//	{
//		if (row == 4 && column == 0)
//		{
//			std::shared_ptr<dae::TextureComponent> componentTextureColorWheel{ std::make_shared<dae::TextureComponent>() };
//			componentTextureColorWheel->SetTexture("ColorWheel.png");
//			float posXColorWheel = widthStartPos - (textureWidth / 3);
//
//			componentTextureColorWheel->SetPosition(posXColorWheel, HeightStartPos - textureHeight / 3);
//			FieldData currentDataColorWheel;
//			currentDataColorWheel.Row = row - 1;
//			currentDataColorWheel.Column = column - 1;
//			currentDataColorWheel.MiddlePosX = posXColorWheel + textureWidth / 4;
//			currentDataColorWheel.MiddlePosY = HeightStartPos;
//			currentDataColorWheel.TextureComponent = componentTextureColorWheel;
//
//			m_Field.push_back(currentDataColorWheel);
//			go->addComponent(componentTextureColorWheel);
//		}
//		else if (row == 4 && column == temp - 1)
//		{
//			std::shared_ptr<dae::TextureComponent> componentTextureColorWheel{ std::make_shared<dae::TextureComponent>() };
//			componentTextureColorWheel->SetTexture("ColorWheel.png");
//			float posXColorWheel = widthStartPos + (column * textureWidth) + textureWidth;
//
//			componentTextureColorWheel->SetPosition(posXColorWheel, HeightStartPos - textureHeight / 3);
//			FieldData currentDataColorWheel;
//			currentDataColorWheel.Row = row - 1;
//			currentDataColorWheel.Column = column;
//			currentDataColorWheel.MiddlePosX = posXColorWheel + textureWidth / 4;
//			currentDataColorWheel.MiddlePosY = HeightStartPos;
//			currentDataColorWheel.TextureComponent = componentTextureColorWheel;
//
//			m_Field.push_back(currentDataColorWheel);
//			go->addComponent(componentTextureColorWheel);
//		}
//
//		std::shared_ptr<dae::TextureComponent> componentTexture{ std::make_shared<dae::TextureComponent>() };
//		componentTexture->SetTexture("BackGroundTileRed.png");
//		if (row == 0)
//		{
//			textureWidth = float(componentTexture->GetWidth());
//			textureHeight = float(componentTexture->GetHeight());
//		}
//
//
//		float posX = widthStartPos + (column * textureWidth);
//
//		componentTexture->SetPosition(posX, HeightStartPos);
//		FieldData currentData;
//		currentData.Row = row;
//		currentData.Column = column;
//		currentData.MiddlePosX = posX + textureWidth / 4;
//		currentData.MiddlePosY = HeightStartPos;
//		currentData.TextureComponent = componentTexture;
//
//		m_Field.push_back(currentData);
//		go->addComponent(componentTexture);
//	}
//	widthStartPos -= textureWidth / 2;
//	HeightStartPos += textureHeight / 4 * 3;
//}