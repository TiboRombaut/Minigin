#pragma once
#include "ControlComponent.h"
class SlickAndSamAIComponent :
    public ControlComponent
{
public:
	SlickAndSamAIComponent(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field);

	void Update();
	void Render() const {};

	//FieldDataPlayer GetFieldData()const;
	//void SetFieldData(FieldDataPlayer data);
	//bool GetCanMove();
	void SetIsDead(bool isDead);
	bool GetIsDead()const;
	~SlickAndSamAIComponent();
	SlickAndSamAIComponent(const SlickAndSamAIComponent& other) = delete;
	SlickAndSamAIComponent(SlickAndSamAIComponent&& other) = delete;
	SlickAndSamAIComponent& operator=(const SlickAndSamAIComponent& other) = delete;
	SlickAndSamAIComponent& operator=(SlickAndSamAIComponent&& other) = delete;
private:
	bool m_IsDead;
	//FieldDataPlayer m_QBertFieldData;
	//float m_CurrentTime = 0.5f;
	MoveLeftUpCommand* m_pCommandMoveLeftUp = nullptr;
	MoveRightUpCommand* m_pCommandMoveRightUp = nullptr;
};

