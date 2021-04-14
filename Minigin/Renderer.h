#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void InitPlayer(int index,int amount,int Score);
		void UpdateLives(int index,int amount);
		void UpdateScore(int index,int amount);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
		void RenderUI() const;
	private:
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_pWindow{};
		//bool* m_pShowDemo{ new bool(true) };
		int m_QBert1Lives{ 0 };
		int m_QBert1Score{ 0 };

		int m_QBert2Lives{ 0 };
		int m_QBert2Score{ 0 };
	};
}
