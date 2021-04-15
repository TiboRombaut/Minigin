#include "MiniginPCH.h"
#include "Command.h"

#include "ScoreComponent.h"
#include "ServiceLocator.h"
//#include "Command.h"
//
Command::Command(std::shared_ptr<dae::GameObject> actor)
	:m_pActor(actor)
{}
//
//Command::Command(dae::GameObject* actor)
//	: m_pActor(actor)
//{}
//
//
//Command::~Command()
//{
//}
//
////Fire::Fire(std::shared_ptr<dae::GameObject> actor)
////	:Command(actor)
////{
////
////}
////
////Duck::Duck(std::shared_ptr<dae::GameObject> actor)
////	: Command(actor)
////{
////
////}
////
////Jump::Jump(std::shared_ptr<dae::GameObject> actor)
////	: Command(actor)
////{
////
////}
////
////Fart::Fart(std::shared_ptr<dae::GameObject> actor)
////	: Command(actor)
////{
////
////}
////
////Kill::Kill(std::shared_ptr<dae::GameObject> actor)
////	: Command(actor)
////{
////
////}
//
//Kill::Kill(dae::GameObject* pObject)
//	: Command(pObject)
//{
//
//}

Kill::Kill(std::shared_ptr<dae::GameObject> pObject)
	:Command(pObject)
{
	
}

void Kill::Execute()
{
    getActor()->GetComponent<dae::HealthComponent>()->LoseLive();
};

ColorChange::ColorChange(std::shared_ptr<dae::GameObject> pObject)
	:Command(pObject)
{

}

void ColorChange::Execute()
{
	int scoreChangingColor{ 25 };
	
	getActor()->GetComponent<dae::ScoreComponent>()->AddScore(scoreChangingColor);
};

CoilyDefeated::CoilyDefeated(std::shared_ptr<dae::GameObject> pObject)
	:Command(pObject)
{

}

void CoilyDefeated::Execute()
{
	int scoreDefeatingCoily{ 500 };
	getActor()->GetComponent<dae::ScoreComponent>()->AddScore(scoreDefeatingCoily);
};

CatchingSlickOrSam::CatchingSlickOrSam(std::shared_ptr<dae::GameObject> pObject)
	:Command(pObject)
{

}

void CatchingSlickOrSam::Execute()
{
	int scoreDefeatingSlickOrSam{ 300 };
	
	getActor()->GetComponent<dae::ScoreComponent>()->AddScore(scoreDefeatingSlickOrSam);
};

RemainingDisks::RemainingDisks(std::shared_ptr<dae::GameObject> pObject)
	:Command(pObject)
{

}

void RemainingDisks::Execute()
{
	int scorePerDisk{ 50 };
	int randRemainingDisks{ rand() % 5 };
	std::cout << randRemainingDisks << " disks remaining\n";
	getActor()->GetComponent<dae::ScoreComponent>()->AddScore(scorePerDisk * randRemainingDisks);
};

PlaySoundCommand::PlaySoundCommand(std::shared_ptr<dae::GameObject> pObject, std::string fileName)
	:Command(pObject)
	,m_FileName(fileName)
{

}

void PlaySoundCommand::Execute()
{
	dae::ServiceLocator::get_sound_system().Play(0, 1, m_FileName);
	std::cout << "sound";
};

MuteCommand::MuteCommand(std::shared_ptr<dae::GameObject> pObject)
	:Command(pObject)
{

}

void MuteCommand::Execute()
{
	dae::ServiceLocator::get_sound_system().ToggleMute();
	std::cout << "mute";
};

ChangeTextureCommand::ChangeTextureCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<dae::TextureComponent> textureComponent
	, std::string fileName)
	:Command(pObject)
	, m_TextureComponent(textureComponent)
	, m_FileName(fileName)
{

}

void ChangeTextureCommand::Execute()
{
	if (m_TextureComponent != nullptr)
	{
		m_TextureComponent->SetTexture(m_FileName);
	}
};
