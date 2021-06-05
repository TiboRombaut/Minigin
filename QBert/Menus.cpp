#include "Menus.h"
#include "GameObject.h"
#include "InputManager.h"
#include "CommandQbert.h"
Menus::Menus(std::shared_ptr<dae::TextureComponent> playButton,std::shared_ptr<dae::TextureComponent> exitButton,
	std::shared_ptr<dae::TextureComponent> restartButton, std::shared_ptr<dae::TextureComponent> mainMenuButton,
	std::shared_ptr<dae::TextureComponent> pauseScreen, std::shared_ptr<dae::TextureComponent> DeathScreen)
	:m_pPlayButton(playButton)
	, m_pDeathScreen(DeathScreen)
	, m_pMainMenuButton(mainMenuButton)
	, m_pRestartButton(restartButton)
	, m_pExitButton(exitButton)
	, m_pPauseScreen(pauseScreen)
{
	m_pDeathScreen->GetGameObject()->SetIsActive(false);
	m_pPauseScreen->GetGameObject()->SetIsActive(false);
	m_pPlayButton->GetGameObject()->SetIsActive(false);
	m_pMainMenuButton->GetGameObject()->SetIsActive(false);
	m_pRestartButton->GetGameObject()->SetIsActive(false);
	m_pExitButton->GetGameObject()->SetIsActive(false);
}

void Menus::Update()
{
	auto mousePos = dae::InputManager::GetMousePos();
	if (m_pPlayButton->GetGameObject()->GetIsActive())
	{
		if (IsInButton(mousePos, glm::vec2(m_pPlayButton->GetTransform().GetPosition().x, m_pPlayButton->GetTransform().GetPosition().y),
			glm::vec2(m_pPlayButton->GetWidth(), m_pPlayButton->GetHeight())))
		{
			m_pPlayButton->SetTexture("ResumePressed.png");
			m_MouseClickHappenend = InWhatButtonGameMenu::Play;
		}
		else
		{
			m_pPlayButton->SetTexture("Resume.png");
			if (m_MouseClickHappenend == InWhatButtonGameMenu::Play)
			{
				m_MouseClickHappenend = InWhatButtonGameMenu::None;
			}
		}
	}

	if (m_pMainMenuButton->GetGameObject()->GetIsActive())
	{
		if (IsInButton(mousePos, glm::vec2(m_pMainMenuButton->GetTransform().GetPosition().x, m_pMainMenuButton->GetTransform().GetPosition().y),
			glm::vec2(m_pMainMenuButton->GetWidth(), m_pMainMenuButton->GetHeight())))
		{
			m_pMainMenuButton->SetTexture("MainMenuPressed.png");
			m_MouseClickHappenend = InWhatButtonGameMenu::MainMenu;
		}
		else
		{
			m_pMainMenuButton->SetTexture("MainMenu.png");
			if (m_MouseClickHappenend == InWhatButtonGameMenu::MainMenu)
			{
				m_MouseClickHappenend = InWhatButtonGameMenu::None;
			}
		}
	}

	if (m_pRestartButton->GetGameObject()->GetIsActive())
	{
		if (IsInButton(mousePos, glm::vec2(m_pRestartButton->GetTransform().GetPosition().x, m_pRestartButton->GetTransform().GetPosition().y),
			glm::vec2(m_pRestartButton->GetWidth(), m_pRestartButton->GetHeight())))
		{
			m_pRestartButton->SetTexture("RestartPressed.png");
			m_MouseClickHappenend = InWhatButtonGameMenu::Restart;
		}
		else
		{
			m_pRestartButton->SetTexture("Restart.png");
			if (m_MouseClickHappenend == InWhatButtonGameMenu::Restart)
			{
				m_MouseClickHappenend = InWhatButtonGameMenu::None;
			}
		}
	}

	if (m_pExitButton->GetGameObject()->GetIsActive())
	{
		if (IsInButton(mousePos, glm::vec2(m_pExitButton->GetTransform().GetPosition().x, m_pExitButton->GetTransform().GetPosition().y),
			glm::vec2(m_pExitButton->GetWidth(), m_pExitButton->GetHeight())))
		{
			m_pExitButton->SetTexture("ExitPressed.png");
			m_MouseClickHappenend = InWhatButtonGameMenu::Exit;
		}
		else
		{
			m_pExitButton->SetTexture("Exit.png");
			if (m_MouseClickHappenend == InWhatButtonGameMenu::Exit)
			{
				m_MouseClickHappenend = InWhatButtonGameMenu::None;
			}
		}
	}


}

void Menus::SetPauseScreenActive()
{
	m_pPlayButton->GetGameObject()->SetIsActive(true);
	m_pRestartButton->GetGameObject()->SetIsActive(true);
	m_pMainMenuButton->GetGameObject()->SetIsActive(true);
	m_pExitButton->GetGameObject()->SetIsActive(true);
	m_pPauseScreen->GetGameObject()->SetIsActive(true);

	//m_IsActive = true;
}

void Menus::SetPauseScreenInActive()
{
	m_pPauseScreen->GetGameObject()->SetIsActive(false);
	m_pPlayButton->GetGameObject()->SetIsActive(false);
	m_pMainMenuButton->GetGameObject()->SetIsActive(false);
	m_pRestartButton->GetGameObject()->SetIsActive(false);
	m_pExitButton->GetGameObject()->SetIsActive(false);
	//m_IsActive = false;
}

void Menus::SetDeathScreenActive()
{
	m_pMainMenuButton->GetGameObject()->SetIsActive(true);
	m_pRestartButton->GetGameObject()->SetIsActive(true);
	m_pExitButton->GetGameObject()->SetIsActive(true);
	m_pDeathScreen->GetGameObject()->SetIsActive(true);

	//m_IsActive = true;
}

void Menus::SetDeathScreenInActive()
{
	m_pDeathScreen->GetGameObject()->SetIsActive(false);
	m_pRestartButton->GetGameObject()->SetIsActive(false);
	m_pMainMenuButton->GetGameObject()->SetIsActive(false);
	m_pExitButton->GetGameObject()->SetIsActive(false);
	//m_IsActive = false;
}

//void Menus::SetActive(std::shared_ptr<dae::TextureComponent> object)
//{
//	auto scale = object->GetTransform()->GetScale();
//	auto posScreen = object->GetTransform()->GetPosition();
//
//	object->GetTransform()->Translate(posScreen.x, posScreen.y / -2, posScreen.z);
//}
//
//void Menus::SetInActive(std::shared_ptr<dae::TextureComponent> object)
//{
//	auto scale = object->GetTransform()->GetScale();
//	auto posScreen = object->GetTransform()->GetPosition();
//	object->GetTransform()->Translate(posScreen.x, posScreen.y * -2, posScreen.z);
//}

bool Menus::IsInButton(glm::vec2 pos, glm::vec2  posTexture, glm::vec2 sizeTexture)
{
	if (pos.x > posTexture.x  && pos.x < posTexture.x + sizeTexture.x &&
		pos.y > posTexture.y  && pos.y < posTexture.y + sizeTexture.y)
	{
		return true;
	}
	return false;
}
