#include "Game.h"

Game::Game() :
    m_gameIsRunning{ false }
{
SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow("Player Finite State Machine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	init();
}
    
Game::~Game()
{
    cleanUp();
}
    
void Game::run()
{
	AnimatedSprite player_animated_sprite(m_playerTex);

	Player player(player_animated_sprite);

	gpp::Events input;

	m_gameIsRunning = true;
	SDL_Event e{};

	while (m_gameIsRunning)
	{

		while(SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				m_gameIsRunning = false;
			}
			if (e.type == SDL_KEYDOWN)
			{
			
				
				// Deal with KeyPressed
		
				// Died Event
				if (e.key.keysym.sym  ==SDLK_d) {
					DEBUG_MSG("gpp::Events::Event::DIED_EVENT");
					input.setCurrent(gpp::Events::Event::DIED_EVENT);
				}
				// Revieved Event
				else if (e.key.keysym.sym  ==SDLK_r) {
					DEBUG_MSG("gpp::Events::Event::REVIVED_EVENT");
					input.setCurrent(gpp::Events::Event::REVIVED_EVENT);
				}
				// Running attack
				else if (e.key.keysym.sym  ==SDLK_z
					&& 
					e.key.keysym.sym  ==SDLK_RIGHT 
					||
					e.key.keysym.sym  ==SDLK_RIGHT 
					&& 
					e.key.keysym.sym  ==SDLK_z
					)
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_START");
					input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
				}
				// Attack
				else if (e.key.keysym.sym  ==SDLK_z)
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_START_EVENT");
					input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
				}
				// Throw attack
				else if (e.key.keysym.sym  ==SDLK_x 
					&& 
					e.key.keysym.sym  ==SDLK_RIGHT
					||
					e.key.keysym.sym  ==SDLK_RIGHT  
					&& 
					e.key.keysym.sym  ==SDLK_x
					)
				{
					DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
					input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
				}
				// Throw Attack
				else if (e.key.keysym.sym  ==SDLK_x)
				{
					DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
					input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
				}
				// Run Right
				else if (e.key.keysym.sym  ==SDLK_RIGHT)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				// Climb Up
				else if (e.key.keysym.sym  ==SDLK_UP)
				{
					DEBUG_MSG("gpp::Events::Event::MOVE_UP_START_EVENT");
					input.setCurrent(gpp::Events::Event::MOVE_UP_START_EVENT);
				}
				// Climb Down
				else if (e.key.keysym.sym  ==SDLK_DOWN)
				{
					DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_START_EVENT");
					input.setCurrent(gpp::Events::Event::MOVE_DOWN_START_EVENT);
				}
				// Hit Bottom of Ladder Event
				else if (e.key.keysym.sym  ==SDLK_c)
				{
					DEBUG_MSG("gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT);
				}
				// Hit Top of Ladder Event
				else if (e.key.keysym.sym  ==SDLK_t)	
				{
					DEBUG_MSG("gpp::Events::Event::HIT_LADDER_TOP_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_LADDER_TOP_EVENT);
				}
				// Jump Run
				if (e.key.keysym.sym  ==SDLK_SPACE
					&& 
					e.key.keysym.sym  ==SDLK_RIGHT
					||
					e.key.keysym.sym  ==SDLK_RIGHT
					&& 
					e.key.keysym.sym  ==SDLK_SPACE
					)
				{
					DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
					input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
				}
				// Jump Event
				else if (e.key.keysym.sym  ==SDLK_SPACE)
				{
					DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
					input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
				}
				// Running Slide
				else if (e.key.keysym.sym  == SDLK_DOWN
					&& 
					e.key.keysym.sym  ==SDLK_RIGHT
					||
					e.key.keysym.sym  ==SDLK_RIGHT
					&& 
					e.key.keysym.sym  ==SDLK_DOWN
					)
				{
					DEBUG_MSG("gpp::Events::Event::SLIDE_EVENT");
					input.setCurrent(gpp::Events::Event::SLIDE_EVENT);
				}
				// Hit Ground Event
				else if (e.key.keysym.sym  ==SDLK_h)
				{
					DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
				}

				// Jump Attack Event
				else if (e.key.keysym.sym  ==SDLK_h)
				{
					DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
				}

				// Jump Throw Attack Event
				else if (e.key.keysym.sym  ==SDLK_h)
				{
					DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
				}
			}

				// Deal with KeyReleased
			else if (e.type == SDL_KEYUP)
				{// Run and Stop Attack
				if (e.key.keysym.sym == SDLK_z
					&&
					e.key.keysym.sym == SDLK_RIGHT)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				// Stop Attack
				else if (e.key.keysym.sym  == SDLK_z)
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
				}
				// Run and Stop Throw Attack
				else if (e.key.keysym.sym  == SDLK_x
					&&
					e.key.keysym.sym == SDLK_RIGHT)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				// Stop Throw Attack
				else if (e.key.keysym.sym  == SDLK_x)
				{
					DEBUG_MSG("gpp::Events::Event::THROW_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::THROW_STOP_EVENT);
				}
				// Stop Running Right
				else if (e.key.keysym.sym  == SDLK_RIGHT)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_STOP_EVENT);
				}
				// Stop Slide
				else if (e.key.keysym.sym  == SDLK_DOWN 
					&&
					e.key.keysym.sym  ==SDLK_RIGHT)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				// Stop Moving Up
				else if (e.key.keysym.sym  == SDLK_UP)
				{
					DEBUG_MSG("gpp::Events::Event::MOVE_UP_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::MOVE_UP_STOP_EVENT);
				}
				// Stop Moving Down
				else if (e.key.keysym.sym  == SDLK_DOWN)
				{
					DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::MOVE_DOWN_STOP_EVENT);
				}
				
				}
			else
			{
				DEBUG_MSG("gpp::Events::Event::NONE");
				
				input.setCurrent(gpp::Events::Event::NONE);
				
			}
			// Handle input to Player
			player.handleInput(input);
		}
	
		// update
		player.update();

		// render
		SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(m_renderer);

		player.render(m_renderer);

		SDL_RenderPresent(m_renderer);
	}
}



void Game::init()
{
m_playerTex = util.loadFromFile(PLAYER_SPRITES, m_renderer);
	if (m_playerTex == nullptr)
	{
		DEBUG_MSG("Failed to load file");
		m_playerTex = util.loadFromFile(ERROR_SPRITES, m_renderer);
	}

}

void Game::cleanUp()
{
   	std::cout << "Cleaning up" << std::endl;

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	m_renderer = nullptr;

	
	IMG_Quit();
	SDL_Quit();
}
