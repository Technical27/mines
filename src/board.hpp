#include <SDL/SDL.h>
#include <chrono>
#include <os.h>
#include <random>
#include <tuple>
#include <vector>

#include "images.hpp"
#include "tile.hpp"

#pragma once

enum BoardState { BOARD_NORMAL, BOARD_WIN, BOARD_LOSE };

enum BoardSize { BOARD_SIZE_SMALL, BOARD_SIZE_MEDIUM, BOARD_SIZE_LARGE };

class Board {
private:
  SDL_Surface *screen;

  uint8_t mineCount;
  uint8_t width;
  uint8_t height;

  SDL_Rect boardRect;
  SDL_Rect cursorRect;
  std::vector<SDL_Rect> verticalLines;
  std::vector<SDL_Rect> horizontalLines;
  uint8_t revealedTiles = 0;
  uint8_t cursorX = 0;
  uint8_t cursorY = 0;

  uint32_t backgroundColor;
  uint32_t boardColor;
  uint32_t lineColor;

  uint32_t cursorColor;

  uint32_t loseColor;
  uint32_t winColor;
  uint32_t revealedTileColor;

  std::vector<std::vector<Tile>> tiles;
  std::vector<SDL_Surface *> tileSurfaces;

  void markTiles(uint8_t x, uint8_t y);
  void incrementIfNotMine(uint8_t x, uint8_t y);

  SDL_Surface *loadTile(uint16_t *data);

  bool revealTile(uint8_t x, uint8_t y);

  std::tuple<uint8_t, uint8_t, uint8_t> getSize(BoardSize size);

public:
  Board(SDL_Surface *scr, BoardSize size);
  ~Board();

  Board(Board &&) = default;
  Board(const Board &) = default;
  Board &operator=(Board &&) = default;
  Board &operator=(const Board &) = default;

  BoardState state = BOARD_NORMAL;

  void draw();

  void reveal();

  void flag();

  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();
};
