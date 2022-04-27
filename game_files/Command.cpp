#include "Command.h"

Command::Command() {}

Command::~Command() {}

void Command::Execute() {}


Command_GameController::Command_GameController(Subject_GameModel *game, Observer_GameView *render)
{
	m_game = game;
	m_render = render;
}

Command_GameController::~Command_GameController() {}

void Command_GameController::Execute()
{
	sf::Event event;
	int move_counter = 0;	// counter for random move to intermix the puzzle

	while (m_render->window().isOpen())
	{
		while (m_render->window().pollEvent(event))
		{
			if (event.type == sf::Event::Closed) m_render->window().close();
			if (event.type == sf::Event::KeyPressed)
			{
				// get the pressed key - do the corresponding action
				if (event.key.code == sf::Keyboard::Escape) m_render->window().close();
				if (event.key.code == sf::Keyboard::Left) m_game->Action_Move(Direction::Left);
				if (event.key.code == sf::Keyboard::Right) m_game->Action_Move(Direction::Right);
				if (event.key.code == sf::Keyboard::Up) m_game->Action_Move(Direction::Up);
				if (event.key.code == sf::Keyboard::Down) m_game->Action_Move(Direction::Down);
				// new game
				if (event.key.code == sf::Keyboard::F2)
				{
					m_game->Init();
					move_counter = 100;
				}
			}
		}

		// if counter is not zero - continue to intermix the puzzle
		if (move_counter-- > 0) m_game->Action_Move((Direction)(rand() % 4));
	}
}

