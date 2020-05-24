#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../SDL2/include/SDL.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <string>

int main(int argc, char *argv[]) {

    SDL_Window* window = nullptr;
    SDL_GLContext gl = nullptr;

    // Initialize SDL 
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    } 

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    std::string msg_start = "SDL2 Iniciado"; 
    SDL_Log("%s", msg_start.c_str());

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
    int width = mode.w;
    int height = mode.h;

    SDL_Log("Width: %d; Height: %d", width, height);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow(nullptr, 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (window == nullptr) {
        SDL_Log("Faild to create window %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // OpenGL Context
    gl = SDL_GL_CreateContext(window);
    if (gl == nullptr) {
        SDL_Log("Faild to create Context OpenGL %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Main Loop 
    Uint8 done = 0;
    SDL_Event event;
    int count = 0;
    while(!done) {

        // Check Eventes
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN)
            {
                done = 1;
            }
        }
        SDL_Log("Count: %d", count++);

        glClearColor((rand() % 256) / 256.0f, (rand() % 256) / 256.0f, (rand() % 256) / 256.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
        SDL_Delay(100);

    }

    exit(0);
}