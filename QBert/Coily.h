#pragma once
#include "AIComponent.h"
#include <memory>
#include "Structs.h"
#include "PlayingField.h"
#include "CommandQbert.h"
#include <GameObject.h>
#include "QBertComponent.h"
#include "ControlComponent.h"
class Coily final : public AIComponent
{
	enum class PossibleMovement : unsigned int
	{
		LeftUp,
		LeftDown,
		RightUp,
		RightDown
	};
public:

	Coily(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field, std::vector<std::shared_ptr<QBertComponent>>& Qberts, 
		float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> textureComp);

	void Update();
	void Render() const {};

	bool HasReachedBottom() { return !m_IsEgg; };
	bool GetIsDead()const;
	void SetIsDead(bool isDead);
	void SetIsEgg(bool isEgg);

	MoveLeftUpCommand* GetCommandUpLeft()const;
	MoveRightUpCommand* GetCommandUpRight()const;
	MoveRightDownCommand* GetCommandDownRight()const;
	MoveLeftDownCommand* GetCommandDownLeft()const;

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
	bool m_IsEgg = true;
	std::vector < std::shared_ptr<QBertComponent>> m_pQBerts;
	bool m_IsDead = false;
};
