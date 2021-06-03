#include "QBertComponent.h"
#include <GameTime.h>

QBertComponent::QBertComponent(float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> textureComp)
	:ControlComponent(timeItTakesToMove,textureComp)
{
	m_RespawnPos.x = textureComp->GetTransform().GetPosition().x;
	m_RespawnPos.y = textureComp->GetTransform().GetPosition().y;
}

//FieldDataPlayer QBertComponent::GetFieldData()const
//{
//	return m_QBertFieldData;
//}
//
//void QBertComponent::SetFieldData(FieldDataPlayer data)
//{
//	m_QBertFieldData = data;
//}
//
//bool QBertComponent::GetCanMove()
//{
//	//float minTime{0.5f};
//	//if (m_CurrentTime > minTime)
//	//{
//	//	m_CurrentTime = 0.0f;
//	//	return true;
//	//}
//	//return false;
//
//}
void QBertComponent::ColorWheelNeedsToMovetoTop(std::shared_ptr<dae::TextureComponent> textureColorWheel, glm::vec2 EndPos)
{
	m_PlatformNeedsToMove = true;
	m_ColorWheelPlatform = textureColorWheel;
	m_TargetPosColorWheel = EndPos;

}

void QBertComponent::Update()
{

	//std::cout << "Qbert FieldData: X:  " << m_QBertFieldData.Row << "  Y:  " << m_QBertFieldData.Column << std::endl;
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
		float posX = m_TextureComp->GetTransform().GetPosition().x;
		float posY = m_TextureComp->GetTransform().GetPosition().y;
		float posXColorWheel = m_ColorWheelPlatform->GetTransform().GetPosition().x;
		float posYColorWheel = m_ColorWheelPlatform->GetTransform().GetPosition().y;

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

		m_TextureComp->SetPosition(posX, posY);
		m_ColorWheelPlatform->SetPosition(posXColorWheel, posYColorWheel);
		float distanceX = glm::distance(posX, m_TargetPosColorWheel.x);
		float distanceY = glm::distance(posY, m_TargetPosColorWheel.y);

		if (distanceX < 1.0f && distanceY < 1.0f)
		{
			m_PlatformNeedsToMove = false;
			m_Speed.x = 0.0f;
			m_Speed.y = 0.0f;
			m_TextureComp->SetPosition(m_TargetPosColorWheel.x, m_TargetPosColorWheel.y);

			m_QBertFieldData.Column = 0;
			m_QBertFieldData.Row = 0;
			m_ColorWheelPlatform->SetIsActiveComponent(false);
		}
	}
	else if (m_QBertFieldData.Row == -1 || m_QBertFieldData.Column == -1)
	{
		auto fieldData = m_QBertFieldData;
		m_TextureComp->SetPosition(m_RespawnPos.x, m_RespawnPos.y);
		fieldData.Column = 0;
		fieldData.Row = 0;
		m_QBertFieldData = fieldData;
		ResetCurrentTime();
	}


}