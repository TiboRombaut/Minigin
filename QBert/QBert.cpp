#include <SDL.h>
#undef main

#include <Minigin.h>
#include "Level.h"
#include <memory>
#include "SceneManager.h"
#include "Scene.h"
#include "MainMenuScene.h"
void LoadGame()
{

	auto& sceneMenu = dae::SceneManager::GetInstance().CreateScene("Menu");

	std::shared_ptr<dae::GameObject> objMenu = std::make_shared<dae::GameObject>();
	std::shared_ptr<MainMenuScene> menu = std::make_shared<MainMenuScene>();
	menu->LoadGame(sceneMenu);
	objMenu->addComponent(menu);
	sceneMenu.Add(objMenu);

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level");

	std::shared_ptr<dae::GameObject> obj = std::make_shared<dae::GameObject>();
	std::shared_ptr<Level> level = std::make_shared<Level>();
	level->LoadGame(scene);
	obj->addComponent(level);
	scene.Add(obj);

	dae::SceneManager::GetInstance().SetActiveScene("Level");
}

int main()
{
	dae::Minigin engine;
	engine.Run(LoadGame);
	return 0;
}