#include "Game.hpp"

Game::Game(int elements_count) :
	m_elements_count(elements_count)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		throw SDL_GetError();
	}

	if (TTF_Init() != 0) {
		throw TTF_GetError();
	}

	//if (IMG_Init(IMG_INIT_PNG) != 0) {
	//	throw "Error at IMG_Init";
	//}

	state = STATE_OK;
	m_desired_fps = 60;

	lineManager = std::make_unique<LineManager>(elements_count);

	bulletManager = std::make_unique<BulletManager>(
		elements_count
		, lineManager->GetLinesPointer()
	);

	m_fps_rect = SDL_Rect{ 10, 10, 100, 120 };

	m_fps_font = TTF_OpenFont("../data/fonts/OpenSans-Bold.ttf", 400);
	if (m_fps_font == nullptr)
	{
		throw TTF_GetError();
	}

	//m_generator = std::mt19937(m_rd());
	//m_distribution_screen_width = std::uniform_int_distribution<short>(window->GetLeftBorderX(), window->GetRightBorderX());
	//m_distribution_screen_height = std::uniform_int_distribution<short>(window->GetTopBorderY(), window->GetBottomBorderY());

	//m_distribution_direction_x = std::uniform_int_distribution<short>(-5, 5);
	//m_distribution_direction_y = std::uniform_int_distribution<short>(-5, 5);
}

Game::~Game()
{
	TTF_CloseFont(m_fps_font);
	TTF_Quit();

	//IMG_Quit();
	SDL_Quit();
}

void Game::DrawScore(SDL_Renderer* _renderer, int fps)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_fps_font, std::to_string(fps).c_str(), SDL_Color{ 200, 200, 200, 255 });

	SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
	if (Message == nullptr) {
		throw SDL_GetError();
	}

	SDL_FreeSurface(surfaceMessage);

	SDL_RenderCopy(_renderer, Message, NULL, &m_fps_rect);

	SDL_DestroyTexture(Message);
}

bool Game::isCollision(const SDL_FRect* bullet_coordinate, FLineCoordinate* line_coordinate) const
{
	return SDL_IntersectFRectAndLine(bullet_coordinate, &line_coordinate->X1, &line_coordinate->X2, &line_coordinate->Y1, &line_coordinate->Y2);
}

void Game::Fire(SDL_FPoint start_position, SDL_FPoint dirrection, float speed, float shot_time, float life_time)
{
	bulletManager->Fire(start_position, dirrection, speed, shot_time, life_time);
}

void Game::AddLines(unsigned short window_center_X, unsigned short window_center_Y)
{
	//for (int i = 0; i < 10; ++i) {
		lineManager->AddNewLine(FLineCoordinate{ 500.0F, 500.0F, 800.0F, 800.0F });
	//}
}

void Game::Update(float elapsed_secs)
{
	bulletManager->Update(elapsed_secs);
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

void Game::DrawAll(int fps)
{
	Window* window = Window::GetInstance(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_SetRenderDrawColor(window->GetRenderer(), 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(window->GetRenderer()); // Clear Scene
	SDL_SetRenderDrawColor(window->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

	bulletManager->DrawAllBullets(window->GetRenderer());
	lineManager->DrawAllLines(window->GetRenderer());

	this->DrawScore(window->GetRenderer(), fps);

	SDL_RenderPresent(window->GetRenderer());
}

Game::State Game::GetState() const
{
	return state;
}