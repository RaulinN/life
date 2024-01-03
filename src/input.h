//
// Created by Raulin Nicolas on 02.01.24.
//

#pragma once

#include <stdint.h>


typedef struct {
	uint8_t left;			/* arrow left */
	uint8_t right;			/* arrow right */
	uint8_t up;				/* arrow up */
	uint8_t down;			/* arrow down */
	uint8_t a;				/* space bar */
	uint8_t f;				/* letter f */
	uint8_t n;				/* letter n */

	int8_t delta_left;
	int8_t delta_right;
	int8_t delta_up;
	int8_t delta_down;
	int8_t delta_a;
	int8_t delta_f;
	int8_t delta_n;
} InputState;

/**
 * Update the input state
 *
 * @param input_state The input state to update
 * @param key_states The current state of the keyboard
 */
void input_state_update(InputState *input_state, const uint8_t *key_states);
