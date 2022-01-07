#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

#include "Game.h"

#undef main

int main()
{
	Game game {30, 40, 20};
	while (game.IsPlaying())
	{
		game.Update();
		game.Render();
	}

	return 0;
}
