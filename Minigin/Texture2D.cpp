#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

dae::Texture2D::Texture2D(SDL_Texture* pTexture)
{
	m_pTexture = pTexture;
	SDL_QueryTexture(pTexture, NULL, NULL, &m_Width, &m_Height);
}

int dae::Texture2D::GetWidth()
{
	return m_Width;
}

int dae::Texture2D::GetHeight()
{
	return m_Height;
}