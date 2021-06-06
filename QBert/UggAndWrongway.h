#pragma once
#include "AIComponent.h"
#include "CommandQbert.h"

class UggAndWrongway final : public AIComponent
{
public:
	UggAndWrongway(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField,
		float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> pTextureComp);

	void Update();
	void Render() const {};

	~UggAndWrongway();
	UggAndWrongway(const UggAndWrongway& other) = delete;
	UggAndWrongway(UggAndWrongway&& other) = delete;
	UggAndWrongway& operator=(const UggAndWrongway& other) = delete;
	UggAndWrongway& operator=(UggAndWrongway&& other) = delete;
private:
	MoveLeftUpCommand* m_pCommandMoveLeftUp = nullptr;
	MoveRightUpCommand* m_pCommandMoveRightUp = nullptr;
};

