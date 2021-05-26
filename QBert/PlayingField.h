#pragma once
#include <BaseComponent.h>
#include "Structs.h"
#include <vector>
#include <memory>
#include "GameObject.h"
#include <string>
class PlayingField : public dae::BaseComponent
{
public:
	PlayingField(float widthStartPos,float heightStartPos,std::shared_ptr<dae::GameObject> field);
	//PlayingField(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field);

	void Update();
	void Render() const {};

	std::vector<FieldData> GetField()const;
	FieldData GetPlayerFieldDataFirst()const;
	FieldData GetPlayerFieldDataLast()const;
	FieldData GetFieldDataLeftBottom()const;

	std::string GetFirstTileName()const
	{
		return "../Data/BackGroundTileRed.png";
	}
	std::string GetSecondTileName()const
	{
		return "../Data/BackGroundTileYellow.png";
	}
	std::string GetThirthTileName()const
	{
		return "../Data/BackGroundTileBlue.png";
	}
	//FieldDataPlayer GetFieldData()const;
	//void SetFieldData(FieldDataPlayer data);
	//bool GetCanMove();
	~PlayingField() = default;
	PlayingField(const PlayingField& other) = delete;
	PlayingField(PlayingField&& other) = delete;
	PlayingField& operator=(const PlayingField& other) = delete;
	PlayingField& operator=(PlayingField&& other) = delete;
private:
	std::vector<FieldData> m_Field;
	int m_BottomLeftIndex = 0;
};

