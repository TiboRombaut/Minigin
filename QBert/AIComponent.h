#pragma once
#include <BaseComponent.h>
#include "Structs.h"
#include <iostream>
#include "CommandQbert.h"
#include "ControlComponent.h"
class AIComponent : public ControlComponent
{
public:
	AIComponent(std::shared_ptr<dae::GameObject> pObject,std::vector<FieldData>& field);

	void Update();
	void Render() const {};

	//FieldDataPlayer GetFieldData()const;
	//void SetFieldData(FieldDataPlayer data);
	//bool GetCanMove();
	~AIComponent();
	AIComponent(const AIComponent& other) = delete;
	AIComponent(AIComponent&& other) = delete;
	AIComponent& operator=(const AIComponent& other) = delete;
	AIComponent& operator=(AIComponent&& other) = delete;
private:
	//FieldDataPlayer m_QBertFieldData;
	//float m_CurrentTime = 0.5f;
	MoveLeftUpCommand* m_pCommandMoveLeftUp = nullptr;
	MoveRightUpCommand* m_pCommandMoveRightUp = nullptr;

};

