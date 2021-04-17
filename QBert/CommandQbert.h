#pragma once
#include <Command.h>
#include "Structs.h"
#include <string>
//
//class CommandQbert
//{
//};

class MoveLeftDownCommand : public Command
{
public:
    MoveLeftDownCommand(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field, std::string fileNamePath);
    void Execute() override;
private:
    std::vector<FieldData> m_Field;
    std::string m_FileNameBackgroundTile;
};

class MoveRightDownCommand : public Command
{
public:
    MoveRightDownCommand(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field, std::string fileNamePath);
    void Execute() override;
private:
    std::vector<FieldData> m_Field;
    std::string m_FileNameBackgroundTile;
};

class MoveLeftUpCommand : public Command
{
public:
    MoveLeftUpCommand(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field, std::string fileNamePath);
    MoveLeftUpCommand(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field);
    void Execute() override;
private:
    std::vector<FieldData> m_Field;
    std::string m_FileNameBackgroundTile;
};

class MoveRightUpCommand : public Command
{
public:
    MoveRightUpCommand(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field, std::string fileNamePath);
    MoveRightUpCommand(std::shared_ptr<dae::GameObject> pObject, std::vector<FieldData>& field);
    void Execute() override;
private:
    std::vector<FieldData> m_Field;
    std::string m_FileNameBackgroundTile;
};