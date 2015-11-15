#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include "../include/res_path.h"
#include "../include/cleanup.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void logSDLError(std::ostream &os, const std::string &msg){
    os << msg << " error: " << SDL_GetError() << std::endl;
}

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }

    // Create a window
    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if(win == nullptr){
        logSDLError(std::cout, "CreateWindow");
        return 1;
    }

    // Create a renderer
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == nullptr){
        SDL_DestroyWindow(win);
        logSDLError(std::cout, "CreateRenderer");
        SDL_Quit();
        return 1;
    }

    // Load a BMP
    std::string imagePath = getResourcePath("Lesson1") + "hello.bmp";
    SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
    if(bmp == nullptr){
        cleanup(ren, win);
        logSDLError(std::cout, "LoadBmp");
        SDL_Quit();
        return 1;
    }

    // Create a texture from the loaded BMP
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if(tex == nullptr){
        cleanup(ren, win);
        logSDLError(std::cout, "CreateTextureFromSurface");
        SDL_Quit();
        return 1;
    }

    for(int i=0;i<3;i++){
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
        SDL_Delay(1000);
    }


    cleanup(tex, ren, win);
    SDL_Quit();

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}


