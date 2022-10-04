#include "title.hpp"

static const char *NAME = "Minesweeper";
static const char *TEXT1 = "Press del/scratchpad or click to start";
static const char *TEXT2 = "Press menu to change options";

Title::Title(SDL_Surface *scr) {
  screen = scr;
  font = nSDL_LoadFont(NSDL_FONT_TINYTYPE, 29, 43, 61);
  uint8_t half = (screen->w / 2);
  line1Width = half - (nSDL_GetStringWidth(font, NAME) / 2);
  line2Width = half - (nSDL_GetStringWidth(font, TEXT1) / 2);
  line3Width = half - (nSDL_GetStringWidth(font, TEXT2) / 2);
  backgroundColor = SDL_MapRGB(screen->format, 184, 200, 222);
}

void Title::draw() {
  SDL_FillRect(screen, nullptr, backgroundColor);

  if (state == TITLE_INTRO) {
    nSDL_DrawString(screen, font, line1Width, 20, NAME);
    nSDL_DrawString(screen, font, line2Width, 40, TEXT1);
    nSDL_DrawString(screen, font, line3Width, 60, TEXT2);
  } else if (state == TITLE_SETTINGS) {
  }
}

void Title::run() {
  draw();

  SDL_Flip(screen);
  bool keyHeld = false;

  while (true) {
    if (keyHeld) {
      keyHeld = isKeyPressed(KEY_NSPIRE_DEL) ||
                isKeyPressed(KEY_NSPIRE_CLICK) ||
                isKeyPressed(KEY_NSPIRE_SCRATCHPAD);
    } else if (isKeyPressed(KEY_NSPIRE_DEL) || isKeyPressed(KEY_NSPIRE_CLICK) ||
               isKeyPressed(KEY_NSPIRE_SCRATCHPAD)) {
      break;
    }

    SDL_Delay(25);
  }
}

Title::~Title() { nSDL_FreeFont(font); }
