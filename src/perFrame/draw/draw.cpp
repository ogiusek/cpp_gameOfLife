#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <functional>

using namespace std;

void Draw(Window *window, FPS *fps, vector<function<void(Window *)>> toDraw)
{
  // Clear the screen
  SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
  SDL_RenderClear(window->renderer);

  for (auto method : toDraw)
    method(window);

  DrawText(window, 0, 0, (to_string(fps->fps_in_last_second) + "FPS"));
  // Draw::Text(gameState, 0, 0, (to_string(gameState->frames.fps) + "FPS"));
  // // Draw a rectangle
  // SDL_Rect rect = {100, 100, 200, 200};
  // SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
  // SDL_RenderFillRect(window->renderer, &rect);

  // Update the screen
  SDL_RenderPresent(window->renderer);
}