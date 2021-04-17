#pragma once
#include <BaseComponent.h>
#include "Structs.h"
#include <iostream>
#include "CommandQbert.h"

class ControlComponent : public dae::BaseComponent
{
public:
	ControlComponent() = default;

	virtual void Update() = 0;
	virtual void Render() const = 0;

	FieldDataPlayer GetFieldData()const;
	void SetFieldData(FieldDataPlayer data);
	bool GetCanMove();
	void ResetCurrentTime();

	virtual ~ControlComponent() = default;
	ControlComponent(const ControlComponent& other) = delete;
	ControlComponent(ControlComponent&& other) = delete;
	ControlComponent& operator=(const ControlComponent& other) = delete;
	ControlComponent& operator=(ControlComponent&& other) = delete;
protected:
	FieldDataPlayer m_QBertFieldData;
	float m_CurrentTime = 0.5f;
};

