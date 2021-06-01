#pragma once
#include <Windows.h>
#include <XInput.h>
#include <SDL.h>

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

	enum class WayKeyBoardButton {
		buttonUp = SDL_KEYUP,
		buttonDown = SDL_KEYDOWN,
		MouseButtonDown = SDL_MOUSEBUTTONDOWN,
		MouseButtonUp = SDL_MOUSEBUTTONUP,
		none
	};

	enum class KeyBoardAndMouseButton
	{
		//https://stackoverflow.com/questions/56915258/difference-between-sdl-scancode-and-sdl-keycode
		//explanation differnce keycode/scancode bets use keycode because that wont be affected by dofferent keyboard layout
		ButtonQ = SDLK_q,		//is scancode better maybe use this?
		ButtonW = SDLK_w,
		ButtonE = SDLK_e,
		ButtonR = SDLK_r,
		ButtonT = SDLK_t,
		ButtonY = SDLK_y,
		ButtonU = SDLK_u,
		ButtonI = SDLK_i,
		ButtonO = SDLK_o,
		ButtonP = SDLK_p,
		ButtonA = SDLK_a,
		ButtonS = SDLK_s,
		ButtonD = SDLK_d,
		ButtonF = SDLK_f,
		ButtonG = SDLK_g,
		ButtonH = SDLK_h,
		ButtonJ = SDLK_j,
		ButtonK = SDLK_k,
		ButtonL = SDLK_l,
		ButtonZ = SDLK_z,
		ButtonX = SDLK_x,
		ButtonC = SDLK_c,
		ButtonV = SDLK_v,
		ButtonB = SDLK_b,
		ButtonN = SDLK_n,
		ButtonM = SDLK_m,
		//ButtonTab = VK_TAB,
		//ButtonShift = VK_SHIFT,
		//ButtonCrtl = VK_CONTROL,
		ButtonAltLeft = SDLK_LALT,
		ButtonAltRight = SDLK_RALT,
		ButtonArrowUp = SDLK_UP,			//this also uses scancode
		ButtonArrowDown = SDL_SCANCODE_DOWN,//uses scancode
		ButtonArrowRight = SDL_SCANCODE_RIGHT,
		ButtonArrowLeft = SDL_SCANCODE_LEFT,
		//ButtonSpace = VK_SPACE,
		//ButtonEscape = VK_ESCAPE,
		Button0 = SDLK_0,
		Button1 = SDLK_1,
		Button2 = SDLK_2,
		Button3 = SDLK_3,
		Button4 = SDLK_4,
		Button5 = SDLK_5,
		Button6 = SDLK_6,
		Button7 = SDLK_7,
		Button8 = SDLK_8,
		Button9 = SDLK_9,

		//mouse buttons
		MouseButtonLeft = SDL_BUTTON_LEFT,
		MouseButtonRight = SDL_BUTTON_RIGHT,
		MouseButtonMiddle = SDL_BUTTON_MIDDLE,
		None
	};

	struct ButtonCommand
	{
		Command* pCommand;
		ControllerButton whichControllerButton;
		KeyBoardAndMouseButton whichKeyBoardButton;
		WayKeyBoardButton whichKeyBoardButtonWay;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager();
		bool ProcessInput();
		bool IsPressed(const ControllerButton& button);
		bool HandleKeyBoard();
		void AddCommand(const ControllerButton button, const KeyBoardAndMouseButton& whichKeyBoardButton, const WayKeyBoardButton& whichKeyBoardButtonWay, Command* pCommand);
		void ExecuteCommand(const size_t index);
		static glm::vec2 GetMousePos();
		void EndGame() { m_StopGame = true; };
	private:

		XINPUT_STATE m_CurrentState{};
		XINPUT_KEYSTROKE m_CurrentKeyStroke{};
		SDL_Event m_SDLEvent{};

		std::vector<ButtonCommand> m_CommandButton = {};
		bool m_StopGame = false;
	};
}
