//
// Created by Raulin Nicolas on 02.01.24.
//

#include "ui.h"


void fill_rect(
		SDL_Renderer *renderer,
		int32_t x, int32_t y,
		int32_t width, int32_t height,
		Color color
) {
	SDL_Rect rect = { .x = x, .y = y, .w = width, .h = height };
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void draw_rect(
		SDL_Renderer *renderer,
		int32_t x, int32_t y,
		int32_t width, int32_t height,
		Color color
) {
	SDL_Rect rect = { .x = x, .y = y, .w = width, .h = height };
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &rect);
}

void draw_cell(
		SDL_Renderer *renderer,
		CellState value,
		int32_t row, int32_t col,
		int32_t offset_x, int32_t offset_y
) {
	const int32_t x = col * CELL_SIZE + (col + 1) * CELL_MARGIN + offset_x;
	const int32_t y = row * CELL_SIZE + (row + 1) * CELL_MARGIN + offset_y;

	Color color_base = (value) ? COLORS[COLOR_GRAY_BASE] : COLORS[COLOR_WHITE];

	fill_rect(renderer, x, y, CELL_SIZE, CELL_SIZE, COLORS[COLOR_GRAY_DARK]);
	fill_rect(renderer, x + CELL_EDGE_SIZE, y, CELL_SIZE - CELL_EDGE_SIZE, CELL_SIZE - CELL_EDGE_SIZE, COLORS[COLOR_GRAY_LIGHT]);
	fill_rect(renderer, x + CELL_EDGE_SIZE, y + CELL_EDGE_SIZE, CELL_SIZE - 2 * CELL_EDGE_SIZE, CELL_SIZE - 2 * CELL_EDGE_SIZE, color_base);
}

void draw_cursor(
		SDL_Renderer *renderer,
		TTF_Font *font,
		int32_t row, int32_t col,
		int32_t offset_x, int32_t offset_y
) {
	int32_t x = col * CELL_SIZE + (col + 1) * CELL_MARGIN + offset_x;
	int32_t y = row * CELL_SIZE + (row + 1) * CELL_MARGIN + offset_y;

	x += CELL_SIZE / 2 + 2 * CELL_EDGE_SIZE + 1; 	// adjustments depending on the font
	y += CELL_SIZE / 2 - CELL_EDGE_SIZE;			// adjustments depending on the font

	draw_string(renderer, font, "x", x, y, TEXT_ALIGN_CENTER, COLORS[COLOR_BLACK]);
}

void draw_board(
		SDL_Renderer *renderer,
		const BoardState *board_state,
		int32_t offset_x, int32_t offset_y
) {
	const int32_t x = offset_x;
	const int32_t y = offset_y;

	const int32_t w = BOARD_BACKGROUND_WIDTH(board_state->width);
	const int32_t h = BOARD_BACKGROUND_HEIGHT(board_state->height);

	fill_rect(renderer, x, y, w, h, COLORS[COLOR_GRAY_BACKGROUND]);

	for (int32_t row = 0; row < board_state->height; row += 1) {
		for (int32_t col = 0; col < board_state->width; col += 1) {
			const CellState value = board_state_get(board_state, row, col);
			draw_cell(renderer, value, row, col, offset_x + BOARD_PADDING, offset_y + BOARD_PADDING);
		}
	}
}


void draw_string(
		SDL_Renderer *renderer,
		TTF_Font *font,
		const char *text,
		int32_t x, int32_t y,
		TextAlignment alignment,
		Color color
) {
	SDL_Color sdl_color = { color.r, color.g, color.b, color.a };
	SDL_Surface *surface = TTF_RenderText_Solid(font, text, sdl_color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect rect;
	rect.y = y;
	rect.w = surface->w;
	rect.h = surface->h;
	switch (alignment) {
		case TEXT_ALIGN_LEFT:
			rect.x = x;
			break;
		case TEXT_ALIGN_CENTER:
			rect.x = x - surface->w / 2;
			break;
		case TEXT_ALIGN_RIGHT:
			rect.x = x - surface->w;
			break;
	}

	SDL_RenderCopy(renderer, texture, 0, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void draw_scoreboard(
		SDL_Renderer *renderer,
		const GameState *game_state,
		TTF_Font *font,
		int32_t offset_x, int32_t offset_y
) {
	// generation, fps, phase
	char buffer[128];

	int32_t x = offset_x;
	int32_t y = offset_y;

	// draw scoreboard background
	fill_rect(renderer, x, y, SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT, COLORS[COLOR_GRAY_BACKGROUND]);

	// draw generation label
	x += SCOREBOARD_PADDING;
	y += SCOREBOARD_PADDING;

	snprintf(buffer, sizeof(buffer), "Generation = %d", game_state->generation);
	draw_string(renderer, font, buffer, x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);

	// draw game phase label
	y += SCOREBOARD_STRING_DISTANCE;

	snprintf(buffer, sizeof(buffer), "Game phase = %d", game_state->phase);
	draw_string(renderer, font, buffer, x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);

	// draw game speed label
	y += SCOREBOARD_STRING_DISTANCE;

	snprintf(buffer, sizeof(buffer), "Game speed = %dx", game_state->speed_multiplier);
	draw_string(renderer, font, buffer, x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);

	// draw game time label
	y += SCOREBOARD_STRING_DISTANCE;

	snprintf(buffer, sizeof(buffer), "Game time  = %.1f", game_state->time);
	draw_string(renderer, font, buffer, x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);

	// draw fps label
	y += SCOREBOARD_STRING_DISTANCE;

	snprintf(buffer, sizeof(buffer), "FPS        = %d", TARGET_FPS);
	draw_string(renderer, font, buffer, x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);

	// draw cursor position
	y += SCOREBOARD_STRING_DISTANCE;
	y += SCOREBOARD_STRING_DISTANCE;

	snprintf(buffer, sizeof(buffer), "Cursor row = %d", game_state->cursor_row);
	draw_string(renderer, font, buffer, x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);
	y += SCOREBOARD_STRING_DISTANCE;
	snprintf(buffer, sizeof(buffer), "Cursor col = %d", game_state->cursor_col);
	draw_string(renderer, font, buffer, x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);
}

int32_t max(int32_t a, int32_t b) {
	return (a > b) ? a : b;
}

void draw_help(
		SDL_Renderer *renderer,
		TTF_Font *font,
		GameState *game_state,
		int32_t offset_x, int32_t offset_y
) {
	const int32_t b_h = BOARD_BACKGROUND_HEIGHT(game_state->board_state->height);

	int32_t x = offset_x;
	int32_t y = offset_y + max(SCOREBOARD_HEIGHT, b_h) + ELEMENTS_MARGIN;

	int32_t w = HELP_BACKGROUND_WIDTH(game_state->board_state->width);

	// draw scoreboard background
	fill_rect(renderer, x, y, w, HELP_HEIGHT, COLORS[COLOR_GRAY_BACKGROUND]);

	x += HELP_PADDING;
	y += HELP_PADDING;
	draw_string(renderer, font, "Press [space] to (un)pause", x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);

	y += HELP_STRING_DISTANCE;
	if (game_state->phase == GAME_PHASE_PAUSE) {
		draw_string(renderer, font, "Press [arrow keys] to move cursor", x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);

		y += HELP_STRING_DISTANCE;
		draw_string(renderer, font, "Press [N] to step", x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);

		y += HELP_STRING_DISTANCE;
		draw_string(renderer, font, "Press [F] to flip cell", x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);
	} else if (game_state->phase == GAME_PHASE_PLAY) {
		draw_string(renderer, font, "Press [Up arrow] to speed up", x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);

		y += HELP_STRING_DISTANCE;
		draw_string(renderer, font, "Press [Down arrow] to speed down", x, y, TEXT_ALIGN_LEFT, COLORS[COLOR_WHITE]);
	}

}
