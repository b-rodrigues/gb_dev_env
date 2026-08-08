#include "board.h"
#include <string.h>

uint8_t board[BOARD_HEIGHT][BOARD_WIDTH];

void board_init(void) {
    uint8_t r, c;
    for (r = 0; r < BOARD_HEIGHT; r++) {
        for (c = 0; c < BOARD_WIDTH; c++) {
            board[r][c] = 0;
        }
    }
}

uint8_t board_is_occupied(int8_t x, int8_t y) {
    if (x < 0 || x >= BOARD_WIDTH) return 1;
    if (y < 0) return 0; /* Above top wall is allowed for piece spawning */
    if (y >= BOARD_HEIGHT) return 1;
    return board[y][x] != 0;
}

void board_set_cell(uint8_t x, uint8_t y, uint8_t val) {
    if (x < BOARD_WIDTH && y < BOARD_HEIGHT) {
        board[y][x] = val;
    }
}

uint8_t board_check_and_clear_lines(void) {
    int8_t r, c, k;
    uint8_t lines_cleared = 0;

    for (r = BOARD_HEIGHT - 1; r >= 0; r--) {
        uint8_t full = 1;
        for (c = 0; c < BOARD_WIDTH; c++) {
            if (board[r][c] == 0) {
                full = 0;
                break;
            }
        }
        if (full) {
            lines_cleared++;
            /* Shift everything down */
            for (k = r; k > 0; k--) {
                for (c = 0; c < BOARD_WIDTH; c++) {
                    board[k][c] = board[k - 1][c];
                }
            }
            /* Clear top line */
            for (c = 0; c < BOARD_WIDTH; c++) {
                board[0][c] = 0;
            }
            /* Re-check same row index since new row shifted into row r */
            r++;
        }
    }
    return lines_cleared;
}
