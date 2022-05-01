#pragma once
#include <SFML/Graphics.hpp>
#include "Observer.h"

class Command {
public:
    virtual ~Command();
    virtual void Execute() = 0;
protected:
    Command();
};

class Command_GameController : public Command {

	Subject_GameModel *m_game;
	Observer_GameView *m_render;
public:
	Command_GameController(Subject_GameModel *game, Observer_GameView *render);
	~Command_GameController();
	void Execute(); // the main game cycle
};

