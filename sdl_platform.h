#ifndef SDL_EXAMPLE_H
#define SDL_EXAMPLE_H

#include "SDL.h"
#include "common.h"
#include "game.h"

// TODO(partkyle): handle game.h import here
typedef struct sdl_offscreen_buffer
{
    SDL_Texture *texture;

    game_offscreen_buffer *game_buffer;
} sdl_offscreen_buffer;

typedef struct sdl_window_dimension
{
    int32 width;
    int32 height;
} sdl_window_dimension;

typedef struct platform_dynamic_game
{
    char dll_filename[MAX_PATH_LENGTH];
    char tmp_dll_filename[MAX_PATH_LENGTH];
    char lock_filename[MAX_PATH_LENGTH];
} platform_dynamic_game;

#endif
