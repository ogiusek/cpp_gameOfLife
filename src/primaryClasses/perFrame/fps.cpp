#include <SDL2/SDL.h>
#include <cmath>
using namespace std;

class FPS
{
private:
  int limit = 0;
  int last_frame = 0;

  void PerformFrame()
  {
    elapsed_time = SDL_GetTicks() - last_frame;
    last_frame = SDL_GetTicks();
  }

  void Delay()
  {
    int wanted_time_between_frames = ceil(1000.0 / (float)limit);
    int time_between_frames = SDL_GetTicks() - last_frame;
    if (time_between_frames < wanted_time_between_frames)
      SDL_Delay(wanted_time_between_frames - time_between_frames);
  }

  bool CanMakeNextFrame()
  {
    return !(ceil(1000.0 / (float)limit) > SDL_GetTicks() - last_frame);
  }

public:
  int elapsed_time = 0;

  // bool MakeNewFrame()
  void MakeNewFrame()
  {
    Delay();
    // bool can = CanMakeNextFrame();
    // if (can)
    PerformFrame();
    // return can;
  }

  FPS(int _limit) : limit(_limit), last_frame(SDL_GetTicks()) {}
};