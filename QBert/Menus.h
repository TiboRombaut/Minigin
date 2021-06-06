#pragma once
#include <BaseComponent.h>
#include <TextureComponent.h>
#include <TextComponent.h>
#include <memory>
#include "Enums.h"

class Menus : public dae::BaseComponent
{
public:
	Menus(std::shared_ptr<dae::TextureComponent> playButton, std::shared_ptr<dae::TextureComponent> exitButton,
		std::shared_ptr<dae::TextureComponent> restartButton, std::shared_ptr<dae::TextureComponent> mainMenuButton,
		std::shared_ptr<dae::TextureComponent> pauseScreen, std::shared_ptr<dae::TextureComponent> DeathScreen,
		std::shared_ptr<dae::TextComponent> textFinalScore);

	void Update();
	void Render() const {};
	void SetPauseScreenActive();
	void SetPauseScreenInActive();

	InWhatButtonGameMenu& GetInWhatButtonGameMenu() { return m_MouseClickHappenend; };

	void SetDeathScreenActive(int finalScore);
	void SetDeathScreenInActive();
private:
	bool IsInButton(glm::vec2 pos, glm::vec2  posTexture,glm::vec2 sizeTexture);

	InWhatButtonGameMenu m_MouseClickHappenend = InWhatButtonGameMenu::None;
	std::shared_ptr<dae::TextureComponent> m_pPlayButton;
	std::shared_ptr<dae::TextureComponent> m_pMainMenuButton;
	std::shared_ptr<dae::TextureComponent> m_pRestartButton;
	std::shared_ptr<dae::TextureComponent> m_pExitButton;
	std::shared_ptr<dae::TextureComponent> m_pPauseScreen;
	std::shared_ptr<dae::TextureComponent> m_pDeathScreen;
	std::shared_ptr<dae::TextComponent> m_pTextFinalScore;
};

