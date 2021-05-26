#pragma once
#include "AIComponent.h"
#include <memory>
#include "Structs.h"
#include "PlayingField.h"
#include "CommandQbert.h"
class UggAndWrongway final : public AIComponent
{
public:
	UggAndWrongway(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field);

	void Update();
	void Render() const {};

	//FieldDataPlayer GetFieldData()const;
	//void SetFieldData(FieldDataPlayer data);
	//bool GetCanMove();

	~UggAndWrongway();
	UggAndWrongway(const UggAndWrongway& other) = delete;
	UggAndWrongway(UggAndWrongway&& other) = delete;
	UggAndWrongway& operator=(const UggAndWrongway& other) = delete;
	UggAndWrongway& operator=(UggAndWrongway&& other) = delete;
private:
	MoveLeftUpCommand* m_pCommandMoveLeftUp = nullptr;
	MoveRightUpCommand* m_pCommandMoveRightUp = nullptr;
};

