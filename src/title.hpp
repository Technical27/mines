#include <SDL/SDL.h>

enum TitleState { TITLE_INTRO, TITLE_SETTINGS };

class Title {
public:
  Title(SDL_Surface *scr);
  Title(Title &&) = default;
  Title(const Title &) = default;
  Title &operator=(Title &&) = default;
  Title &operator=(const Title &) = default;
  ~Title();

  void draw();
  void run();

private:
  SDL_Surface *screen;
  nSDL_Font *font;
  uint32_t backgroundColor;

  uint8_t line1Width;
  uint8_t line2Width;
  uint8_t line3Width;

  TitleState state = TITLE_INTRO;
};
