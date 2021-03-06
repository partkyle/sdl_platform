#ifndef GAME_H
#define GAME_H

#include "common.h"
#include <time.h>

typedef struct game_offscreen_buffer
{
    void *memory;
    int width;
    int height;
    int pitch;
    int bytes_per_pixel;
} game_offscreen_buffer;

typedef struct game_button_state
{
    int half_transition_count;
    bool32 ended_down;
} game_button_state;

typedef struct game_controller_input
{
    bool32 is_connected;
    bool32 is_analog;
    real32 stick_average_x;
    real32 stick_average_y;

    union
    {
        game_button_state buttons[12];
        struct
        {
            game_button_state move_up;
            game_button_state move_down;
            game_button_state move_left;
            game_button_state move_right;

            game_button_state action_up;
            game_button_state action_down;
            game_button_state action_left;
            game_button_state action_right;

            game_button_state left_shoulder;
            game_button_state right_shoulder;

            game_button_state back;
            game_button_state start;

            game_button_state terminator;
        };
    };
} game_controller_input;

typedef struct game_input
{
    union
    {
        game_button_state mouse_buttons[5];
        struct
        {
            game_button_state MouseLeft;
            game_button_state MouseRight;
            game_button_state MouseMiddle;
            game_button_state MouseB1;
            game_button_state MouseB2;
        };
    };

    int32 mouse_x, mouse_y, mouse_z;
    int32 rel_mouse_x, rel_mouse_y;

    real32 dtForFrame;
    time_t t;

    game_controller_input controllers[5];
} game_input;

typedef struct game_memory
{
    bool32 is_initialized;

    uint64 permanent_storage_size;
    void *permanent_storage;

    uint64 transient_storage_size;
    void *transient_storage;
} game_memory;

#define GAME_UPDATE_AND_RENDER(name) int32 name(game_offscreen_buffer *buffer, game_memory *memory, game_input *input)
typedef GAME_UPDATE_AND_RENDER(game_update_and_render);

#define MAX_PATH_LENGTH 1024

typedef struct game_code
{
    void *game_code_dll;

    uint64 DLL_last_write_time;

    game_update_and_render *update_and_render;
} game_code;

typedef struct memory_arena
{
    memory_index size;
    uint8 *base;
    memory_index used;
} memory_arena;

internal void
initialize_arena(memory_arena *arena, memory_index size, uint8 *base)
{
    arena->size = size;
    arena->base = base;
    arena->used = 0;
}

#define push_struct(arena, type) (type *)push_size_(arena, sizeof(type))
#define push_array(arena, count, type) (type *)push_size_(arena, (count)*sizeof(type))

void *
push_size_(memory_arena *arena, memory_index size)
{
    assert((arena->used + size) <= arena->size);
    void *result = arena->base + arena->used;
    arena->used += size;

    return(result);
}

#endif
