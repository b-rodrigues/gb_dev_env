#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>

void sound_init(void);
void sound_update(void);
void sound_play_move(void);
void sound_play_drop(void);
void sound_play_clear(void);

#endif /* SOUND_H */
