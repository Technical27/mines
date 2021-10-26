#include <SDL/SDL.h>
#include <os.h>
#include <random>
#include <vector>

#include "images.hpp"
#include "tile.hpp"

typedef enum { BOARD_NORMAL, BOARD_WIN, BOARD_LOSE } BoardState;

class Board {
private:
  SDL_Surface *screen;
  nSDL_Font *font;

  SDL_Rect boardRect;
  SDL_Rect cursorRect;
  std::vector<SDL_Rect> verticalLines;
  std::vector<SDL_Rect> horizontalLines;
  int titleWidth;
  int revealedTiles = 0;
  int cursorX = 0;
  int cursorY = 0;

  std::vector<std::vector<Tile>> tiles;
  std::vector<SDL_Surface *> tileSurfaces;

  void markTiles(int x, int y);
  void incrementIfNotMine(int x, int y);

  SDL_Surface *loadTile(uint16_t *data);

  bool revealTile(int x, int y);

public:
  Board(SDL_Surface *scr);
  ~Board();

  BoardState state = BOARD_NORMAL;

  void draw();

  void reveal();

  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();
};
