#pragma once
#include <BaseComponent.h>
#include "Structs.h"
#include <iostream>
#include "CommandQbert.h"
#include "ControlComponent.h"
#include "PlayingField.h"
class AIComponent : public ControlComponent
{
public:
	//AIComponent(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field);
	explicit AIComponent(float timeItTakesToMove,  std::shared_ptr<dae::TextureComponent> textureComp);

	virtual void Update() = 0;
	virtual void Render()const = 0;

	//FieldDataPlayer GetFieldData()const;
	//void SetFieldData(FieldDataPlayer data);
	//bool GetCanMove();
	void SetIsDead(bool isDead);
	bool GetIsDead()const;
	~AIComponent() = default;
	AIComponent(const AIComponent& other) = delete;
	AIComponent(AIComponent&& other) = delete;
	AIComponent& operator=(const AIComponent& other) = delete;
	AIComponent& operator=(AIComponent&& other) = delete;
private:
	bool m_IsDead = false;
	//FieldDataPlayer m_QBertFieldData;
	//float m_CurrentTime = 0.5f;
/*	MoveLeftUpCommand* m_pCommandMoveLeftUp = nullptr;
	MoveRightUpCommand* m_pCommandMoveRightUp = nullptr*/;

};

