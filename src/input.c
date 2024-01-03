//
// Created by Raulin Nicolas on 02.01.24.
//

#include "input.h"

#include <SDL.h>

void input_state_update(InputState *input_state, const uint8_t *key_states) {
	InputState prev_input = *input_state;

	input_state->left = key_states[SDL_SCANCODE_LEFT];
	input_state->right = key_states[SDL_SCANCODE_RIGHT];
	input_state->up = key_states[SDL_SCANCODE_UP];
	input_state->down = key_states[SDL_SCANCODE_DOWN];
	input_state->a = key_states[SDL_SCANCODE_SPACE];
	input_state->f = key_states[SDL_SCANCODE_F];
	input_state->n = key_states[SDL_SCANCODE_N];

	input_state->delta_left = input_state->left - prev_input.left;
	input_state->delta_right = input_state->right - prev_input.right;
	input_state->delta_up = input_state->up - prev_input.up;
	input_state->delta_down = input_state->down - prev_input.down;
	input_state->delta_a = input_state->a - prev_input.a;
	input_state->delta_f = input_state->f - prev_input.f;
	input_state->delta_n = input_state->n - prev_input.n;
}
