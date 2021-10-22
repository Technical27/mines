#include <SDL/SDL.h>
#include <os.h>
#include <random>
#include <vector>

#include "tile.hpp"

class Board {
private:
  SDL_Surface *screen;
  nSDL_Font *font;

  SDL_Rect boardRect;
  SDL_Rect cursorRect;
  SDL_Rect verticalLines[8];
  SDL_Rect horizontalLines[8];
  int titleWidth;
  int cursorX = 0;
  int cursorY = 0;

  std::vector<std::vector<Tile>> tiles;

  void markTiles(int x, int y);
  void incrementIfNotMine(int x, int y);

public:
  Board(SDL_Surface *scr);

  ~Board();

  void draw();

  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();
};
