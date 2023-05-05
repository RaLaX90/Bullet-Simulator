//#include <iostream>
//#include <chrono>
//#include <thread>

#include "Game.hpp"

int main(int argc, char* argv[])
{
	int NumberOfBulletsAndWalls = 10;

	Game game{ NumberOfBulletsAndWalls }; // parameter (int) - how bullets and walls you want

	//  Well, thats work, but after some time - freeze:( If you wanna to try it - uncomment code below, uncomment #include "iostream", 
	//	"chrono" and "thread" and comment "AddBullets()" function in "Game" class constructor.
	//	Meanwhile, program perfectly work in synchronous mode.
	//{
	//	Window* window = Window::GetInstance(MAP_WIDTH, MAP_HEIGHT);

	//	std::jthread thr{ [&] {
	//		for (int i = 0; i < NumberOfBulletsAndWalls; ++i) {
	//			game.Fire(window->GetRenderer(), SDL_FPoint{ (MAP_WIDTH / 2) - 7.5F, (MAP_HEIGHT / 2) - 7.5F }, SDL_FPoint{ 100, 60 }, 0.4F, 0.0F, 3.0F);
	//			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//			std::cout << std::this_thread::get_id() << std::endl;
	//	}
	//	} };
	//	thr.detach();
	//}

	while (game.GetState() == Game::State::STATE_OK)
	{
		game.HandleEvents();
		game.CalculateFPS();
		game.Update();
		game.DrawAll();
	}

	return 0;
}