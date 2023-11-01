#include <iostream>
#include <SDL2/SDL.h>
#include <functional>
#include <vector>
#include <cmath>

using namespace std;

class Object
{
public:
  float xPos, yPos;
  int width, height;
};

class Square
{
public:
  int lastToggle = 0;
  int xI, yI,
      gap,
      width, height;

  bool alive = false;

  void Draw(Window *window)
  {
    if (!alive)
      return;
    int xPos = int(float(xI * (width + gap)));
    int yPos = int(float(yI * (height + gap)));

    SDL_Rect rect = {int(xPos * window->scale + window->xOffset), int(yPos * window->scale + window->yOffset),
                     (int)ceil(width * window->scale), (int)ceil(height * window->scale)};
    SDL_Rect screen = {0, 0, window->width, window->height};
    if (!SDL_HasIntersection(&screen, &rect))
      return;

    SDL_RenderFillRect(window->renderer, &rect);
  }

  bool isIn(float scale, int xPos, int yPos)
  {
    int elemXPos = int(xI * (width + gap) * scale),
        elemYPos = int(yI * (height + gap) * scale);

    return (xPos >= elemXPos && elemXPos + width * scale >= xPos) &&
           (yPos >= elemYPos && elemYPos + height * scale >= yPos);
  }

  void toggle()
  {
    int now = SDL_GetTicks();
    if (now < lastToggle + 500)
      return;

    lastToggle = now;
    alive = !alive;
  }

  Square(int _xI, int _yI, int _gap, int _width, int _height)
      : xI(_xI), yI(_yI), gap(_gap), width(_width), height(_height) {}
};

class Board
{
private:
  int gap = 0;
  int tSize = 10;
  int width = 50, height = 15;

  void Restart()
  {
    running = 0;

    board.clear();
    for (int cI = 0; cI < width; cI++)
    {
      board.push_back({});
      for (int sI = 0; sI < height; sI++)
        board.at(cI).push_back(Square(cI, sI, gap, tSize, tSize));
    }
  }

public:
  bool running = 0;

  vector<vector<Square>> board;

  void Input(Window *window, Inputs *inputs)
  {
    if (inputs->isPressed('r'))
      Restart();

    if (inputs->isPressed(32))
      running = !running;

    if (!running && inputs->mouse.isHeld(3))
      for (int cI = 0; cI < board.size(); cI++)
        for (int sI = 0; sI < board.at(cI).size(); sI++)
          if (board.at(cI).at(sI).isIn(window->scale, inputs->mouse.x - window->xOffset, inputs->mouse.y - window->yOffset))
            board.at(cI).at(sI).toggle();
  }

  void Draw(Window *window)
  {
    if (!width || !height)
      return;

    SDL_Rect rect = {(int)floor(window->xOffset), (int)floor(window->yOffset),
                     (int)floor(window->scale * float(width * (tSize + gap) - gap)),
                     (int)floor(window->scale * float(height * (tSize + gap) - gap))};

    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(window->renderer, &rect);

    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
    for (int cI = 0; cI < board.size(); cI++)
      for (int sI = 0; sI < board.at(cI).size(); sI++)
        board.at(cI).at(sI).Draw(window);
  }

  void Update()
  {
    if (!running)
      return;

    vector<vector<Square>> newBoard = board;
    for (int x = 0; x < width; x++)
      for (int y = 0; y < height; y++)
      {
        bool xMinus = x > 0, xPlus = x < width - 1,
             yMinus = y > 0, yPlus = y < height - 1;
        int neighbours = 0;
        if (xMinus)
          neighbours += (int)board[x - 1][y].alive;
        if (yMinus)
          neighbours += (int)board[x][y - 1].alive;
        if (xPlus)
          neighbours += (int)board[x + 1][y].alive;
        if (yPlus)
          neighbours += (int)board[x][y + 1].alive;

        if (xMinus && yMinus)
          neighbours += (int)board[x - 1][y - 1].alive;
        if (xMinus && yPlus)
          neighbours += (int)board[x - 1][y + 1].alive;
        if (xPlus && yMinus)
          neighbours += (int)board[x + 1][y - 1].alive;
        if (xPlus && yPlus)
          neighbours += (int)board[x + 1][y + 1].alive;

        if (neighbours == 3 || (neighbours == 2 && board[x][y].alive))
          newBoard[x][y].alive = 1;
        else
          newBoard[x][y].alive = 0;
      }

    for (int x = 0; x < width; x++)
      for (int y = 0; y < height; y++)
        if (board[x][y].alive != newBoard[x][y].alive)
        {
          board = newBoard;
          return;
        }
    running = 0;
  }

  Board(int _tSize, int _width, int _height, int _gap = 0)
      : tSize(_tSize), width(_width), height(_height), gap(_gap)
  {
    Restart();
  }
};