#include "main.hpp"

int main(void) {
  SDL_Surface *screen;
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
  /* SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
   */
  SDL_ShowCursor(SDL_DISABLE);

  Board board(screen);

  SDL_Event event;
  bool done = false;

  while (board.state == BOARD_NORMAL && !done) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_KP_ENTER:
        case SDLK_RETURN:
          board.reveal();
          break;
        case SDLK_ESCAPE:
          done = true;
          break;
        case SDLK_DOWN:
        case SDLK_5:
          board.moveDown();
          break;
        case SDLK_UP:
        case SDLK_8:
          board.moveUp();
          break;
        case SDLK_LEFT:
        case SDLK_4:
          board.moveLeft();
          break;
        case SDLK_RIGHT:
        case SDLK_6:
          board.moveRight();
          break;
        default:
          break;
        }
      }
    }

    board.draw();
    SDL_Flip(screen);

    SDL_Delay(50);
  }

  if (board.state != BOARD_NORMAL) {
    board.draw();
    SDL_Flip(screen);
    done = false;
    while (!done) {
      SDL_WaitEvent(&event);
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_KP_ENTER:
        case SDLK_RETURN:
        case SDLK_ESCAPE:
          done = true;
          break;
        default:
          break;
        }
      }
    }
  }

  SDL_Quit();
  return 0;
}
