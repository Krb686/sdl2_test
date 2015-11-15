#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <iostream>
#include <SDL2/SDL.h>
#include "../include/res_path.h"

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        std::cout << "SDL_INIT Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if(win == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a renderer
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == nullptr){
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Load a BMP
    std::string imagePath = getResourcePath("Lesson1") + "hello.bmp";
    SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
    if(bmp == nullptr){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a texture from the loaded BMP
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if(tex == nullptr){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    for(int i=0;i<3;i++){
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
        SDL_Delay(1000);
    }


    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    /*
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap
        SDL_BlitSurface(bmp, 0, screen, &dstrect);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);
    */
    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
