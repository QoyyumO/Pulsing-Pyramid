#include <SDL.h>
#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void drawPyramid(SDL_Renderer* renderer, float pulse) {
    // Define the vertices of the pyramid
    SDL_Point vertices[5] = {
        {SCREEN_WIDTH / 2, 50},  // Apex
        {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 100},  // Base vertex 1
        {SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT - 100},  // Base vertex 2
        {SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT - 300},  // Base vertex 3
        {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 300}   // Base vertex 4
    };

    // Connect the vertices to form the edges of the pyramid
    SDL_SetRenderDrawColor(renderer, 255 * pulse, 0, 0, SDL_ALPHA_OPAQUE); // Use pulse for color modulation
    SDL_RenderDrawLine(renderer, vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y);
    SDL_RenderDrawLine(renderer, vertices[0].x, vertices[0].y, vertices[2].x, vertices[2].y);
    SDL_RenderDrawLine(renderer, vertices[0].x, vertices[0].y, vertices[3].x, vertices[3].y);
    SDL_RenderDrawLine(renderer, vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y);
    SDL_RenderDrawLine(renderer, vertices[1].x, vertices[1].y, vertices[4].x, vertices[4].y); // Missing line
    SDL_RenderDrawLine(renderer, vertices[2].x, vertices[2].y, vertices[3].x, vertices[3].y);
    SDL_RenderDrawLine(renderer, vertices[3].x, vertices[3].y, vertices[4].x, vertices[4].y);
    SDL_RenderDrawLine(renderer, vertices[4].x, vertices[4].y, vertices[1].x, vertices[1].y);


}

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("Pyramid Pulsing Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    float pulse = 0.0f;
    float pulseSpeed = 0.05f;

    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Update pulse
        pulse = 0.5f + 0.5f * std::sin(SDL_GetTicks() * pulseSpeed);

        // Draw the pyramid with pulsing effect
        drawPyramid(renderer, pulse);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}