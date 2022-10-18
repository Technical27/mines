#include <SDL/SDL.h>
#include <vector>

#include "board.hpp"

#pragma once

class Title {
public:
  Title(SDL_Surface *scr);
  Title(Title &&) = default;
  Title(const Title &) = default;
  Title &operator=(Title &&) = default;
  Title &operator=(const Title &) = default;
  ~Title();

  void draw();
  BoardSize run();

private:
  SDL_Surface *screen;
  nSDL_Font *font;
  uint32_t backgroundColor;
  uint8_t difficulty = 1;

  const char *difficultyToName();

  BoardSize difficultyToSize();

  std::vector<uint8_t> lineWidth;
};
