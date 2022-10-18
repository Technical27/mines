#pragma once

enum TileState {
  TILE_STATE_1,
  TILE_STATE_2,
  TILE_STATE_3,
  TILE_STATE_4,
  TILE_STATE_5,
  TILE_STATE_6,
  TILE_STATE_7,
  TILE_STATE_8,
  TILE_STATE_MINE,
  TILE_STATE_AIR,
};

class Tile {
public:
  TileState state = TILE_STATE_AIR;
  bool revealed = false;
  bool flagged = false;
};
