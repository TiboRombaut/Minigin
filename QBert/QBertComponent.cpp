#include "QBertComponent.h"
#include <GameTime.h>
#include <HealthComponent.h>
#include <GameObject.h>
QBertComponent::QBertComponent(float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> pTextureComp)
	:ControlComponent(timeItTakesToMove, pTextureComp)
{
	

}

void QBertComponent::SetRespawnPoint()
{
	m_RespawnPos.MiddlePosX = m_pTextureComp->GetTransform().GetPosition().x;
	m_RespawnPos.MiddlePosY = m_pTextureComp->GetTransform().GetPosition().y;
	m_RespawnPos.Row = m_FieldData.Row;
	m_RespawnPos.Column = m_FieldData.Column;
}

void QBertComponent::ColorWheelNeedsToMovetoTop(std::shared_ptr<dae::TextureComponent> pTextureColorWheel, glm::vec2 EndPos)
{
	m_PlatformNeedsToMove = true;
	m_pColorWheelPlatform = pTextureColorWheel;
	m_TargetPosColorWheel = EndPos;

}

void QBertComponent::RespawnQBert()
{
	m_pTextureComp->SetPosition(m_RespawnPos.MiddlePosX, m_RespawnPos.MiddlePosY);
	m_FieldData.Row = m_RespawnPos.Row;
	m_FieldData.Column = m_RespawnPos.Column;
	ResetCurrentTime();
	SetMoveToTarget(glm::vec2(m_RespawnPos.MiddlePosX, m_RespawnPos.MiddlePosY));
	SetThatHeIsAllowedtoMove(false);
}


void QBertComponent::Update()
{

	if (!m_PlatformNeedsToMove)
	{
		m_CurrentTime += GameTime::GetInstance().GetDeltaTime();
	}

	if (m_NeedsToMove)
	{
		UpdateMovement();
	}
	else if(m_PlatformNeedsToMove)
	{
		//for movement platform
		float posX = m_pTextureComp->GetTransform().GetPosition().x;
		float posY = m_pTextureComp->GetTransform().GetPosition().y;
		float posXColorWheel = m_pColorWheelPlatform->GetTransform().GetPosition().x;
		float posYColorWheel = m_pColorWheelPlatform->GetTransform().GetPosition().y;

		if (m_Speed.x == 0.0f && m_Speed.y == 0.0f)
		{
			float speed{ 10.0f };
			float sign = m_TargetPosColorWheel.x - posX;
			speed *= sign / speed;
			m_Speed.x = speed/2;

			speed = 10;

			sign = m_TargetPosColorWheel.y - posY;
			speed *= sign / speed;
			m_Speed.y = speed/2;
		}

		posX += m_Speed.x * GameTime::GetInstance().GetDeltaTime();
		posXColorWheel += m_Speed.x * GameTime::GetInstance().GetDeltaTime();
		posY += m_Speed.y * GameTime::GetInstance().GetDeltaTime();
		posYColorWheel += m_Speed.y * GameTime::GetInstance().GetDeltaTime();

		m_pTextureComp->SetPosition(posX, posY);
		m_pColorWheelPlatform->SetPosition(posXColorWheel, posYColorWheel);
		float distanceX = glm::distance(posX, m_TargetPosColorWheel.x);
		float distanceY = glm::distance(posY, m_TargetPosColorWheel.y);

		if (distanceX < 2.0f && distanceY < 2.0f)
		{
			m_PlatformNeedsToMove = false;
			m_Speed.x = 0.0f;
			m_Speed.y = 0.0f;
			m_pTextureComp->SetPosition(m_TargetPosColorWheel.x, m_TargetPosColorWheel.y);

			m_FieldData.Column = 0;
			m_FieldData.Row = 0;
			m_pColorWheelPlatform->SetIsActiveComponent(false);
		}
	}
	else if (m_FieldData.Row == -1 || m_FieldData.Column == -1)
	{
		RespawnQBert();
		//m_pTextureComp->GetGameObject().
		m_pTextureComp->GetGameObject()->GetComponent<dae::HealthComponent>()->LoseLive();
	}


}