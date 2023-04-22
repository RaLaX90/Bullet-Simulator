//#include <iostream>

#include "Game.hpp"

#include "Global.hpp"

int main(int argc, char* argv[])
{
	Game game(10);

	game.AddLines(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	game.Fire(SDL_FPoint{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 }, SDL_FPoint{ -100, -100 }, 1.0F, 0.0F, 0.0F);

	int frameCount = 0, fps = 0;
	float timerFPS = 0;

	uint32_t begin = SDL_GetTicks(), end;
	float elapsed_secs;

	while (game.GetState() == Game::State::STATE_OK)
	{
		end = SDL_GetTicks();
		elapsed_secs = (end - begin) / 1000.0F;
		begin = end;

		timerFPS += elapsed_secs;

		//std::cout << timerFPS << std::endl;

		frameCount++;
		if (timerFPS > 1.0F) {
			fps = frameCount;
			frameCount = 0;
			timerFPS = 0;
		}

		game.Update(elapsed_secs);
		game.HandleEvents();
		game.DrawAll(fps);
	}

	return 0;
}