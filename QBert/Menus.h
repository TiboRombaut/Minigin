#pragma once
#include <BaseComponent.h>
#include <TextureComponent.h>
#include <memory>
#include "Enums.h"
class Menus : public dae::BaseComponent
{
public:
	Menus(std::shared_ptr<dae::TextureComponent> playButton, std::shared_ptr<dae::TextureComponent> exitButton,
		std::shared_ptr<dae::TextureComponent> pauseScreen, std::shared_ptr<dae::TextureComponent> DeathScreen);

	void Update();
	void Render() const {};
	void SetPauseScreenActive();
	void SetPauseScreenInActive();

	InWhatButtonGameMenu& GetInWhatButtonGameMenu() { return m_MouseClickHappenend; };

	void SetDeathScreenActive();
	void SetDeathScreenInActive();
private:
	bool IsInButton(glm::vec2 pos, glm::vec2  posTexture,glm::vec2 sizeTexture);
	//void SetActive(std::shared_ptr<dae::TextureComponent> object);
	//void SetInActive(std::shared_ptr<dae::TextureComponent> object);

	InWhatButtonGameMenu m_MouseClickHappenend = InWhatButtonGameMenu::None;
	std::shared_ptr<dae::TextureComponent> m_pPlayButton;
	std::shared_ptr<dae::TextureComponent> m_pExitButton;
	std::shared_ptr<dae::TextureComponent> m_pPauseScreen;
	std::shared_ptr<dae::TextureComponent> m_pDeathScreen;
	//bool m_IsActive;
};

