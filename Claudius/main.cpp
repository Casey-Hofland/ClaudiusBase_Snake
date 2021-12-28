#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

#include "Game.h"
#include "Time.h"

#undef main

int main()
{
	Game game {30, 40, 20};

	Time time{};
	while (true)
	{
		time.Update();

		// Update the game
		game.Update(time.GetDeltaTime());

		// Render the game
		game.Render();
	}

	return 0;
}
