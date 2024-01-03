//
// Created by Raulin Nicolas on 02.01.24.
//

#pragma once

#include <stdint.h>

#include "board.h"

#include "input.h"


#define GAME_SPEED_MULTIPLIER_MIN 1
#define GAME_SPEED_MULTIPLIER_MAX 8

typedef enum {
	GAME_PHASE_PLAY,
	GAME_PHASE_PAUSE,
} GamePhase;

typedef struct {
	BoardState *board_state;			/* current board of cells */

	GamePhase phase;					/* current game phase */
	uint32_t generation;				/* current generation */

	float time;							/* current time */
	float time_next_update;				/* time when the next update will take place */
	float time_next_render;				/* time when the next render will take place */
	uint8_t speed_multiplier;			/* game speed multiplier (1 = normal speed) */

	InputState input_state;				/* input state of the game */

	// pause state
	int32_t cursor_row;					/* row board position of the cell selection cursor */
	int32_t cursor_col;					/* column board position of the cell selection cursor */
} GameState;

/**
 * Initialize a new game
 *
 * Returns NULL if the allocation fails
 *
 * @param board_width The width of the board
 * @param board_height The height of the board
 * @return An new game with a board of size width x height
 */
GameState *game_state_init(int32_t board_width, int32_t board_height);

/**
 * Destroy a game
 *
 * @param game_state The game to destroy
 */
void game_state_free(GameState *game_state);

/**
 * Start the game of life
 *
 * @param n_rows The number of rows in the game
 * @param n_cols The number of columns in the game
 */
void start_game(int32_t n_rows, int32_t n_cols);
