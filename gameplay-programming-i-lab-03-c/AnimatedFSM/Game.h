#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "Defines.h"
#include "Player.h"
#include "Events.h"
#include "Debug.h"
#include <cstdint>
#include <Utiliity.h>


class Game
{
public:

    Game();
    ~Game();
    void run();
    
private:
 void init();
    void cleanUp();

    bool m_gameIsRunning;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    SDL_Texture* m_playerTex;
  
    
  

    
    Utiliity util;
};


