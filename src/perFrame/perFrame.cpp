#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <functional>

using namespace std;

class SomeCursorShit
{
public:
  int x = -1, y = -1;

  void reset()
  {
    x = -1;
    y = -1;
  }

  void set(int _x, int _y)
  {
    x = _x;
    y = _y;
  }
};
SomeCursorShit mama;

void wasd(Window *window, FPS *fps, Inputs *inputs)
{
  float speed = 1 * fps->elapsed_time;
  if (inputs->isHeld('w'))
    window->yOffset += speed;

  if (inputs->isHeld('a'))
    window->xOffset += speed;

  if (inputs->isHeld('s'))
    window->yOffset -= speed;

  if (inputs->isHeld('d'))
    window->xOffset -= speed;
}

void resizing()
{
}

int lastFrame = 0;

bool PerFrame(Window *window, FPS *fps, Inputs *inputs, Board *board)
{
  bool show_performance = false;
  int preformanceTimer = SDL_GetTicks();

  // inputs->coutAll();
  if (!GetInput(inputs) || inputs->isHeld(SDLK_ESCAPE))
    return 1;

  wasd(window, fps, inputs);
  board->Input(window, inputs);

  if (inputs->isPressed(SDLK_F11))
    ToggleFullScreen(window);

  int resize = inputs->mouse.scroll;
  if (resize)
  {
    float last_scale = window->scale;
    window->scale += window->scale * (float(resize) * 1.1) / 10;
    float xDiffrence = (((float)window->width * last_scale) - ((float)window->width * window->scale)),
          yDiffrence = (((float)window->height * last_scale) - ((float)window->height * window->scale));
    float lDist = inputs->mouse.x,
          tDist = inputs->mouse.y;

    // cout << xDiffrence * (lDist / (float)window->width) << " . " << inputs->mouse.x << " mouse:size " << window->width << endl;
    // cout << (lDist / (float)window->width) << " " << (tDist / (float)window->height) << endl;
    // cout << xDiffrence * (float)lDist / (float)window->width << " " << yDiffrence * (float)tDist / (float)window->height << endl;
    // window->xOffset += xDiffrence * (lDist / (float)window->width);
    window->xOffset += xDiffrence * (.5);
    // window->yOffset += yDiffrence * (tDist / (float)window->height);
    window->yOffset += yDiffrence * (.5);
  }

  if (inputs->mouse.isHeld(1)) // move with mouse
  {
    if (mama.x != -1)
    {
      window->xOffset += inputs->mouse.x - mama.x;
      window->yOffset += inputs->mouse.y - mama.y;
    }
    mama.set(inputs->mouse.x, inputs->mouse.y);
  }
  else
    mama.reset();

  if (show_performance)
  {
    cout << "input " << SDL_GetTicks() - preformanceTimer << "ms ";
    preformanceTimer = SDL_GetTicks();
  }

  // update
  lastFrame += fps->elapsed_time;
  while (lastFrame > 0)
  {
    board->Update();
    lastFrame -= 100;
  }

  if (show_performance)
  {
    cout << "update " << SDL_GetTicks() - preformanceTimer << "ms ";
    preformanceTimer = SDL_GetTicks();
  }

  // draw
  auto DrawBackgroundLambda = [](Window *window) -> void
  { DrawBackground(window, 0, 255, 255); };

  auto DrawLambda = [&board](Window *window) -> void
  { board->Draw(window); };

  Draw(window, fps, {DrawBackgroundLambda, DrawLambda});

  if (show_performance)
  {
    cout << "draw " << SDL_GetTicks() - preformanceTimer << "ms\n";
    preformanceTimer = SDL_GetTicks();
  }

  // end
  return 0;
}
