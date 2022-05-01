#include "Singleton.h"
#include "Command.h"
#include "Subject.h"
#include "Observer.h"

int main()
{
	Assets::Instance().Load();                          // load the font

	Subject_GameModel game;			                    // create game model					
	Observer_GameView render(&game);					// create model view
	Command_GameController controller(&game, &render);	// create command controller
	controller.Execute();						    	// start the game

	return 0;
}
