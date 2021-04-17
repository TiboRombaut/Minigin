#pragma once
#include <BaseComponent.h>
#include "Structs.h"
#include <iostream>
#include "ControlComponent.h"
class QBertComponent : public ControlComponent
{
public:
	QBertComponent() = default;

	void Update()override;
	void Render() const override {};

	//FieldDataPlayer GetFieldData()const;
	//void SetFieldData(FieldDataPlayer data);
	//bool GetCanMove();
	~QBertComponent() = default;
	QBertComponent(const QBertComponent& other) = delete;
	QBertComponent(QBertComponent&& other) = delete;
	QBertComponent& operator=(const QBertComponent& other) = delete;
	QBertComponent& operator=(QBertComponent&& other) = delete;
//private :
//	FieldDataPlayer m_QBertFieldData;
//	float m_CurrentTime = 0.5f;
};

