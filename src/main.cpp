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

  board.draw();
  SDL_Flip(screen);
  while (!done) {
    /* if (isKeyPressed(KEY_NSPIRE_MENU)) { */
    /*   break; */
    /* } */

    /* if (key_held) { */
    /*   key_held = */
    /*       isKeyPressed(KEY_NSPIRE_UPRIGHT) || isKeyPressed(KEY_NSPIRE_LEFTUP)
     * || */
    /*       isKeyPressed(KEY_NSPIRE_DOWNLEFT) || */
    /*       isKeyPressed(KEY_NSPIRE_RIGHTDOWN) || */
    /*       isKeyPressed(KEY_NSPIRE_RIGHT) || isKeyPressed(KEY_NSPIRE_LEFT) ||
     */
    /*       isKeyPressed(KEY_NSPIRE_UP) || isKeyPressed(KEY_NSPIRE_DOWN) || */
    /*       isKeyPressed(KEY_NSPIRE_8) || isKeyPressed(KEY_NSPIRE_4) || */
    /*       isKeyPressed(KEY_NSPIRE_5) || isKeyPressed(KEY_NSPIRE_6); */
    /* } else if (isKeyPressed(KEY_NSPIRE_UPRIGHT)) { */
    /*   board.moveUp(); */
    /*   board.moveRight(); */
    /*   key_held = true; */
    /* } else if (isKeyPressed(KEY_NSPIRE_LEFTUP)) { */
    /*   board.moveUp(); */
    /*   board.moveLeft(); */
    /*   key_held = true; */
    /* } else if (isKeyPressed(KEY_NSPIRE_DOWNLEFT)) { */
    /*   board.moveDown(); */
    /*   board.moveLeft(); */
    /*   key_held = true; */
    /* } else if (isKeyPressed(KEY_NSPIRE_RIGHTDOWN)) { */
    /*   board.moveDown(); */
    /*   board.moveRight(); */
    /*   key_held = true; */
    /* } else if (isKeyPressed(KEY_NSPIRE_LEFT) || isKeyPressed(KEY_NSPIRE_4)) {
     */
    /*   board.moveLeft(); */
    /*   key_held = true; */
    /* } else if (isKeyPressed(KEY_NSPIRE_RIGHT) || isKeyPressed(KEY_NSPIRE_6))
     * { */
    /*   board.moveRight(); */
    /*   key_held = true; */
    /* } else if (isKeyPressed(KEY_NSPIRE_UP) || isKeyPressed(KEY_NSPIRE_8)) {
     */
    /*   board.moveUp(); */
    /*   key_held = true; */
    /* } else if (isKeyPressed(KEY_NSPIRE_DOWN) || isKeyPressed(KEY_NSPIRE_5)) {
     */
    /*   board.moveDown(); */
    /*   key_held = true; */
    /* } */

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
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
        case SDLK_ESCAPE:
          done = true;
          break;
        default:
          break;
        }
      }
    }
    SDL_FillRect(screen, nullptr, 0);
    board.draw();
    SDL_Flip(screen);
  }

  SDL_Quit();
  return 0;
}
