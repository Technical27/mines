#include "title.hpp"

static std::vector<const char *> text = {
    "Minesweeper",
    "Press del/scratchpad or click to start",
    "Press left/right to change difficulty",
};

Title::Title(SDL_Surface *scr) {
  screen = scr;
  font = nSDL_LoadFont(NSDL_FONT_TINYTYPE, 29, 43, 61);
  uint8_t half = (screen->w / 2);

  for (const char *line : text) {
    lineWidth.push_back(half - (nSDL_GetStringWidth(font, line) / 2));
  }
  backgroundColor = SDL_MapRGB(screen->format, 184, 200, 222);
}

const char *Title::difficultyToName() {
  switch (difficulty) {
  case 0:
    return "   easy  >";
  case 1:
    return "< medium >";
  case 2:
  default:
    return "<  hard   ";
  }
}

BoardSize Title::difficultyToSize() {
  switch (difficulty) {
  case 0:
    return BOARD_SIZE_SMALL;
  case 1:
    return BOARD_SIZE_MEDIUM;
  case 2:
  default:
    return BOARD_SIZE_LARGE;
  }
}

void Title::draw() {
  SDL_FillRect(screen, nullptr, backgroundColor);
  for (uint8_t i = 0; i < text.size(); i++) {
    nSDL_DrawString(screen, font, lineWidth[i], i * 20 + 20, text[i]);
  }

  char text[22];
  sprintf(text, "difficulty: %s", difficultyToName());

  uint8_t half = (screen->w / 2);
  nSDL_DrawString(screen, font, half - (nSDL_GetStringWidth(font, text) / 2),
                  80, text);
}

std::tuple<BoardSize, bool> Title::run() {
  draw();
  SDL_Flip(screen);

  bool keyHeld = true;

  while (true) {
    if (keyHeld) {
      keyHeld = isKeyPressed(KEY_NSPIRE_DEL) ||
                isKeyPressed(KEY_NSPIRE_CLICK) ||
                isKeyPressed(KEY_NSPIRE_SCRATCHPAD) ||
                isKeyPressed(KEY_NSPIRE_LEFT) ||
                isKeyPressed(KEY_NSPIRE_RIGHT) || isKeyPressed(KEY_NSPIRE_ESC);
    } else if (isKeyPressed(KEY_NSPIRE_DEL) || isKeyPressed(KEY_NSPIRE_CLICK) ||
               isKeyPressed(KEY_NSPIRE_SCRATCHPAD)) {
      break;
    } else if (isKeyPressed(KEY_NSPIRE_ESC)) {
      return std::make_tuple(difficultyToSize(), true);
    } else if (isKeyPressed(KEY_NSPIRE_RIGHT)) {
      keyHeld = true;
      if (difficulty < 2) {
        difficulty++;
      }
    } else if (isKeyPressed(KEY_NSPIRE_LEFT)) {
      keyHeld = true;
      if (difficulty > 0) {
        difficulty--;
      }
    } else {
      SDL_Delay(25);
      continue;
    }

    draw();
    SDL_Flip(screen);
    SDL_Delay(75);
  }

  return std::make_tuple(difficultyToSize(), false);
}

Title::~Title() { nSDL_FreeFont(font); }
