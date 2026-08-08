#include <gb/gb.h>
#include "game.h"
#include "input.h"
#include "render.h"

void main(void) {
    render_init();
    game_init();

    while (1) {
        input_update();
        game_update();
        game_render();
        render_vsync();
    }
}
