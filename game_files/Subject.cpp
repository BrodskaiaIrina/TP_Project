#include "Subject.h"

Subject::Subject() {}
Subject::~Subject() {}

void Subject::Attach(Observer* o) {

    _observers.push_back(o);
}

void Subject::Detach(Observer* o) {

    _observers.remove(o);
}

void Subject::Notify() {

    std::list<Observer*>::iterator i;
    Observer *o;

    for ( i = _observers.begin(); i != _observers.end(); i++ ) {
        o = *i;
        o->Update(this);
    }
}

Subject_GameModel::Subject_GameModel()
{
	Init();
}

void Subject_GameModel::Init()
{
	// fill-up the array of cells
	for (int i = 0; i < ARRAY_SIZE - 1; i++) elements[i] = i + 1;
	// empty cell - the last in the array
	empty_index = ARRAY_SIZE - 1;
	elements[empty_index] = 0;	// the empty cell has a zero value
	solved = true;
}

bool Subject_GameModel::Check()
{
	// check if the puzzle is solved
	for (unsigned int i = 0; i < ARRAY_SIZE; i++)
	{
		if (elements[i] > 0 && elements[i] != i + 1) return false;
	}
	return true;
}

void Subject_GameModel::Action_Move(Direction direction)
{
	// calculate row and column of the empty cell
	int col = empty_index % SIZE;
	int row = empty_index / SIZE;

	// could we intermix, calculate an index of the cell beeing moved
	int move_index = -1;
	if (direction == Direction::Left && col < (SIZE - 1)) move_index = empty_index + 1;
	if (direction == Direction::Right && col > 0) move_index = empty_index - 1;
	if (direction == Direction::Up && row < (SIZE - 1)) move_index = empty_index + SIZE;
	if (direction == Direction::Down && row > 0) move_index = empty_index - SIZE;

	// move the cell to the empty cell position
	if (empty_index >= 0 && move_index >= 0)
	{
		int tmp = elements[empty_index];
		elements[empty_index] = elements[move_index];
		elements[move_index] = tmp;
		empty_index = move_index;
	}
	solved = Check();

    Notify(); // notify all registered observers by calling Update() of each of them
}

