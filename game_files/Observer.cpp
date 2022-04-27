#include "Subject.h"
#include "Observer.h"
#include "Singleton.h"

Observer::Observer() {}

Observer::~Observer() {}

void Observer_GameView::Update(Subject* theChangedSubject) {

    if (theChangedSubject == m_game) {
        Render();
    }
}

Observer_GameView::Observer_GameView(Subject_GameModel *game)
{
	m_game = game;
    m_game->Attach(this);
	Init();
    Render();
}

Observer_GameView::~Observer_GameView() {
    m_game->Detach(this);    
}

bool Observer_GameView::Init()
{
	setPosition(50.f, 50.f);
	// create window 600x600 and refresh rate 60 shots per second
	m_window.create(sf::VideoMode(600, 600), "puzzle15");
	m_window.setFramerateLimit(60);
	// text with control keys
	m_text = sf::Text("F2 - New Game / Esc - Exit / Arrow Keys - Move Tile", Assets::Instance().font, 20);
//  m_text.setFillColor(sf::Color::Cyan);
	m_text.setFillColor(sf::Color::Green);
	m_text.setPosition(5.f, 5.f);
	return true;
}

void Observer_GameView::Render()
{
	m_window.clear();
	m_window.draw(*this);
	m_window.draw(m_text);
	m_window.display();
}

void Observer_GameView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Color color = sf::Color(200, 100, 200);

	// draw the game field frame
	sf::RectangleShape shape(sf::Vector2f(Subject_GameModel::FIELD_SIZE, Subject_GameModel::FIELD_SIZE));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);

	// prepare frame for the cells
	shape.setSize(sf::Vector2f(Subject_GameModel::CELL_SIZE - 2, Subject_GameModel::CELL_SIZE - 2));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	// prepare text for cells numbers
	sf::Text text("", Assets::Instance().font, 52);

	int *elements = m_game->GetState();
	for (unsigned int i = 0; i < Subject_GameModel::ARRAY_SIZE; i++)
	{
		shape.setOutlineColor(color);
		text.setFillColor(color);
		text.setString(std::to_string(elements[i]));
		if (m_game->IsSolved())
		{
			// other colour for the solved puzzle
//      	shape.setOutlineColor(sf::Color::Cyan);
//			text.setFillColor(sf::Color::Cyan);
			shape.setOutlineColor(sf::Color::Green);
			text.setFillColor(sf::Color::Green);		}
		else if (elements[i] == i + 1)
		{
			// colour the cell on the correct position
			text.setFillColor(sf::Color::Green);
		}

		// draw all cells except the empty one
		if (elements[i] > 0)
		{
			// calculate cell position to draw
			sf::Vector2f position(i % Subject_GameModel::SIZE * Subject_GameModel::CELL_SIZE + 10.f, i / Subject_GameModel::SIZE * Subject_GameModel::CELL_SIZE + 10.f);
			shape.setPosition(position);
			// text position was defined manually
			text.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f);
            // draw the cell frame
			target.draw(shape, states);
            // draw the cell number
			target.draw(text, states);
		}
	}
}

