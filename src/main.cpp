#include "main.hpp"

static const uint8_t MINE_COUNT = 16;
static const uint8_t BOARD_WIDTH = 12;
static const uint8_t BOARD_HEIGHT = 9;

int main(void) {
  SDL_Surface *screen;
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
  SDL_ShowCursor(SDL_DISABLE);

  Title title(screen);
  title.run();

  Board board(screen, MINE_COUNT, BOARD_WIDTH, BOARD_HEIGHT);

  bool done = false;
  bool keyHeld = true;

  // Draw the initial state
  board.draw();
  SDL_Flip(screen);

  while (board.state == BOARD_NORMAL && !done) {
    // This horrible hack is necessary to not have keys repeat.
    if (keyHeld) {
      keyHeld =
          isKeyPressed(KEY_NSPIRE_ESC) || isKeyPressed(KEY_NSPIRE_UP) ||
          isKeyPressed(KEY_NSPIRE_SCRATCHPAD) || isKeyPressed(KEY_NSPIRE_VAR) ||
          isKeyPressed(KEY_NSPIRE_CLICK) || isKeyPressed(KEY_NSPIRE_DEL) ||
          isKeyPressed(KEY_NSPIRE_DOWN) || isKeyPressed(KEY_NSPIRE_5) ||
          isKeyPressed(KEY_NSPIRE_8) || isKeyPressed(KEY_NSPIRE_LEFT) ||
          isKeyPressed(KEY_NSPIRE_4) || isKeyPressed(KEY_NSPIRE_RIGHT) ||
          isKeyPressed(KEY_NSPIRE_6) || isKeyPressed(KEY_NSPIRE_DOWNLEFT) ||
          isKeyPressed(KEY_NSPIRE_LEFTUP) ||
          isKeyPressed(KEY_NSPIRE_RIGHTDOWN) ||
          isKeyPressed(KEY_NSPIRE_UPRIGHT) || isKeyPressed(KEY_NSPIRE_TAB);
      SDL_Delay(25);
      continue;
    } else if (isKeyPressed(KEY_NSPIRE_ESC)) {
      done = true;
    } else if (isKeyPressed(KEY_NSPIRE_DEL) || isKeyPressed(KEY_NSPIRE_CLICK) ||
               isKeyPressed(KEY_NSPIRE_SCRATCHPAD)) {
      board.reveal();
      keyHeld = true;
    } else if (isKeyPressed(KEY_NSPIRE_TAB) || isKeyPressed(KEY_NSPIRE_VAR)) {
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
    } else {
      SDL_Delay(25);
      continue;
    }

    board.draw();
    SDL_Flip(screen);

    SDL_Delay(75);
  }

  if (board.state != BOARD_NORMAL) {
    board.draw();
    SDL_Flip(screen);
    while (true) {
      if (keyHeld) {
        keyHeld = isKeyPressed(KEY_NSPIRE_ESC) ||
                  isKeyPressed(KEY_NSPIRE_DEL) ||
                  isKeyPressed(KEY_NSPIRE_CLICK) ||
                  isKeyPressed(KEY_NSPIRE_SCRATCHPAD);
      } else if (isKeyPressed(KEY_NSPIRE_ESC) || isKeyPressed(KEY_NSPIRE_DEL) ||
                 isKeyPressed(KEY_NSPIRE_CLICK) ||
                 isKeyPressed(KEY_NSPIRE_SCRATCHPAD)) {
        break;
      }

      SDL_Delay(10);
    }
  }

  SDL_Quit();
  return 0;
}
