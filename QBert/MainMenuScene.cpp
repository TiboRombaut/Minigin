#include "MainMenuScene.h"
#include <ResourceManager.h>
#include <TextComponent.h>
#include <InputManager.h>
#include "CommandQbert.h"
void MainMenuScene::LoadGame(dae::Scene& currentScene)
{
	auto go = std::make_shared<dae::GameObject>();
	std::shared_ptr<dae::TextureComponent> component{ std::make_shared<dae::TextureComponent>() };
	component->SetTexture("background.jpg");
	go->addComponent(component);


	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto component2 = std::make_shared<dae::TextComponent>("Programming 4 Exam Assignment", font);
	component2->SetPosition(80, 20);
	go->addComponent(component2);
	currentScene.Add(go);

	auto soloButton = std::make_shared<dae::GameObject>();
	m_pSoloButton = { std::make_shared<dae::TextureComponent>("Solo.png") };
	m_pSoloButton->SetPosition(250, 200);
	soloButton->addComponent(m_pSoloButton);
	currentScene.Add(soloButton);

	auto coopButton = std::make_shared<dae::GameObject>();
	m_pCoopButton = { std::make_shared<dae::TextureComponent>("Coop.png") };
	m_pCoopButton->SetPosition(250, 250);
	coopButton->addComponent(m_pCoopButton);
	currentScene.Add(coopButton);

	auto vsButton = std::make_shared<dae::GameObject>();
	m_pVersusButton = { std::make_shared<dae::TextureComponent>("Vs.png") };
	m_pVersusButton->SetPosition(250, 300);
	vsButton->addComponent(m_pVersusButton);
	currentScene.Add(vsButton);

	auto& input = dae::InputManager::GetInstance();

	MouseClickMainMenuCommand* mosueClick = new MouseClickMainMenuCommand(m_MouseClickHappenend);
	input.AddCommand(dae::ControllerButton::None, dae::KeyBoardAndMouseButton::MouseButtonLeft, dae::WayKeyBoardButton::MouseButtonDown, mosueClick);

}

void MainMenuScene::Update()
{
	auto mousePos = dae::InputManager::GetMousePos();
	if (m_pSoloButton)
	{
		if (IsInButton(mousePos, glm::vec2(m_pSoloButton->GetTransform().GetPosition().x, m_pSoloButton->GetTransform().GetPosition().y),
			glm::vec2(m_pSoloButton->GetWidth(), m_pSoloButton->GetHeight())))
		{
			m_pSoloButton->SetTexture("SoloPressed.png");
			m_MouseClickHappenend = InWhatButtonMainMenu::Solo;
		}
		else
		{
			m_pSoloButton->SetTexture("Solo.png");
			if (m_MouseClickHappenend == InWhatButtonMainMenu::Solo)
			{
				m_MouseClickHappenend = InWhatButtonMainMenu::None;
			}
		}
	}
	if (m_pCoopButton)
	{
		if (IsInButton(mousePos, glm::vec2(m_pCoopButton->GetTransform().GetPosition().x, m_pCoopButton->GetTransform().GetPosition().y),
			glm::vec2(m_pCoopButton->GetWidth(), m_pCoopButton->GetHeight())))
		{
			m_pCoopButton->SetTexture("CoopPressed.png");
			m_MouseClickHappenend = InWhatButtonMainMenu::Coop;
		}
		else
		{
			m_pCoopButton->SetTexture("Coop.png");
			if (m_MouseClickHappenend == InWhatButtonMainMenu::Coop)
			{
				m_MouseClickHappenend = InWhatButtonMainMenu::None;
			}
		}
	}
	if (m_pVersusButton)
	{
		if (IsInButton(mousePos, glm::vec2(m_pVersusButton->GetTransform().GetPosition().x, m_pVersusButton->GetTransform().GetPosition().y),
			glm::vec2(m_pVersusButton->GetWidth(), m_pVersusButton->GetHeight())))
		{
			m_pVersusButton->SetTexture("VsPressed.png");
			m_MouseClickHappenend = InWhatButtonMainMenu::Vs;
		}
		else
		{
			m_pVersusButton->SetTexture("Vs.png");
			if (m_MouseClickHappenend == InWhatButtonMainMenu::Vs)
			{
				m_MouseClickHappenend = InWhatButtonMainMenu::None;
			}
		}
	}
	//switch (m_MouseClickHappenend)
	//{
	//case InWhatButtonMainMenu::Solo:
	//	//start solo game
	//	std::cout << "start solo";
	//	break;
	//case InWhatButtonMainMenu::Coop:
	//	//start coop game
	//	std::cout << "start coop";
	//	break;
	//case InWhatButtonMainMenu::Vs:
	//	//start vs game
	//	std::cout << "start vs";
	//	break;
	//case InWhatButtonMainMenu::None:
	//	std::cout << "none";
	//	break;
	//default:
	//	break;
	//}
}

bool MainMenuScene::IsInButton(glm::vec2 pos, glm::vec2  posTexture, glm::vec2 sizeTexture)
{
	if (pos.x > posTexture.x && pos.x < posTexture.x + sizeTexture.x &&
		pos.y > posTexture.y && pos.y < posTexture.y + sizeTexture.y)
	{
		return true;
	}
	return false;
}
