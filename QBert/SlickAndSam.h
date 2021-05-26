#pragma once
#include "AIComponent.h"
#include <memory>
#include "Structs.h"
#include "PlayingField.h"
#include "CommandQbert.h"

class SlickAndSam final : public AIComponent
{
public:
	SlickAndSam(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field);

	void Update();
	void Render() const {};

	//FieldDataPlayer GetFieldData()const;
	//void SetFieldData(FieldDataPlayer data);
	//bool GetCanMove();

	~SlickAndSam();
	SlickAndSam(const SlickAndSam& other) = delete;
	SlickAndSam(SlickAndSam&& other) = delete;
	SlickAndSam& operator=(const SlickAndSam& other) = delete;
	SlickAndSam& operator=(SlickAndSam&& other) = delete;
private:
	MoveLeftDownCommand* m_pCommandMoveLeftDown = nullptr;
	MoveRightDownCommand* m_pCommandMoveRightDown = nullptr;

};

