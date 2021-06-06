#include "AIComponent.h"

#include <GameTime.h>
#include <GameObject.h>

AIComponent::AIComponent(float timeItTakesToMove, std::shared_ptr<dae::TextureComponent> pTextureComp)
	:ControlComponent(timeItTakesToMove, pTextureComp)
{

}

void AIComponent::SetIsDead(bool isDead)
{
	m_IsDead = isDead;
}

bool AIComponent::GetIsDead()const
{
	return m_IsDead;
}