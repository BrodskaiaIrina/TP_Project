#pragma once
#include <SFML/Graphics.hpp>
#include "Subject.h"

class Subject;
class Subject_GameModel;

class Observer {
public:
    ~Observer();
    virtual void Update(Subject* theChangedSubject) = 0;
protected:
    Observer();
};

class Observer_GameView : public Observer, public sf::Drawable, public sf::Transformable {
	Subject_GameModel *m_game;
	sf::RenderWindow m_window;
	sf::Text m_text;
public:
	Observer_GameView(Subject_GameModel *game);
	~Observer_GameView();
	sf::RenderWindow& window() { return m_window; };
	bool Init();
	void Render();
    void Update(Subject*);
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


