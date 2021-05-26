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
			componentTexture->SetTexture("BackGroundTileRed.png");
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
//void PlayingField::Render()const
//{
//
//}

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