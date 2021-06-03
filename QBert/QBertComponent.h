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
	QBertComponent(float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> textureComp);

	void Update()override;
	void Render() const override {};

	void ColorWheelNeedsToMovetoTop(std::shared_ptr<dae::TextureComponent> textureColorWheel,glm::vec2 EndPos);

	//FieldDataPlayer GetFieldData()const;
	//void SetFieldData(FieldDataPlayer data);
	//bool GetCanMove();
	~QBertComponent() = default;
	QBertComponent(const QBertComponent& other) = delete;
	QBertComponent(QBertComponent&& other) = delete;
	QBertComponent& operator=(const QBertComponent& other) = delete;
	QBertComponent& operator=(QBertComponent&& other) = delete;
private :
	std::shared_ptr<dae::TextureComponent> m_ColorWheelPlatform;
	bool m_PlatformNeedsToMove = false;
	glm::vec2 m_TargetPosColorWheel;
	glm::vec2 m_RespawnPos;
};

