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

	bool ChangeTileColor(int whatTile, bool isQBert);

	std::string GetFirstTileName()const
	{
		return m_FirstTileName;
	}
	std::string GetSecondTileName()const
	{
		return m_SecondTileName;
	}
	std::string GetThirthTileName()const
	{
		return m_ThirthTileName;
	}
	//FieldDataPlayer GetFieldData()const;
	//void SetFieldData(FieldDataPlayer data);
	//bool GetCanMove();

	bool GetLevelIsResetted()const;
	bool GetColorWheelsRemaining()const;
	void SetLevelIsResetted(bool resetLevel);
	void ResetColorWheelsRemaining();

	~PlayingField() = default;
	PlayingField(const PlayingField& other) = delete;
	PlayingField(PlayingField&& other) = delete;
	PlayingField& operator=(const PlayingField& other) = delete;
	PlayingField& operator=(PlayingField&& other) = delete;
private:
	bool ChangeTileLevel1(int whatTile, int isQBert);
	bool ChangeTileLevel2(int whatTile, int isQBert);
	bool ChangeTileLevel3(int whatTile, int isQBert);
	bool LevelFinished(std::string goalName);

	void ResetLevel();

	bool m_LevelIsResetted = false;
	std::vector<FieldData> m_Field;
	
	int m_BottomLeftIndex = 0;
	int m_CurrentLevel = 1;
	int m_ColorWheelsRemaining = 0;
	std::string m_FirstTileName = "../Data/BackGroundTileRed.png";
	std::string m_SecondTileName = "../Data/BackGroundTileYellow.png";
	std::string m_ThirthTileName = "../Data/BackGroundTileBlue.png";
};

