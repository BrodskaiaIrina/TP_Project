#include "Singleton.h"

void Assets::Load()
{
	if (!font.loadFromFile("font.ttf")) throw;
}
