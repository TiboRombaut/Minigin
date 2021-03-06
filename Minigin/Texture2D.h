#pragma once

struct SDL_Texture;
namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* pTexture);
		~Texture2D();

		Texture2D(const Texture2D&) = delete;
		Texture2D(Texture2D&&) = delete;
		Texture2D& operator= (const Texture2D&) = delete;
		Texture2D& operator= (const Texture2D&&) = delete;

		int GetWidth();
		int GetHeight();
	private:
		SDL_Texture* m_pTexture;

		int m_Width = 0;
		int m_Height = 0;
	};
}
