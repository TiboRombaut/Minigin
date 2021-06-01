#pragma once
#include "BaseComponent.h"
#include <Scene.h>
#include "Enums.h"

class MainMenuScene : public dae::BaseComponent
{
public:
	MainMenuScene() = default;

	void LoadGame(dae::Scene& currentScene);

	void Update();
	void Render() const {};
private:
	bool IsInButton(glm::vec2 pos, glm::vec2  posTexture, glm::vec2 sizeTexture);

	InWhatButtonMainMenu m_MouseClickHappenend = InWhatButtonMainMenu::None;
	std::shared_ptr<dae::TextureComponent> m_pSoloButton;
	std::shared_ptr<dae::TextureComponent> m_pCoopButton;
	std::shared_ptr<dae::TextureComponent> m_pVersusButton;
};

