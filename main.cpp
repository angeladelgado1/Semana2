/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL.h"
#include "SDL_image.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"
#include "Llama.h"
#include <string>

//Screen attributes
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;
const int SCREEN_BPP = 32;

SDL_Surface *screen = NULL;
SDL_Rect offset;
Timer* update;


bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //Set the window caption
    SDL_WM_SetCaption( "SDL Runner Lab Progra 3", NULL );

    //If everything initialized fine
    return true;
}

void frameCap()
{
    int frames_per_seccond = 15;
    if(update->get_ticks() < 1000 / frames_per_seccond)
    {
        //Sleep the remaining frame time
        SDL_Delay( ( 1000 / frames_per_seccond ) - update->get_ticks() );
    }
    update->start();
}

int main( int argc, char* args[] )
{
    //Initialize
    init();
    update=new Timer();
    update->start();

    SDL_Surface * game_over = IMG_Load( "game_over.png" );


    Background background(screen);
    Player player(screen);
    Enemy enemy(screen);
    Enemy enemy2(screen);
    Llama Llama(screen);

    SDL_Event event;
    //Quit flag
    bool quit = false;
    while( quit == false )
    {
        //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_UP:
                        if (! player.isJumping){
                            player.jump(); break;
                        }


                }
            }
            //If the user has Xed out the window
            else if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        background.logic();
        player.logic();
        enemy.logic();
        enemy2.logic2();
        Llama.logic();

        if(player.x-enemy.x<50
           && player.x-enemy.x>-50
           && player.y-enemy.y<50
           && player.y-enemy.y>-50
            or player.x-Llama.x<50
           && player.x-Llama.x>-50
           && player.y-Llama.y<50
           && player.y-Llama.y>-50)
        {
            player.perder();
        }

        if(player.x-enemy2.x<50
           && player.x-enemy2.x>-50
           && player.y-enemy2.y<50
           && player.y-enemy2.y>-50
           or player.x-Llama.x<50
           && player.x-Llama.x>-50
           && player.y-Llama.y<50
           && player.y-Llama.y>-50)
        {
           player.perder();
        }

        if (player.murio)
                break;
        background.render();
        player.render();
        enemy.render();
        enemy2.render();
        Llama.render();

        frameCap();

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

    }

    while( quit == false )
    {
        //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE: quit = true; break;
                }
            }
            //If the user has Xed out the window
            else if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        //SDL_Rect offset;
        offset.x = 0;
        offset.y = 0;


        SDL_BlitSurface( game_over, NULL, screen, &offset );

        frameCap();

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
    }

    //SDL_Quit();

    return 0;
}
