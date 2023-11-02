// #include <time.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <functional>
#include <thread>
#include <cmath>
#include <string>

using namespace std;

#include "include.h"

int main()
{
  Window window = INIT_WINDOW(1280, 720);
  Inputs inputs;

  int tSize = 10, bSize = 200, gap = 0;
  Board board(tSize, bSize, bSize, gap);

  FPS fps(60);

  auto perFrame = [&window, &fps, &inputs, &board]() -> bool
  { return PerFrame(&window, &fps, &inputs, &board); };

  perFrame();

  int running = 1;
  while (running)
  {
    fps.MakeNewFrame();

    if (perFrame())
      break;
  }

  CLOSE_WINDOW(&window);

  return 0;
}