#pragma once
#include <Command.h>
#include "Structs.h"
#include <string>
#include "PlayingField.h"
#include <memory>
//
//class CommandQbert
//{
//};

class MoveLeftDownCommand : public Command
{
public:
    MoveLeftDownCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field, std::string fileNamePath);
    void Execute() override;
private:
    std::shared_ptr<PlayingField> m_Field;
    std::string m_FileNameBackgroundTile;
};

class MoveRightDownCommand : public Command
{
public:
    MoveRightDownCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field, std::string fileNamePath);
    void Execute() override;
private:
    std::shared_ptr<PlayingField> m_Field;
    std::string m_FileNameBackgroundTile;
};

class MoveLeftUpCommand : public Command
{
public:
    MoveLeftUpCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field, std::string fileNamePath);
    MoveLeftUpCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field);
    void Execute() override;
private:
    std::shared_ptr<PlayingField> m_Field;
    std::string m_FileNameBackgroundTile;
};

class MoveRightUpCommand : public Command
{
public:
    MoveRightUpCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field, std::string fileNamePath);
    MoveRightUpCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> field);
    void Execute() override;
private:
    std::shared_ptr<PlayingField> m_Field;
    std::string m_FileNameBackgroundTile;
};