#include "ControlComponent.h"
#include "GameTime.h"
#include "QBertComponent.h"
ControlComponent::ControlComponent(float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> textureComp)
	:m_MoveTime(timeItTakesToMove),
	m_TextureComp(textureComp)
{

}

void ControlComponent::SetFieldData(FieldDataPlayer data)
{
	m_QBertFieldData = data;
}

FieldDataPlayer ControlComponent::GetFieldDataPlayer()const
{
	return m_QBertFieldData;
}

void ControlComponent::SetMoveToTarget(glm::vec2 targetPos)
{
	m_TargetPos = targetPos;
	m_Speed.x = 0.0f;
	m_Speed.y = 0.0f;
	SetThatHeIsAllowedtoMove(true);
}

void ControlComponent::SetThatHeIsAllowedtoMove(bool canMove)
{
	m_NeedsToMove = canMove;
}

bool ControlComponent::GetIsAllowedtoMove()const
{
	return m_NeedsToMove;
}

bool ControlComponent::GetCanMove()
{
	if (m_CurrentTime > m_MoveTime)
	{
		return true;
	}
	return false;
}
void ControlComponent::ResetCurrentTime()
{
	m_CurrentTime = 0.0f;
}

void ControlComponent::UpdateMovement()
{
	//if (m_TextureComp->GetGameObject()->HasComponent<QBertComponent>())
	//{
	//	std::cout << "target: " << m_TargetPos.x << " , " << m_TargetPos.y << std::endl;
	//}
	float posX = m_TextureComp->GetTransform().GetPosition().x;
	float posY = m_TextureComp->GetTransform().GetPosition().y;

	if (m_Speed.x == 0.0f && m_Speed.y == 0.0f)
	{
		std::cout << "speed";
		float speed{ 10.0f };
		float sign = m_TargetPos.x - posX;
		speed *= sign / speed;
		m_Speed.x = speed*2;

		speed = 10;

		sign = m_TargetPos.y - posY;
		speed *= sign / speed;
		m_Speed.y = speed*2;
	}

	posX += m_Speed.x * GameTime::GetInstance().GetDeltaTime();
	posY += m_Speed.y * GameTime::GetInstance().GetDeltaTime();

	m_TextureComp->SetPosition(posX, posY);
	float distanceX = glm::distance(posX, m_TargetPos.x);
	float distanceY = glm::distance(posY, m_TargetPos.y);
	
	if (distanceX < 0.5f && distanceY < 0.5f)
	{
		m_NeedsToMove = false;
		m_Speed.x = 0.0f;
		m_Speed.y = 0.0f;
		m_TextureComp->SetPosition(m_TargetPos.x,m_TargetPos.y);

	}
}
