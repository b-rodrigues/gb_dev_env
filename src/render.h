#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include "board.h"
#include "piece.h"

void render_init(void);
void render_board(void);
void render_piece(const Piece *p);
void render_clear_piece(const Piece *p);
void render_ui(uint16_t score, uint16_t lines, uint8_t game_over);
void render_vsync(void);

#endif /* RENDER_H */
