#include "board.hpp"

static const uint8_t TILE_SIZE = 24;

// These need to be options at some point
static const uint8_t MINE_COUNT = 16;
static const uint8_t BOARD_WIDTH = 12;
static const uint8_t BOARD_HEIGHT = 9;

void Board::incrementIfNotMine(uint8_t x, uint8_t y) {
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

void Board::markTiles(uint8_t x, uint8_t y) {
  if (x > 0) {
    incrementIfNotMine(x - 1, y);
    if (y > 0)
      incrementIfNotMine(x - 1, y - 1);
    if (y < BOARD_HEIGHT)
      incrementIfNotMine(x - 1, y + 1);
  }

  if (x < BOARD_WIDTH) {
    incrementIfNotMine(x + 1, y);
    if (y > 0)
      incrementIfNotMine(x + 1, y - 1);
    if (y < BOARD_HEIGHT)
      incrementIfNotMine(x + 1, y + 1);
  }

  if (y > 0)
    incrementIfNotMine(x, y - 1);

  if (y < BOARD_HEIGHT)
    incrementIfNotMine(x, y + 1);
}

SDL_Surface *Board::loadTile(uint16_t *data) {
  SDL_Surface *surface = nSDL_LoadImage(data);
  SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL,
                  SDL_MapRGB(surface->format, 255, 255, 255));
  return surface;
}

Board::Board(SDL_Surface *scr) {
  screen = scr;

  SDL_PixelFormat *fmt = screen->format;
  backgroundColor = SDL_MapRGB(fmt, 184, 200, 222);
  boardColor = SDL_MapRGB(fmt, 160, 160, 180);
  lineColor = SDL_MapRGB(fmt, 140, 140, 160);

  loseColor = SDL_MapRGB(fmt, 200, 0, 0);
  winColor = SDL_MapRGB(fmt, 0, 200, 0);
  revealedTileColor = SDL_MapRGB(fmt, 200, 200, 220);
  cursorColor = SDL_MapRGB(fmt, 100, 100, 100);

  tileSurfaces.reserve(8);
  tileSurfaces.push_back(loadTile(image_tile_1));
  tileSurfaces.push_back(loadTile(image_tile_2));
  tileSurfaces.push_back(loadTile(image_tile_3));
  tileSurfaces.push_back(loadTile(image_tile_4));
  tileSurfaces.push_back(loadTile(image_tile_5));
  tileSurfaces.push_back(loadTile(image_tile_6));
  tileSurfaces.push_back(loadTile(image_tile_7));
  tileSurfaces.push_back(loadTile(image_tile_8));
  tileSurfaces.push_back(loadTile(image_tile_mine));
  tileSurfaces.push_back(loadTile(image_tile_flag));

  boardRect.x = (screen->w - (BOARD_WIDTH * TILE_SIZE)) / 2;
  boardRect.y = (screen->h - (BOARD_HEIGHT * TILE_SIZE)) / 2;
  boardRect.w = BOARD_WIDTH * TILE_SIZE;
  boardRect.h = BOARD_HEIGHT * TILE_SIZE;

  cursorRect.w = TILE_SIZE;
  cursorRect.h = TILE_SIZE;

  verticalLines.reserve(BOARD_HEIGHT);
  for (uint8_t i = 1; i < BOARD_HEIGHT; i++) {
    SDL_Rect line;
    line.y = boardRect.y + ((boardRect.h / BOARD_HEIGHT) * i);
    line.w = boardRect.w;
    line.x = boardRect.x;
    line.h = 1;

    verticalLines[i - 1] = line;
  }

  horizontalLines.reserve(BOARD_WIDTH);
  for (uint8_t i = 1; i < BOARD_WIDTH; i++) {
    SDL_Rect line;
    line.x = boardRect.x + ((boardRect.w / BOARD_WIDTH) * i);
    line.h = boardRect.h;
    line.y = boardRect.y;
    line.w = 1;

    horizontalLines[i - 1] = line;
  }

  std::mt19937 rng(
      std::chrono::system_clock().now().time_since_epoch().count());

  std::uniform_int_distribution<std::mt19937::result_type> widthDist(
      0, BOARD_WIDTH - 1);
  std::uniform_int_distribution<std::mt19937::result_type> heightDist(
      0, BOARD_HEIGHT - 1);

  std::vector<Tile> row;
  row.assign(BOARD_WIDTH, Tile());
  tiles.assign(BOARD_HEIGHT, row);

  for (uint8_t i = 0; i < MINE_COUNT; i++) {
    bool duplicate = true;
    uint8_t randX, randY;

    while (duplicate) {
      randX = widthDist(rng);
      randY = heightDist(rng);
      duplicate = tiles[randY][randX].state == TILE_STATE_MINE;
    }

    tiles[randY][randX].state = TILE_STATE_MINE;
    markTiles(randX, randY);
  }
}

// Screen is 320x240

static void drawRectOutline(SDL_Surface *screen, SDL_Rect rect, uint8_t w,
                            uint32_t color) {
  uint8_t halfW = w / 2;

  uint8_t lineWidth = w - halfW;
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
}

void Board::draw() {
  // Fill in background
  SDL_FillRect(screen, nullptr, backgroundColor);

  // Fill in the background of the main board
  SDL_FillRect(screen, &boardRect, boardColor);

  // Render tiles
  SDL_Rect tileRect;
  tileRect.w = TILE_SIZE;
  tileRect.h = TILE_SIZE;

  SDL_Rect imgRect;
  imgRect.x = 0;
  imgRect.y = 0;
  imgRect.w = TILE_SIZE;
  imgRect.h = TILE_SIZE;

  for (uint8_t i = 0; i < BOARD_HEIGHT; i++) {
    for (uint8_t j = 0; j < BOARD_WIDTH; j++) {
      auto tile = tiles[i][j];
      if (state != BOARD_NORMAL || tile.revealed || tile.flagged) {
        tileRect.x = (boardRect.x + ((boardRect.w / BOARD_WIDTH) * j));
        tileRect.y = (boardRect.y + ((boardRect.h / BOARD_HEIGHT) * i));

        if (state == BOARD_LOSE &&
            ((tile.state == TILE_STATE_MINE && tile.revealed) ||
             (tile.flagged && tile.state != TILE_STATE_MINE))) {
          SDL_FillRect(screen, &tileRect, loseColor);
        } else if (state == BOARD_WIN && tile.state == TILE_STATE_MINE) {
          SDL_FillRect(screen, &tileRect, winColor);
        } else if (!tile.flagged) {
          SDL_FillRect(screen, &tileRect, revealedTileColor);
        }

        if (tile.flagged) {
          SDL_BlitSurface(tileSurfaces[9], &imgRect, screen, &tileRect);
        } else if (tile.state != TILE_STATE_AIR) {
          SDL_BlitSurface(tileSurfaces[tile.state], &imgRect, screen,
                          &tileRect);
        }
      }
    }
  }

  // Draw vertical lines
  for (uint8_t i = 0; i < BOARD_HEIGHT - 1; i++) {
    SDL_FillRect(screen, &verticalLines[i], lineColor);
  }

  // Draw horizontal lines
  for (uint8_t i = 0; i < BOARD_WIDTH - 1; i++) {
    SDL_FillRect(screen, &horizontalLines[i], lineColor);
  }

  // Draw the borders
  drawRectOutline(screen, boardRect, 3, lineColor);

  if (state == BOARD_NORMAL) {
    // Draw the "cursor"
    cursorRect.x = (boardRect.x + ((boardRect.w / BOARD_WIDTH) * cursorX));
    cursorRect.y = (boardRect.y + ((boardRect.h / BOARD_HEIGHT) * cursorY));
    drawRectOutline(screen, cursorRect, 3, cursorColor);
  }
}

void Board::moveLeft() {
  if (cursorX > 0) {
    cursorX--;
  }
}
void Board::moveRight() {
  if (cursorX < BOARD_WIDTH - 1) {
    cursorX++;
  }
}
void Board::moveUp() {
  if (cursorY > 0) {
    cursorY--;
  }
}
void Board::moveDown() {
  if (cursorY < BOARD_HEIGHT - 1) {
    cursorY++;
  }
}

bool Board::revealTile(uint8_t x, uint8_t y) {
  auto &tile = tiles[y][x];

  if (tile.revealed || tile.flagged)
    return false;

  revealedTiles++;
  tile.revealed = true;

  if (tile.state == TILE_STATE_AIR) {
    if (x > 0) {
      revealTile(x - 1, y);
      if (y > 0)
        revealTile(x - 1, y - 1);
      if (y < BOARD_HEIGHT)
        revealTile(x - 1, y + 1);
    }

    if (x < BOARD_WIDTH) {
      revealTile(x + 1, y);
      if (y > 0)
        revealTile(x + 1, y - 1);
      if (y < BOARD_HEIGHT)
        revealTile(x + 1, y + 1);
    }

    if (y > 0)
      revealTile(x, y - 1);

    if (y < BOARD_HEIGHT)
      revealTile(x, y + 1);
  }

  return tile.state == TILE_STATE_MINE;
}

void Board::reveal() {
  if (revealTile(cursorX, cursorY)) {
    state = BOARD_LOSE;
  } else if ((BOARD_WIDTH * BOARD_HEIGHT) - revealedTiles <= MINE_COUNT) {
    // Win if we have only mines left
    state = BOARD_WIN;
  }
}

void Board::flag() {
  auto &tile = tiles[cursorY][cursorX];

  if (tile.revealed)
    return;

  tile.flagged = !tile.flagged;
}

Board::~Board() {
  for (auto &surface : tileSurfaces) {
    SDL_FreeSurface(surface);
  }
}
