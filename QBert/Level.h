#pragma once
#include "BaseComponent.h"
#include <Scene.h>
#include "QBertComponent.h"
#include "AIComponent.h"
#include "PlayingField.h"
#include "Menus.h"
#include <Font.h>
class Level : public dae::BaseComponent
{
public:
	Level();

	void LoadGameSolo(dae::Scene& currentScene);
	void LoadGameCoop(dae::Scene& currentScene);
	void LoadGameVs(dae::Scene& currentScene);

	void Update();
	void Render() const {};

	~Level() = default;
	Level(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) = delete;
private:
	void LoadGame(dae::Scene& currentScene,std::shared_ptr<dae::Font> font);
	void LoadMenus(dae::Scene& currentScene);

	int m_CurrentLevel = 1;
	std::shared_ptr<Menus> m_pMenusComp;
	std::vector<std::shared_ptr<AIComponent>> m_pEnemies;
	std::vector < std::shared_ptr<QBertComponent>> m_pQBerts;
	std::shared_ptr<PlayingField> m_PlayingField;
	float m_CurrentRespawnTimer = 0.0f;
	float m_MaxRespawnTimer = 5.0f;
};

