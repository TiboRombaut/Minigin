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


}

int main()
{
	dae::Minigin engine;
	engine.Run(LoadGame);
	return 0;
}