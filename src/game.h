#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "board.h"
#include "piece.h"
#include "input.h"
#include "render.h"

typedef enum {
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_GAME_OVER
} GameState;

typedef struct {
    GameState state;
    Piece current_piece;
    uint8_t next_type;
    uint16_t score;
    uint16_t lines;
    uint8_t fall_timer;
    uint8_t fall_speed;
    uint8_t random_seed;
} Game;

extern Game g_game;

void game_init(void);
void game_update(void);
void game_render(void);

#endif /* GAME_H */
