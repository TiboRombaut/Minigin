#pragma once
#include "AIComponent.h"
#include <memory>
#include "Structs.h"
#include "PlayingField.h"
#include "CommandQbert.h"
#include <GameObject.h>

class Coily final : public AIComponent
{
public:
	Coily(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field);

	void Update();
	void Render() const {};

	//FieldDataPlayer GetFieldData()const;
	//void SetFieldData(FieldDataPlayer data);
	//bool GetCanMove();
	bool HasReachedBottom() { return !IsEgg; };

	~Coily();
	Coily(const Coily& other) = delete;
	Coily(Coily&& other) = delete;
	Coily& operator=(const Coily& other) = delete;
	Coily& operator=(Coily&& other) = delete;
private:
	MoveLeftUpCommand* m_pCommandMoveLeftUp = nullptr;
	MoveRightUpCommand* m_pCommandMoveRightUp = nullptr;
	MoveRightDownCommand* m_pCommandMoveRightDown = nullptr;
	MoveLeftDownCommand* m_pCommandMoveLeftDown = nullptr;
	std::shared_ptr<dae::GameObject> m_CoilyGameObject;
	bool IsEgg = true;
};

