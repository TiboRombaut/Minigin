#include "Menus.h"
#include "GameObject.h"
#include "InputManager.h"
#include "CommandQbert.h"
Menus::Menus(std::shared_ptr<dae::TextureComponent> playButton,std::shared_ptr<dae::TextureComponent> exitButton,
	std::shared_ptr<dae::TextureComponent> pauseScreen, std::shared_ptr<dae::TextureComponent> DeathScreen)
	:m_pPlayButton(playButton)
	, m_pDeathScreen(DeathScreen)
	, m_pExitButton(exitButton)
	, m_pPauseScreen(pauseScreen)
{
	m_pDeathScreen->GetGameObject()->SetIsActive(false);
	m_pPauseScreen->GetGameObject()->SetIsActive(false);
	m_pPlayButton->GetGameObject()->SetIsActive(false);
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
			m_pPlayButton->SetTexture("SoloPressed.png");
			m_MouseClickHappenend = InWhatButtonGameMenu::Play;
		}
		else
		{
			m_pPlayButton->SetTexture("Solo.png");
			if (m_MouseClickHappenend == InWhatButtonGameMenu::Play)
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
			m_pExitButton->SetTexture("CoopPressed.png");
			m_MouseClickHappenend = InWhatButtonGameMenu::Exit;
		}
		else
		{
			m_pExitButton->SetTexture("Coop.png");
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
	m_pExitButton->GetGameObject()->SetIsActive(true);
	m_pPauseScreen->GetGameObject()->SetIsActive(true);

	//m_IsActive = true;
}

void Menus::SetPauseScreenInActive()
{
	m_pPauseScreen->GetGameObject()->SetIsActive(false);
	m_pPlayButton->GetGameObject()->SetIsActive(false);
	m_pExitButton->GetGameObject()->SetIsActive(false);
	//m_IsActive = false;
}

void Menus::SetDeathScreenActive()
{
	m_pExitButton->GetGameObject()->SetIsActive(true);
	m_pDeathScreen->GetGameObject()->SetIsActive(true);

	//m_IsActive = true;
}

void Menus::SetDeathScreenInActive()
{
	m_pDeathScreen->GetGameObject()->SetIsActive(false);
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
