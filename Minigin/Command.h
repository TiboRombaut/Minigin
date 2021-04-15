#pragma once
#include "GameObject.h"
#include "HealthComponent.h"
#include "TextureComponent.h"


//class Command
//{
//public:
//    Command() = default;
//    virtual ~Command() = default;
//    virtual void Execute() = 0;
//
//    Command(const Command& other) = delete;
//    Command(Command&& other) = delete;
//    Command& operator=(const Command& other) = delete;
//    Command& operator=(Command&& other) = delete;
//};

class Command
{
protected:
	std::shared_ptr<dae::GameObject> getActor()const { return m_pActor; };
	//dae::GameObject* getActor()const { return m_pActor; };
public:
	explicit  Command(std::shared_ptr<dae::GameObject> actor);
	//explicit  Command(dae::GameObject* actor);
	virtual ~Command() = default;
	virtual void Execute() = 0;
private:
	std::shared_ptr<dae::GameObject> m_pActor;
	//dae::GameObject* m_pActor;

};

//class Fire : public Command
//{
//public:
//	Fire(std::shared_ptr<dae::GameObject> actor);
//
//	void Execute()override {
//		//getActor()->Fire();
//	}
//};
//
//class Duck : public Command
//{
//public:
//	Duck(std::shared_ptr<dae::GameObject> actor);
//
//	void Execute()override {
//		//getActor()->Duck();
//	}
//};
//
//class Jump : public Command
//{
//public:
//	Jump(std::shared_ptr<dae::GameObject> actor);
//
//	void Execute()override {
//		//getActor()->Jump();
//	}
//};
//
//class Fart : public Command
//{
//public:
//	Fart(std::shared_ptr<dae::GameObject> actor);
//
//	void Execute()override {
//		//getActor()->Fart();
//	}
//};

class Kill : public Command
{
public:
    Kill(std::shared_ptr<dae::GameObject> pObject);
    void Execute() override;
};

class ColorChange : public Command
{
public:
    ColorChange(std::shared_ptr<dae::GameObject> pObject);
    void Execute() override;
};

class CoilyDefeated : public Command
{
public:
    CoilyDefeated(std::shared_ptr<dae::GameObject> pObject);
    void Execute() override;
};

class CatchingSlickOrSam : public Command
{
public:
    CatchingSlickOrSam(std::shared_ptr<dae::GameObject> pObject);
    void Execute() override;
};

class RemainingDisks : public Command
{
public:
    RemainingDisks(std::shared_ptr<dae::GameObject> pObject);
    void Execute() override;
};

class PlaySoundCommand : public Command
{
public:
    PlaySoundCommand(std::shared_ptr<dae::GameObject> pObject,std::string fileName);
    void Execute() override;
private:
    std::string m_FileName;
};

class MuteCommand : public Command
{
public:
    MuteCommand(std::shared_ptr<dae::GameObject> pObject);
    void Execute() override;
};

class ChangeTextureCommand : public Command
{
public:
    ChangeTextureCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<dae::TextureComponent> textureComponent
        , std::string fileName);
    void Execute() override;
private:
    std::shared_ptr<dae::TextureComponent> m_TextureComponent;
    std::string m_FileName;
};
