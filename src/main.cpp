#include "main.hpp"

int main(void) {
  SDL_Surface *screen;
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
  /* SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
   */
  SDL_ShowCursor(SDL_DISABLE);

  Board board(screen);

  bool done = false;
  bool keyHeld = false;

  while (board.state == BOARD_NORMAL && !done) {
    // This horrible hack is necessary to not have keys repeat.
    if (keyHeld) {
      keyHeld = isKeyPressed(KEY_NSPIRE_ESC) || isKeyPressed(KEY_NSPIRE_UP) ||
                isKeyPressed(KEY_NSPIRE_SCRATCHPAD) ||
                isKeyPressed(KEY_NSPIRE_VAR) || isKeyPressed(KEY_NSPIRE_DEL) ||
                isKeyPressed(KEY_NSPIRE_DOWN) || isKeyPressed(KEY_NSPIRE_5) ||
                isKeyPressed(KEY_NSPIRE_8) || isKeyPressed(KEY_NSPIRE_LEFT) ||
                isKeyPressed(KEY_NSPIRE_4) || isKeyPressed(KEY_NSPIRE_RIGHT) ||
                isKeyPressed(KEY_NSPIRE_6) ||
                isKeyPressed(KEY_NSPIRE_DOWNLEFT) ||
                isKeyPressed(KEY_NSPIRE_LEFTUP) ||
                isKeyPressed(KEY_NSPIRE_RIGHTDOWN) ||
                isKeyPressed(KEY_NSPIRE_UPRIGHT);
    } else if (isKeyPressed(KEY_NSPIRE_ESC)) {
      done = true;
    } else if (isKeyPressed(KEY_NSPIRE_DEL) || isKeyPressed(KEY_NSPIRE_CLICK)) {
      board.reveal();
      keyHeld = true;
    } else if (isKeyPressed(KEY_NSPIRE_SCRATCHPAD) ||
               isKeyPressed(KEY_NSPIRE_VAR)) {
      board.flag();
      keyHeld = true;
    } else if (isKeyPressed(KEY_NSPIRE_DOWN) || isKeyPressed(KEY_NSPIRE_5)) {
      board.moveDown();
      keyHeld = true;
    } else if (isKeyPressed(KEY_NSPIRE_UP) || isKeyPressed(KEY_NSPIRE_8)) {
      board.moveUp();
      keyHeld = true;
    } else if (isKeyPressed(KEY_NSPIRE_LEFT) || isKeyPressed(KEY_NSPIRE_4)) {
      board.moveLeft();
      keyHeld = true;
    } else if (isKeyPressed(KEY_NSPIRE_RIGHT) || isKeyPressed(KEY_NSPIRE_6)) {
      board.moveRight();
      keyHeld = true;
    } else if (isKeyPressed(KEY_NSPIRE_DOWNLEFT)) {
      board.moveDown();
      board.moveLeft();
      keyHeld = true;
    } else if (isKeyPressed(KEY_NSPIRE_LEFTUP)) {
      board.moveUp();
      board.moveLeft();
      keyHeld = true;
    } else if (isKeyPressed(KEY_NSPIRE_RIGHTDOWN)) {
      board.moveDown();
      board.moveRight();
      keyHeld = true;
    } else if (isKeyPressed(KEY_NSPIRE_UPRIGHT)) {
      board.moveUp();
      board.moveRight();
      keyHeld = true;
    }

    board.draw();
    SDL_Flip(screen);

    SDL_Delay(50);
  }

  if (board.state != BOARD_NORMAL) {
    board.draw();
    SDL_Flip(screen);
    while (true) {
      if (keyHeld) {
        keyHeld = isKeyPressed(KEY_NSPIRE_ESC) ||
                  isKeyPressed(KEY_NSPIRE_DEL) ||
                  isKeyPressed(KEY_NSPIRE_CLICK);
      } else if (isKeyPressed(KEY_NSPIRE_ESC) || isKeyPressed(KEY_NSPIRE_DEL) ||
                 isKeyPressed(KEY_NSPIRE_CLICK)) {
        break;
      }
    }
  }

  SDL_Quit();
  return 0;
}
