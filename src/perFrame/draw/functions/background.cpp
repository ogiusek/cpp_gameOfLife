void DrawBackground(Window *window, int r, int g, int b, int a = 255)
{
  SDL_Rect rect = {0, 0, window->width, window->height};
  SDL_SetRenderDrawColor(window->renderer, r, g, b, a);
  SDL_RenderFillRect(window->renderer, &rect);
}
