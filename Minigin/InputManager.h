#pragma once
#include <XInput.h>

#include "Command.h"
#include "Singleton.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = VK_PAD_A,
		ButtonB = VK_PAD_B,
		ButtonX = VK_PAD_X,
		ButtonY = VK_PAD_Y,
		//todo: add the other buttons
		LeftBump = VK_PAD_LSHOULDER,
		LeftTrigger = VK_PAD_LTRIGGER,
		RightBump = VK_PAD_RSHOULDER,
		RightTrigger = VK_PAD_RTRIGGER,
		Start = VK_PAD_START,
		Back = VK_PAD_BACK,
		LeftJoystick = VK_PAD_LTHUMB_PRESS,
		RightJoystick = VK_PAD_RTHUMB_PRESS,
		LeftDpad = VK_PAD_DPAD_LEFT,
		RightDpad = VK_PAD_DPAD_RIGHT,
		UpDpad = VK_PAD_DPAD_UP,
		DownDpad = VK_PAD_DPAD_DOWN,
		None
	};

	struct ButtonCommand
	{
		Command* pCommand;
		ControllerButton whichButton;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput();
		bool IsPressed(const ControllerButton& button)const;
		void AddCommand(const ControllerButton button, Command* pCommand);
		void ExecuteCommand(const ControllerButton& button);
	private:
		XINPUT_STATE m_CurrentState{};
		XINPUT_KEYSTROKE m_CurrentKeyStroke{};

		std::vector<ButtonCommand> m_CommandButton = {};
	};
}
