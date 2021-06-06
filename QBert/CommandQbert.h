#pragma once
#include <Command.h>
#include "Structs.h"
#include <string>
#include "PlayingField.h"
#include <memory>
#include "Enums.h"
#include "Menus.h"

class MoveLeftDownCommand : public Command
{
public:
    MoveLeftDownCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField);
    void Execute() override;
private:
    std::shared_ptr<PlayingField> m_pField;
};

class MoveRightDownCommand : public Command
{
public:
    MoveRightDownCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField);
    void Execute() override;
private:
    std::shared_ptr<PlayingField> m_pField;
};

class MoveLeftUpCommand : public Command
{
public:
    MoveLeftUpCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField);
    void Execute() override;
private:
    std::shared_ptr<PlayingField> m_pField;
};

class MoveRightUpCommand : public Command
{
public:
    MoveRightUpCommand(std::shared_ptr<dae::GameObject> pObject, std::shared_ptr<PlayingField> pField);
    void Execute() override;
private:
    std::shared_ptr<PlayingField> m_pField;
};

class MouseClickMainMenuCommand : public Command
{
public:
    MouseClickMainMenuCommand(InWhatButtonMainMenu& clickHappened);
    void Execute() override;
private:
    InWhatButtonMainMenu& m_InWhatButton;
};

class MouseClickGameMenus : public Command
{
public:
    MouseClickGameMenus(InWhatButtonGameMenu& clickHappened, std::shared_ptr<Menus> Menus);
    void Execute() override;
private:
    InWhatButtonGameMenu& m_InWhatButton;
    std::shared_ptr<Menus> m_pMenus;
};

class PauseMenuCommand : public Command
{
public:
    PauseMenuCommand(std::shared_ptr<Menus> pMenus);
    void Execute() override;
private:
    std::shared_ptr<Menus> m_pMenus;
};