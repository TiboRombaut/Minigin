#pragma once
#include "BaseComponent.h"
#include <Scene.h>
#include "QBertComponent.h"
#include "AIComponent.h"
#include "PlayingField.h"
#include "Menus.h"
class Level : public dae::BaseComponent
{
public:
	Level();

	void LoadGame(dae::Scene& currentScene);

	void Update();
	void Render() const {};

	~Level() = default;
	Level(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) = delete;
private:
	int m_CurrentLevel = 1;
	std::shared_ptr<Menus> m_pMenusComp;
	std::vector<std::shared_ptr<AIComponent>> m_pEnemies;
	std::shared_ptr<QBertComponent> m_pQBert;
	std::shared_ptr<PlayingField> m_PlayingField;
	float m_CurrentRespawnTimer = 0.0f;
	float m_MaxRespawnTimer = 5.0f;
};

