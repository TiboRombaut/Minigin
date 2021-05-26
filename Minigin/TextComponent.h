#pragma once
#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae {
	class Font;

	class TextComponent :
		public dae::BaseComponent
	{
	public:
		TextComponent() = default;
		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font);

		virtual ~TextComponent() = default;
		void Update() override;
		void Render() const override;
		void SetText(const std::string& text);
		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		dae::Transform m_Transform;
		std::shared_ptr<dae::Font> m_Font;
		std::shared_ptr<dae::Texture2D> m_Texture{};
	};
}
