#pragma once
#include "AIComponent.h"
#include "PlayingField.h"
#include <GameObject.h>
#include "QBertComponent.h"
#include "ControlComponent.h"
#include "CommandQbert.h"

class Coily final : public AIComponent
{
public:

	Coily(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField, std::vector<std::shared_ptr<QBertComponent>>& Qberts, 
		float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> pTextureComp,bool isPlayerControlled);

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
	std::shared_ptr<dae::GameObject> m_pCoilyGameObject;
	bool m_IsEgg = true;
	std::vector < std::shared_ptr<QBertComponent>> m_pQBerts;
	bool m_IsDead = false;
	bool m_IsPlayerControlled = false;
};

