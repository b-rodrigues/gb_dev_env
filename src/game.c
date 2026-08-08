#include "game.h"
#include <stdlib.h>

Game g_game;

/* Simple pseudo-random number generator for Game Boy */
static uint8_t next_random_piece(void) {
    g_game.random_seed = (g_game.random_seed * 109 + 89) % 251;
    return g_game.random_seed % NUM_PIECE_TYPES;
}

void game_init(void) {
    board_init();
    g_game.state = GAME_STATE_PLAYING;
    g_game.score = 0;
    g_game.lines = 0;
    g_game.fall_timer = 0;
    g_game.fall_speed = 30; /* Fall every 30 frames (~0.5s) */
    g_game.random_seed = 42;

    g_game.next_type = next_random_piece();
    piece_spawn(&g_game.current_piece, next_random_piece());

    render_board();
    render_next_piece(g_game.next_type);
}

static void try_move_piece(int8_t dx, int8_t dy) {
    Piece test;
    piece_copy(&test, &g_game.current_piece);
    test.x += dx;
    test.y += dy;
    if (!piece_collides(&test)) {
        render_clear_piece(&g_game.current_piece);
        piece_copy(&g_game.current_piece, &test);
    }
}

static void try_rotate_piece(int8_t dir) {
    Piece test;
    piece_copy(&test, &g_game.current_piece);
    test.rotation = (test.rotation + dir + 4) % 4;
    if (!piece_collides(&test)) {
        render_clear_piece(&g_game.current_piece);
        piece_copy(&g_game.current_piece, &test);
    }
}

static void lock_and_spawn(void) {
    uint8_t cleared;
    piece_lock(&g_game.current_piece);
    cleared = board_check_and_clear_lines();
    if (cleared > 0) {
        g_game.lines += cleared;
        g_game.score += cleared * 100;
        /* Increase fall speed slightly as score increases */
        if (g_game.fall_speed > 10) {
            g_game.fall_speed--;
        }
    }
    render_board();

    /* Spawn new piece using next_type, then generate new next_type */
    piece_spawn(&g_game.current_piece, g_game.next_type);
    g_game.next_type = next_random_piece();
    render_next_piece(g_game.next_type);

    if (piece_collides(&g_game.current_piece)) {
        g_game.state = GAME_STATE_GAME_OVER;
    }
}

void game_update(void) {
    g_game.random_seed++;

    if (g_game.state == GAME_STATE_GAME_OVER) {
        if (input_is_pressed(J_START)) {
            game_init();
        }
        return;
    }

    /* Process player input */
    if (input_is_pressed(J_LEFT)) {
        try_move_piece(-1, 0);
    }
    if (input_is_pressed(J_RIGHT)) {
        try_move_piece(1, 0);
    }
    if (input_is_pressed(J_A)) {
        try_rotate_piece(1);
    }
    if (input_is_pressed(J_B)) {
        try_rotate_piece(-1);
    }
    if (input_is_pressed(J_START)) {
        game_init();
        return;
    }

    /* Soft drop on Down press or hold */
    if (input_is_pressed(J_DOWN) || (input_is_down(J_DOWN) && (g_game.fall_timer % 3 == 0))) {
        Piece test;
        piece_copy(&test, &g_game.current_piece);
        test.y += 1;
        if (!piece_collides(&test)) {
            render_clear_piece(&g_game.current_piece);
            piece_copy(&g_game.current_piece, &test);
            g_game.fall_timer = 0;
        } else {
            lock_and_spawn();
            return;
        }
    }

    /* Automatic falling */
    g_game.fall_timer++;
    if (g_game.fall_timer >= g_game.fall_speed) {
        Piece test;
        piece_copy(&test, &g_game.current_piece);
        g_game.fall_timer = 0;
        test.y += 1;
        if (!piece_collides(&test)) {
            render_clear_piece(&g_game.current_piece);
            piece_copy(&g_game.current_piece, &test);
        } else {
            lock_and_spawn();
        }
    }
}

void game_render(void) {
    if (g_game.state == GAME_STATE_PLAYING) {
        render_piece(&g_game.current_piece);
    }
    render_ui(g_game.score, g_game.lines, g_game.state == GAME_STATE_GAME_OVER);
}
