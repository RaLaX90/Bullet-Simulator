#include "Game.hpp"


Game::Game(int elements_count) :
	m_elements_count(elements_count)
{
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		throw SDL_GetError();
	}

	if (TTF_Init()) {
		throw TTF_GetError();
	}

	//if (IMG_Init(IMG_INIT_PNG)) {
	//	throw IMG_GetError;
	//}

	m_state = STATE_OK;

	m_wallManager = std::make_unique<WallManager>(elements_count);
	m_wallManager->AddWalls();

	m_bulletManager = std::make_unique<BulletManager>(
		elements_count,
		m_wallManager->GetWallsPointer()
	);
	m_bulletManager->AddBullets(); // This

	m_fps_rect = SDL_Rect{ 10, 10, 100, 120 };
	m_fps_font = TTF_OpenFont("../data/fonts/OpenSans-Bold.ttf", 400);
	if (m_fps_font == NULL)
	{
		throw TTF_GetError();
	}
}

Game::~Game()
{
	TTF_CloseFont(m_fps_font);
	TTF_Quit();

	//IMG_Quit();
	SDL_Quit();
}

void Game::Fire(const SDL_Renderer* _renderer, SDL_FPoint pos, SDL_FPoint dir, float speed, float time, float life_time)
{
	m_bulletManager->Fire(_renderer, pos, dir, speed, time, life_time);
}

void Game::DrawFPS(const SDL_Renderer* _renderer)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_fps_font, std::to_string(this->m_actualFPS).c_str(), SDL_Color{ 200, 200, 200, 255 });

	SDL_Texture* Message = SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(_renderer), surfaceMessage);
	if (Message == NULL) {
		throw SDL_GetError();
	}

	SDL_FreeSurface(surfaceMessage);

	if (SDL_RenderCopy(const_cast<SDL_Renderer*>(_renderer), Message, NULL, &m_fps_rect)) {
		throw SDL_GetError();
	}

	SDL_DestroyTexture(Message);
}

void Game::CalculateFPS()
{
	m_end = SDL_GetTicks();
	m_elapsed_secs = (m_end - m_begin) / 1000.0F;	// miliseconds to seconds
	m_begin = m_end;

	m_timerFPS += m_elapsed_secs;

	m_frameCount++;
	if (m_timerFPS > 1.0F) { // fps refresh rate (by default = 1 second)
		m_actualFPS = m_frameCount;
		m_frameCount = 0;
		m_timerFPS = 0;
	}
}

void Game::Update()
{
	this->m_bulletManager->Update(this->m_elapsed_secs);
}

void Game::HandleEvents()
{
	while (SDL_PollEvent(&m_event)) {
		switch (m_event.type)
		{
		case SDL_QUIT: {			// press "x" button on the top right 
			m_state = STATE_EXIT;
			break;
		}
		case SDL_KEYDOWN: {
			switch (m_event.key.keysym.sym) {
			case SDLK_ESCAPE: {		// press escape button
				m_state = STATE_EXIT;
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
	Window* window = Window::GetInstance(MAP_WIDTH, MAP_HEIGHT);

	SDL_SetRenderDrawColor(const_cast<SDL_Renderer*>(window->GetRenderer()), 0x00, 0x00, 0x00, 0x00);	// paint background to black color
	SDL_RenderClear(const_cast<SDL_Renderer*>(window->GetRenderer()));									// Clear Scene
	SDL_SetRenderDrawColor(const_cast<SDL_Renderer*>(window->GetRenderer()), 0xFF, 0xFF, 0xFF, 0xFF);

	this->m_bulletManager->DrawAll(window->GetRenderer());
	this->m_wallManager->DrawAll(window->GetRenderer());

	this->DrawFPS(window->GetRenderer());

	SDL_RenderPresent(const_cast<SDL_Renderer*>(window->GetRenderer()));								// paint all object
}

Game::State Game::GetState() const
{
	return m_state;
}