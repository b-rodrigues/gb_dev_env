#include "render.h"
#include <gb/gb.h>

/* Custom 8x8 Tile Data (2bpp format, 16 bytes per tile) */
static const unsigned char TILE_DATA[] = {
    /* Tile 0: Blank */
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    /* Tile 1: Block Pattern 1 (I) */
    0x7E,0x7E,0x42,0x7E,0x42,0x7E,0x42,0x7E,
    0x42,0x7E,0x42,0x7E,0x42,0x7E,0x7E,0x7E,

    /* Tile 2: Block Pattern 2 (J) */
    0x7E,0x7E,0x40,0x7E,0x40,0x7E,0x40,0x7E,
    0x40,0x7E,0x40,0x7E,0x40,0x7E,0x7E,0x7E,

    /* Tile 3: Block Pattern 3 (L) */
    0x7E,0x7E,0x02,0x7E,0x02,0x7E,0x02,0x7E,
    0x02,0x7E,0x02,0x7E,0x02,0x7E,0x7E,0x7E,

    /* Tile 4: Block Pattern 4 (O) */
    0x7E,0x7E,0x42,0x42,0x42,0x42,0x42,0x42,
    0x42,0x42,0x42,0x42,0x42,0x42,0x7E,0x7E,

    /* Tile 5: Block Pattern 5 (S) */
    0x7E,0x7E,0x7E,0x42,0x7E,0x42,0x7E,0x42,
    0x7E,0x42,0x7E,0x42,0x7E,0x42,0x7E,0x7E,

    /* Tile 6: Block Pattern 6 (T) */
    0x7E,0x7E,0x5A,0x7E,0x5A,0x7E,0x5A,0x7E,
    0x5A,0x7E,0x5A,0x7E,0x5A,0x7E,0x7E,0x7E,

    /* Tile 7: Block Pattern 7 (Z) */
    0x7E,0x7E,0x66,0x7E,0x66,0x7E,0x66,0x7E,
    0x66,0x7E,0x66,0x7E,0x66,0x7E,0x7E,0x7E,

    /* Tile 8: Board Frame / Border */
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

static const unsigned char TILE_BLANK = 0;
static const unsigned char TILE_BORDER = 8;

void render_init(void) {
    uint8_t x, y;
    
    /* Load background tile patterns into VRAM starting at index 0 */
    set_bkg_data(0, 9, TILE_DATA);

    /* Clear background map */
    for (y = 0; y < 18; y++) {
        for (x = 0; x < 20; x++) {
            set_bkg_tiles(x, y, 1, 1, &TILE_BLANK);
        }
    }

    /* Draw border around playfield */
    /* Top & bottom borders */
    for (x = BOARD_OFFSET_X - 1; x <= BOARD_OFFSET_X + BOARD_WIDTH; x++) {
        set_bkg_tiles(x, BOARD_OFFSET_Y - 1, 1, 1, &TILE_BORDER);
        set_bkg_tiles(x, BOARD_OFFSET_Y + BOARD_HEIGHT, 1, 1, &TILE_BORDER);
    }
    /* Left & right borders */
    for (y = BOARD_OFFSET_Y; y < BOARD_OFFSET_Y + BOARD_HEIGHT; y++) {
        set_bkg_tiles(BOARD_OFFSET_X - 1, y, 1, 1, &TILE_BORDER);
        set_bkg_tiles(BOARD_OFFSET_X + BOARD_WIDTH, y, 1, 1, &TILE_BORDER);
    }

    SHOW_BKG;
    DISPLAY_ON;
}

void render_board(void) {
    uint8_t r, c;
    for (r = 0; r < BOARD_HEIGHT; r++) {
        for (c = 0; c < BOARD_WIDTH; c++) {
            unsigned char tile = board[r][c];
            set_bkg_tiles(BOARD_OFFSET_X + c, BOARD_OFFSET_Y + r, 1, 1, &tile);
        }
    }
}

void render_piece(const Piece *p) {
    int8_t bx[4], by[4];
    uint8_t i;
    unsigned char tile = p->type + 1;

    piece_get_blocks(p, bx, by);
    for (i = 0; i < 4; i++) {
        if (by[i] >= 0 && by[i] < BOARD_HEIGHT && bx[i] >= 0 && bx[i] < BOARD_WIDTH) {
            set_bkg_tiles(BOARD_OFFSET_X + bx[i], BOARD_OFFSET_Y + by[i], 1, 1, &tile);
        }
    }
}

void render_clear_piece(const Piece *p) {
    int8_t bx[4], by[4];
    uint8_t i;
    unsigned char tile = 0;

    piece_get_blocks(p, bx, by);
    for (i = 0; i < 4; i++) {
        if (by[i] >= 0 && by[i] < BOARD_HEIGHT && bx[i] >= 0 && bx[i] < BOARD_WIDTH) {
            /* Restore board cell if not occupied */
            if (board[by[i]][bx[i]] == 0) {
                set_bkg_tiles(BOARD_OFFSET_X + bx[i], BOARD_OFFSET_Y + by[i], 1, 1, &tile);
            }
        }
    }
}

void render_ui(uint16_t score, uint16_t lines, uint8_t game_over) {
    (void)score;
    (void)lines;
    (void)game_over;
}

void render_vsync(void) {
    vsync();
}
