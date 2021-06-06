#include "MiniginPCH.h"
#include "Command.h"

Command::Command(std::shared_ptr<dae::GameObject> actor)
	:m_pActor(actor)
{}
