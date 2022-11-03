#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Observer.h"

class Observer;

class Subject {
public:
    ~Subject();
    virtual void Attach(Observer*);
    virtual void Detach(Observer*);
    virtual void Notify();
protected:
    Subject();
private:
    std::list<Observer*> _observers;
};

enum class Direction { Left = 0, Right = 1, Up = 2, Down = 3 };

class Subject_GameModel : public Subject {
public:
	static const int SIZE = 4;						// number of cells in a line
	static const int ARRAY_SIZE = SIZE * SIZE;		// size of the array with cells
	static const int FIELD_SIZE = 500;				// size of game field in pixels
	static const int CELL_SIZE = 120;				// size of cell in pixels
protected:
	int elements[ARRAY_SIZE];
	int empty_index;
	bool solved;
public:
	Subject_GameModel();
	void Init();
	bool Check();
    int GetMoveIndex(Direction direction);
	void Action_Move(Direction direction);
	bool IsSolved() { return solved; }
    int* GetState() { return elements; }
};

