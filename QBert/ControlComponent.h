#pragma once
#include <BaseComponent.h>
#include "Structs.h"
#include <memory>
#include <TextureComponent.h>

class ControlComponent : public dae::BaseComponent
{
public:
	explicit ControlComponent(float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> pTextureComp);

	void Update() =  0;
	void UpdateMovement();
	virtual void Render() const = 0;

	FieldDataPlayer GetFieldDataPlayer()const;
	void SetFieldData(FieldDataPlayer data);
	bool GetCanMove();
	void ResetCurrentTime();
	void SetMoveToTarget(glm::vec2 targetPos);
	void SetThatHeIsAllowedtoMove(bool canMove);
	bool GetIsAllowedtoMove()const;

	virtual ~ControlComponent() = default;
	ControlComponent(const ControlComponent& other) = delete;
	ControlComponent(ControlComponent&& other) = delete;
	ControlComponent& operator=(const ControlComponent& other) = delete;
	ControlComponent& operator=(ControlComponent&& other) = delete;
protected:
	FieldDataPlayer m_FieldData;
	float m_CurrentTime = 0.5f;
	float m_MoveTime = 0.5f;

	//move to pos
	bool m_NeedsToMove = false;
	std::shared_ptr<dae::TextureComponent> m_pTextureComp;
	glm::vec2 m_Speed = glm::vec2(0.0f, 0.0f);

private:
	glm::vec2 m_TargetPos;
};

