#include <SDL.h>
#undef main

#include <Minigin.h>
#include "Level.h"
#include <memory>
#include "SceneManager.h"
#include "Scene.h"
void LoadGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level");

	std::shared_ptr<dae::GameObject> obj = std::make_shared<dae::GameObject>();
	std::shared_ptr<Level> level = std::make_shared<Level>();
	level->LoadGame(scene);
	obj->addComponent(level);
	scene.Add(obj);
}

int main()
{
	dae::Minigin engine;
	engine.Run(LoadGame);
	return 0;
}