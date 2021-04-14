#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_pWindow = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();
	//if(m_pShowDemo)
	//{
	//	ImGui::ShowDemoWindow(m_pShowDemo);
	//}
	RenderUI();
	
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::RenderUI()const
{
	ImGui::Begin("gamemode");
	ImGui::Button("Single Player");
	ImGui::Button("Co-op");
	ImGui::Button("Versus");
	ImGui::End();

	ImGui::Begin("Player1");
	std::string textLives{ "Lives: " + std::to_string(m_QBert1Lives) };
	ImGui::Text(textLives.c_str());
	
	std::string textScore{ "Score: " + std::to_string(m_QBert1Score) };
	ImGui::Text(textScore.c_str());
	ImGui::End();

	ImGui::Begin("Player2");
	std::string textLives2{ "Lives: " + std::to_string(m_QBert2Lives) };
	ImGui::Text(textLives2.c_str());

	std::string textScore2{ "Score: " + std::to_string(m_QBert2Score) };
	ImGui::Text(textScore2.c_str());
	ImGui::End();
}

void  dae::Renderer::InitPlayer(int index, int amount,int score)
{
	if(index == 0)
	{
		m_QBert1Lives = amount;
		m_QBert1Score = score;
	}else
	{
		m_QBert2Lives = amount;
		m_QBert2Score = score;
	}

}

void  dae::Renderer::UpdateLives(int index, int amount)
{
	if (index == 0)
	{		
		m_QBert1Lives = amount;
	}
	else
	{
		m_QBert2Lives = amount;
	}
}

void  dae::Renderer::UpdateScore(int index, int amount)
{
	if (index == 0)
	{
		m_QBert1Score = amount;
	}
	else
	{
		m_QBert2Score = amount;
	}
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//delete m_pShowDemo;

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}