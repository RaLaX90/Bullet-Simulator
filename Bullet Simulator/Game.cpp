#include "Game.hpp"

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		throw "Error at sdl_init";
	}

	//if (IMG_Init(IMG_INIT_PNG) != 0) {
	//	throw "Error at IMG_Init";
	//}

	state = STATE_OK;
	//m_desired_fps = 60;

	Window* window = Window::GetInstance(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);

	bulletManager = std::make_unique<BulletManager>();

	//m_generator = std::mt19937(m_rd());
	//m_distribution_screen_width = std::uniform_int_distribution<short>(window->GetLeftBorderX(), window->GetRightBorderX());
	//m_distribution_screen_height = std::uniform_int_distribution<short>(window->GetTopBorderY(), window->GetBottomBorderY());

	//m_distribution_direction_x = std::uniform_int_distribution<short>(-5, 5);
	//m_distribution_direction_y = std::uniform_int_distribution<short>(-5, 5);
}

Game::~Game()
{
	//IMG_Quit();
	SDL_Quit();
}

bool Game::isCollision(const SDL_Rect* object1, const SDL_Rect* object2) const
{
	return SDL_HasIntersection(object1, object2);
}

void Game::Update()
{
	current_time = SDL_GetTicks();

	bulletManager->Update();

	// Clamping FPS.
	if (1000 / m_desired_fps > (SDL_GetTicks() - current_time)) {
		m_actual_fps = 1000 / m_desired_fps - (SDL_GetTicks() - current_time);

		SDL_Delay(m_actual_fps);
	}
}

void Game::HandleEvents()
{
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT: {
			state = STATE_EXIT;
			break;
		}
		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: {
				state = STATE_EXIT;
				break;
			}
			default: {
				break;
			}
			}

			break;
		}
		default: {
			break;
		}
		}
	}
}

void Game::DrawAll()
{
	Window* window = Window::GetInstance(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_SetRenderDrawColor(window->GetRenderer(), 0x00, 0x00, 0x00, 0x00);
	// Clear Scene
	SDL_RenderClear(window->GetRenderer());

	SDL_SetRenderDrawColor(window->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

	bulletManager->DrawAllBullets(window->GetRenderer());

	SDL_RenderPresent(window->GetRenderer());
}

Game::State Game::GetState() const
{
	return state;
}