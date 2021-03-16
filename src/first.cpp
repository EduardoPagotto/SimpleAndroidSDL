#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/include/SDL.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <string>

int main(int argc, char* argv[]) {

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
    Uint32 tsDown = 0;
    int count = 0;
    SDL_Event event;
    while (!done) {
        // Check Eventes
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT:
                case SDL_KEYDOWN:
                    done = 1;
                    SDL_Log("APP finished!!!!");
                    break;

                case SDL_FINGERMOTION:
                    SDL_Log("MOVE XY: %f ; %f", event.tfinger.x, event.tfinger.y); // Vals XY 0.0 -> 1.0
                    break;

                case SDL_FINGERDOWN:
                    tsDown = event.tfinger.timestamp;
                    SDL_Log("DOWN XY: %f ; %f", event.tfinger.x, event.tfinger.y);
                    break;

                case SDL_FINGERUP:
                    Uint32 tot = event.tfinger.timestamp - tsDown;
                    SDL_Log("UP (%d) XY: %f ; %f", tot, event.tfinger.x, event.tfinger.y);

                    if (tot < 1000) { // if hold less than 1 sec
                        done = 1;
                        SDL_Log("APP finished FAST FINGER!!!!");
                    }

                    break;
            }
        }
        // SDL_Log("Count: %d", count++);

        glClearColor((rand() % 256) / 256.0f, (rand() % 256) / 256.0f, (rand() % 256) / 256.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
        SDL_Delay(100);
    }

    exit(0);
}