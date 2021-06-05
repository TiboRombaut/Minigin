#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	m_pActiveScene->Update();
	//for (auto& scene : m_Scenes)
	//{
	//	scene->Update();
	//}
}

void  dae::SceneManager::SetActiveScene(std::string whatScene)
{
	for (size_t i = 0; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i]->GetName() == whatScene)
		{
			m_pActiveScene = m_Scenes[i];
		}
	}
}

void  dae::SceneManager::DeleteScene(std::string whatScene)
{
	for (size_t i = 0; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i]->GetName() == whatScene)
		{
			m_Scenes[i].reset();
			m_Scenes.erase(m_Scenes.begin() + i);
		}
	}
	if (m_Scenes.size() > 0)
	{
		m_pActiveScene = m_Scenes[0];
	}
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetActiveScene()const
{
	return m_pActiveScene;
}

void dae::SceneManager::Render()
{
	m_pActiveScene->Render();
	//for (const auto& scene : m_Scenes)
	//{
	//	scene->Render();
	//}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	std::cout << "create scene: " << name;
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	m_pActiveScene = scene;
	return *scene;
}