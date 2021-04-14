#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);
	XInputGetKeystroke(0, 0, &m_CurrentKeyStroke);

	for (size_t i = 0; i < m_CommandButton.size(); ++i)
	{
		if (IsPressed(m_CommandButton[i].whichButton))
		{
			ExecuteCommand(m_CommandButton[i].whichButton);
		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
		}
		if (e.type == SDLK_a)
		{
			//ExecuteCommand(ControllerButton::ButtonA);
		}
	}

	return true;
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


void dae::InputManager::AddCommand(const ControllerButton button, Command* pCommand)
{
	m_CommandButton.push_back(ButtonCommand{ pCommand,button });
}

void dae::InputManager::ExecuteCommand(const dae::ControllerButton& button)
{
	for (size_t i = 0; i < m_CommandButton.size(); i++)
	{
		if (m_CommandButton[i].whichButton == button)
		{
			m_CommandButton[i].pCommand->Execute();
			return;
		}
	}

	std::cout << "nothing assigned\n";
}


bool dae::InputManager::IsPressed(const ControllerButton& button) const
{
	if (m_CurrentKeyStroke.Flags == XINPUT_KEYSTROKE_KEYDOWN && m_CurrentKeyStroke.VirtualKey == static_cast<WORD>(button))
	{
		//ExecuteCommand(button);
		return true;
	}
	return false;
}