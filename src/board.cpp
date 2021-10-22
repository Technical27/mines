#include "board.hpp"
#include <chrono>
#include <cstdlib>

static const char *TITLE = "Minesweeper";

void Board::incrementIfNotMine(int x, int y) {
  auto &state = tiles[y][x].state;
  switch (state) {
  case TILE_STATE_AIR:
    state = TILE_STATE_1;
    break;
  case TILE_STATE_1:
    state = TILE_STATE_2;
    break;
  case TILE_STATE_2:
    state = TILE_STATE_3;
    break;
  case TILE_STATE_3:
    state = TILE_STATE_4;
    break;
  case TILE_STATE_4:
    state = TILE_STATE_5;
    break;
  case TILE_STATE_5:
    state = TILE_STATE_6;
    break;
  case TILE_STATE_6:
    state = TILE_STATE_7;
    break;
  case TILE_STATE_7:
    state = TILE_STATE_8;
    break;
  case TILE_STATE_MINE:
  case TILE_STATE_8:
    break;
  }
}

void Board::markTiles(int x, int y) {
  incrementIfNotMine(x - 1, y);
  incrementIfNotMine(x + 1, y);

  incrementIfNotMine(x - 1, y - 1);
  incrementIfNotMine(x, y - 1);
  incrementIfNotMine(x + 1, y - 1);

  incrementIfNotMine(x - 1, y + 1);
  incrementIfNotMine(x, y + 1);
  incrementIfNotMine(x + 1, y + 1);
}

Board::Board(SDL_Surface *scr) {
  screen = scr;
  font = nSDL_LoadFont(NSDL_FONT_TINYTYPE, 29, 43, 61);

  boardRect.x = 64;
  boardRect.y = 32;
  boardRect.w = screen->w - 128;
  boardRect.h = screen->h - 48;

  cursorRect.w = 24;
  cursorRect.h = 24;

  titleWidth = (screen->w / 2) - (nSDL_GetStringWidth(font, TITLE) / 2);

  for (int i = 1; i < 8; i++) {
    SDL_Rect line;
    line.y = boardRect.y + ((boardRect.h / 8) * i);
    line.w = boardRect.w;
    line.x = boardRect.x;
    line.h = 1;

    verticalLines[i - 1] = line;
  }

  for (int i = 1; i < 8; i++) {
    SDL_Rect line;
    line.x = boardRect.x + ((boardRect.w / 8) * i);
    line.h = boardRect.h;
    line.y = boardRect.y;
    line.w = 1;

    horizontalLines[i - 1] = line;
  }

  std::mt19937 rng(
      std::chrono::system_clock().now().time_since_epoch().count());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 7);
  std::vector<Tile> row;
  row.assign(8, Tile());
  tiles.assign(8, row);

  for (int i = 0; i < 10; i++) {
    bool duplicate = true;
    int randX, randY;

    while (duplicate) {
      randX = dist(rng);
      randY = dist(rng);
      duplicate = tiles[randY][randX].state == TILE_STATE_MINE;
    }

    tiles[randY][randX].state = TILE_STATE_MINE;
    markTiles(randX, randY);
  }
}

// Screen is 320x240

static void drawRectOutline(SDL_Surface *screen, SDL_Rect rect, int w,
                            uint32_t color) {
  int halfW = w / 2;

  int lineWidth = w - halfW;
  SDL_Rect base = rect;
  base.x = rect.x - halfW;
  base.y = rect.y - halfW;
  base.w = rect.w + halfW;
  base.h = rect.h + halfW;

  SDL_Rect line = base;
  line.h = lineWidth;
  SDL_FillRect(screen, &line, color);

  line = base;
  line.y = base.h + base.y;
  line.h = lineWidth;
  line.w = base.w + lineWidth;
  SDL_FillRect(screen, &line, color);

  line = base;
  line.x = base.w + base.x;
  line.w = lineWidth;
  line.h = base.h + lineWidth;
  SDL_FillRect(screen, &line, color);

  line = base;
  line.w = lineWidth;
  SDL_FillRect(screen, &line, color);
};

void Board::draw() {
  // Fill in background
  SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 184, 200, 222));

  // Fill in the background of the main board
  SDL_FillRect(screen, &boardRect, SDL_MapRGB(screen->format, 160, 160, 180));

  // Draw and center the title
  nSDL_DrawString(screen, font, titleWidth, 10, TITLE);

  // Draw vertical lines
  for (int i = 0; i < 7; i++) {
    SDL_FillRect(screen, &verticalLines[i],
                 SDL_MapRGB(screen->format, 140, 140, 160));
  }

  // Draw horizontal lines
  for (int i = 0; i < 7; i++) {
    SDL_FillRect(screen, &horizontalLines[i],
                 SDL_MapRGB(screen->format, 140, 140, 160));
  }

  // Render tiles
  SDL_Rect tileRect;
  tileRect.w = 24;
  tileRect.h = 24;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (tiles[i][j].state != TILE_STATE_AIR) {
        tileRect.x = (boardRect.x + ((boardRect.w / 8) * j));
        tileRect.y = (boardRect.y + ((boardRect.h / 8) * i));
        if (tiles[i][j].state == TILE_STATE_MINE) {
          SDL_FillRect(screen, &tileRect,
                       SDL_MapRGB(screen->format, 100, 100, 100));
        } else {
          SDL_FillRect(screen, &tileRect,
                       SDL_MapRGB(screen->format,
                                  128 + (16 * (tiles[i][j].state + 1)), 50,
                                  50));
        }
      }
    }
  }

  // Draw the "cursor"
  cursorRect.x = (boardRect.x + ((boardRect.w / 8) * cursorX));
  cursorRect.y = (boardRect.y + ((boardRect.h / 8) * cursorY));
  drawRectOutline(screen, cursorRect, 3,
                  SDL_MapRGB(screen->format, 100, 100, 100));
}

void Board::moveLeft() {
  if (cursorX > 0) {
    cursorX--;
  }
}
void Board::moveRight() {
  if (cursorX < 7) {
    cursorX++;
  }
}
void Board::moveUp() {
  if (cursorY > 0) {
    cursorY--;
  }
}
void Board::moveDown() {
  if (cursorY < 7) {
    cursorY++;
  }
}

Board::~Board() { nSDL_FreeFont(font); }
