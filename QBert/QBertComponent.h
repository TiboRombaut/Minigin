#pragma once
#include <BaseComponent.h>
#include "Structs.h"
#include <iostream>
#include "ControlComponent.h"
#include <memory>
#include <TextureComponent.h>
class QBertComponent : public ControlComponent
{
public:
	QBertComponent(float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> pTextureComp);

	void Update()override;
	void Render() const override {};

	void ColorWheelNeedsToMovetoTop(std::shared_ptr<dae::TextureComponent> pTextureColorWheel,glm::vec2 EndPos);
	void SetRespawnPoint();
	void RespawnQBert();

	~QBertComponent() = default;
	QBertComponent(const QBertComponent& other) = delete;
	QBertComponent(QBertComponent&& other) = delete;
	QBertComponent& operator=(const QBertComponent& other) = delete;
	QBertComponent& operator=(QBertComponent&& other) = delete;
private :
	std::shared_ptr<dae::TextureComponent> m_pColorWheelPlatform;
	bool m_PlatformNeedsToMove = false;
	glm::vec2 m_TargetPosColorWheel;
	FieldData m_RespawnPos;
};

