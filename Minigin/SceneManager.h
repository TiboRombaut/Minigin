#pragma once
#include "MiniginPCH.h"
#include "Singleton.h"
#include <vector>
namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void Render();
		void SetActiveScene(std::string whatScene);
		std::shared_ptr<Scene> GetActiveScene()const;
		void DeleteScene(std::string whatScene);
		//void DeleteActiveScene();
		
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_pActiveScene;
	};
}
