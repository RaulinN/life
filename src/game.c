//
// Created by Raulin Nicolas on 02.01.24.
//

#include "game.h"
#include <stdlib.h>

#include <SDL.h>

#include "log.h"
#include "ui.h"
#include "input.h"

#define TIME_BETWEEN_UPDATES 0.8f // 800 ms


GameState *game_state_init(int32_t board_width, int32_t board_height) {
	GameState *game_state = (GameState*) calloc(1, sizeof(GameState));
	if (game_state == NULL) {
		LOG_ERROR("memory allocation failed");
		return NULL;
	}

	BoardState *board_state = board_state_init(board_width, board_height);
	if (board_state == NULL) {
		LOG_ERROR("memory allocation failed");
		free(game_state);
		return NULL;
	}

	game_state->board_state = board_state;
	game_state->phase = GAME_PHASE_PAUSE;
	game_state->speed_multiplier = 1;
	game_state->input_state = (InputState){ 0 };

	return game_state;
}

void game_state_free(GameState *game_state) {
	free(game_state->board_state);
	game_state->board_state = NULL;
	free(game_state);
}

void game_state_next_generation(GameState *game_state) {
	BoardState *new_board_state = board_state_update(game_state->board_state);
	if (new_board_state == NULL) {
		LOG_ERROR("new board memory allocation failed");
		exit(EXIT_FAILURE);
	}


	board_state_free(game_state->board_state);
	game_state->board_state = new_board_state;

	const float delta_next_update = TIME_BETWEEN_UPDATES * (1.0f / game_state->speed_multiplier);
	game_state->time_next_update = game_state->time + delta_next_update;
	game_state->generation += 1;
}

void game_state_update_play(GameState *game_state) {
	while (game_state->time >= game_state->time_next_update) {
		// enough time has pass to create the next generation of cells
		game_state_next_generation(game_state);
	}

	if (game_state->input_state.delta_up > 0) {
		// speed the game up
		if (game_state->speed_multiplier < GAME_SPEED_MULTIPLIER_MAX) {
			game_state->speed_multiplier *= 2;
		}
	}
	if (game_state->input_state.delta_down > 0) {
		// slow the game down
		if (game_state->speed_multiplier > GAME_SPEED_MULTIPLIER_MIN) {
			game_state->speed_multiplier /= 2;
		}
	}

	if (game_state->input_state.delta_a > 0) {
		game_state->phase = GAME_PHASE_PAUSE;
	}
}

void game_state_update_pause(GameState *game_state) {

	if (game_state->input_state.delta_left > 0) {
		if (game_state->cursor_col > 0) {
			game_state->cursor_col -= 1;
		}
	}
	if (game_state->input_state.delta_right > 0) {
		if (game_state->cursor_col < game_state->board_state->width - 1) {
			game_state->cursor_col += 1;
		}
	}
	if (game_state->input_state.delta_up > 0) {
		if (game_state->cursor_row > 0) {
			game_state->cursor_row -= 1;
		}
	}
	if (game_state->input_state.delta_down > 0) {
		if (game_state->cursor_row < game_state->board_state->height - 1) {
			game_state->cursor_row += 1;
		}
	}

	if (game_state->input_state.delta_f > 0) {
		// flip the cell pointed by the cursor
		board_state_flip(game_state->board_state, game_state->cursor_row, game_state->cursor_col);
	}

	if (game_state->input_state.delta_n > 0) {
		// advance to the next generation
		game_state_next_generation(game_state);
	}

	if (game_state->input_state.delta_a > 0) {
		game_state->phase = GAME_PHASE_PLAY;
	}
}

void game_state_update(GameState *game_state) {
	switch (game_state->phase) {
		case GAME_PHASE_PLAY:
			game_state_update_play(game_state);
			break;
		case GAME_PHASE_PAUSE:
			game_state_update_pause(game_state);
			break;
	}
}

void game_state_render(GameState *game_state, SDL_Renderer *renderer, TTF_Font *font) {
	while (game_state->time >= game_state->time_next_render) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		int32_t x = ELEMENTS_MARGIN;
		int32_t y = ELEMENTS_MARGIN;

		// draw scoreboard
		draw_scoreboard(renderer, game_state, font, x, y);

		// draw the help notice
		draw_help(renderer, font, game_state, x, y);

		// draw the board
		x += SCOREBOARD_WIDTH + ELEMENTS_MARGIN;
		draw_board(renderer, game_state->board_state, x, y);

		game_state->time_next_render = game_state->time + DELTA_TIME_NEXT_FRAME;


		if (game_state->phase == GAME_PHASE_PAUSE) {
			// render the cursor
			draw_cursor(renderer, font, game_state->cursor_row, game_state->cursor_col, x, y);
		}

		SDL_RenderPresent(renderer);
	}
}

void start_game(int32_t n_rows, int32_t n_cols) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		LOG_ERROR("SDL_INIT error: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if (TTF_Init() < 0) {
		LOG_ERROR("SDL_TTF error: %s", TTF_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	SDL_Window *win = SDL_CreateWindow(
			"Game of Life",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH(n_cols), WINDOW_HEIGHT(n_rows),
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);
	if (win == NULL) {
		LOG_ERROR("SDL_CreateWindow error: %s", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(
			win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (renderer == NULL) {
		LOG_ERROR("SDL_CreateRenderer error: %s", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	const char* font_name = "novem___.ttf";
	TTF_Font *font = TTF_OpenFont(font_name, 20);
	if (font == NULL) {
		LOG_ERROR("TTF_OpenFont error: %s", TTF_GetError());
		FLOG_INFO("the file \"novem___.ttf\" should be in the build folder");
		SDL_Quit();
		exit(EXIT_FAILURE);
	}


	/* initialize game objects */
	GameState *game = game_state_init(n_cols, n_rows);
	if (game == NULL) {
		LOG_ERROR("game creation failed");
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	/* actually run the game */
	int quit = 0;
	while (!quit) {
		// update game timer
		game->time = SDL_GetTicks() / 1000.0f;

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = 1;
			}
		}

		int32_t key_count;
		const uint8_t *key_states = SDL_GetKeyboardState(&key_count);

		if (key_states[SDL_SCANCODE_ESCAPE]) {
			quit = 1;
		}

		input_state_update(&game->input_state, key_states);


		game_state_update(game);
		game_state_render(game, renderer, font);
	}

	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	game_state_free(game);
}
