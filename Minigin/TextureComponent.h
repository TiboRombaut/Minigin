#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Transform.h"
#include <string>
#include <memory>
namespace dae {
	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent() = default;
		TextureComponent(const std::string& fileName);

		virtual ~TextureComponent() = default;
		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		int GetWidth()const;
		int GetHeight()const;
		std::string GetFileName()const;
	private:
		dae::Transform m_Transform;
		std::shared_ptr<dae::Texture2D> m_Texture{};
		std::string m_FileName;
	};
}
