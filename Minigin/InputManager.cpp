#include "MiniginPCH.h"
#include "InputManager.h"

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);
	XInputGetKeystroke(0, 0, &m_CurrentKeyStroke);

	for (size_t i = 0; i < m_CommandButton.size(); ++i)
	{
		if (IsPressed(m_CommandButton[i].whichControllerButton))
		{
			ExecuteCommand(i);
		}
	}

	return  HandleKeyBoard();
}

dae::InputManager::~InputManager()
{
	for (size_t i = 0; i < m_CommandButton.size(); ++i)
	{
		if (m_CommandButton[i].pCommand != nullptr)
		{
			delete m_CommandButton[i].pCommand;
		}
	}

}


void dae::InputManager::AddCommand(const ControllerButton button, const KeyBoardAndMouseButton& whichKeyBoardButton, const WayKeyBoardButton& whichKeyBoardButtonWay, Command* pCommand)
{
	m_CommandButton.push_back(ButtonCommand{ pCommand,button,whichKeyBoardButton,whichKeyBoardButtonWay });
}

void dae::InputManager::ExecuteCommand(const size_t index)
{
	if (index >= 0 && index < m_CommandButton.size())
	{
		m_CommandButton[index].pCommand->Execute();
		return;
	}

	std::cout << "nothing assigned\n";
}

bool dae::InputManager::HandleKeyBoard()
{
	while (SDL_PollEvent(&m_SDLEvent)) {
		if (m_SDLEvent.type == SDL_QUIT)
		{
			return false;
		}
		for (size_t i = 0; i < m_CommandButton.size(); ++i)
		{
			if (static_cast<WORD>(m_CommandButton[i].whichKeyBoardButton) == SDLK_UP)
			{
				std::cout << "up";
			}
			switch (m_CommandButton[i].whichKeyBoardButtonWay)
			{
			case WayKeyBoardButton::buttonUp:
			case WayKeyBoardButton::buttonDown:
				//this check is necessary or he wont know the difference between key up and down
				if (m_SDLEvent.type == static_cast<WORD>(m_CommandButton[i].whichKeyBoardButtonWay))
				{
					if (m_SDLEvent.key.keysym.sym == static_cast<WORD>(m_CommandButton[i].whichKeyBoardButton))
					{
						//this is normal SDLK
						ExecuteCommand(i);
					}
					else if (m_SDLEvent.key.keysym.scancode == static_cast<WORD>(m_CommandButton[i].whichKeyBoardButton))
					{
						//this is scancode
						ExecuteCommand(i);
					}
				}
				break;
			case WayKeyBoardButton::MouseButtonDown:
			case WayKeyBoardButton::MouseButtonUp:
				if (m_SDLEvent.type == static_cast<WORD>(m_CommandButton[i].whichKeyBoardButtonWay))
				{

					if (m_SDLEvent.button.button == static_cast<WORD>(m_CommandButton[i].whichKeyBoardButton))
					{
						ExecuteCommand(i);
					}
				}
				break;
			default:
				std::cout << "nothing assigned" << std::endl;
				break;
			}
		}
	}
	return true;
}

bool dae::InputManager::IsPressed(const ControllerButton& button)
{
	if (m_CurrentKeyStroke.Flags == XINPUT_KEYSTROKE_KEYDOWN && m_CurrentKeyStroke.VirtualKey == static_cast<WORD>(button))
	{
		return true;
	}
	return false;
}