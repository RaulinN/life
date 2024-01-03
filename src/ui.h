//
// Created by Raulin Nicolas on 02.01.24.
//

#pragma once

#include <stdint.h>

#include "SDL.h"
#include "SDL_ttf.h"

#include "color.h"
#include "game.h"
#include "board.h"


#define MAX(a, b) \
	(((a) > (b)) ? (a) : (b))
#define ELEMENTS_MARGIN 10

#define SCOREBOARD_WIDTH 200
#define SCOREBOARD_HEIGHT 240
#define SCOREBOARD_PADDING 16
#define SCOREBOARD_STRING_DISTANCE 26

#define CELL_SIZE 30
#define CELL_MARGIN 4
#define CELL_EDGE_SIZE (CELL_SIZE / 8)

#define BOARD_PADDING 8
#define BOARD_BACKGROUND_WIDTH(num_cell_width) \
	(2 * (BOARD_PADDING) + ((num_cell_width) + 1) * (CELL_MARGIN) + (num_cell_width) * (CELL_SIZE))
#define BOARD_BACKGROUND_HEIGHT(num_cell_height) \
	(2 * (BOARD_PADDING) + ((num_cell_height) + 1) * (CELL_MARGIN) + (num_cell_height) * (CELL_SIZE))

#define HELP_HEIGHT 128
#define HELP_PADDING (SCOREBOARD_PADDING)
#define HELP_STRING_DISTANCE (SCOREBOARD_STRING_DISTANCE)
#define HELP_BACKGROUND_WIDTH(num_cell_width) \
	((SCOREBOARD_WIDTH) + (ELEMENTS_MARGIN) + BOARD_BACKGROUND_WIDTH(num_cell_width))

#define WINDOW_WIDTH(num_cell_width) \
	(2 * (ELEMENTS_MARGIN) + HELP_BACKGROUND_WIDTH(num_cell_width))
#define WINDOW_HEIGHT(num_cell_height) \
	(3 * (ELEMENTS_MARGIN) + MAX(SCOREBOARD_HEIGHT, BOARD_BACKGROUND_HEIGHT(num_cell_height)) + HELP_HEIGHT)

#define TARGET_FPS 30
#define DELTA_TIME_NEXT_FRAME (1.0f / TARGET_FPS)


typedef enum {
	TEXT_ALIGN_LEFT,
	TEXT_ALIGN_CENTER,
	TEXT_ALIGN_RIGHT
} TextAlignment;



/**
 * Draw a rectangle of the colour color, of size (width x height) at position (x, y)
 *
 * @param renderer The renderer used to draw the outline
 * @param x The x-axis position of the outline
 * @param y The y-axis position of the outline
 * @param width The width of the outline
 * @param height The height of the outline
 * @param color The color of the outline
 */
void fill_rect(
		SDL_Renderer *renderer,
		int32_t x, int32_t y,
		int32_t width, int32_t height,
		Color color
);

/**
 * Draw a rectangle outline of the colour color, of size (width x height) at position (x, y)
 *
 * @param renderer The renderer used to draw the rectangle
 * @param x The x-axis position of the rectangle
 * @param y The y-axis position of the rectangle
 * @param width The width of the rectangle
 * @param height The height of the rectangle
 * @param color The color of the rectangle
 */
void draw_rect(
		SDL_Renderer *renderer,
		int32_t x, int32_t y,
		int32_t width, int32_t height,
		Color color
);



/**
 * Draw the cell located at position (row x col)
 *
 * @param renderer The renderer used to draw
 * @param value The value of the cell (live or dead)
 * @param row The row of the cell
 * @param col The column of the cell
 * @param offset_x The x-axis offset at which to start drawing
 * @param offset_y The y-axis offset at which to start drawing
 */
void draw_cell(
		SDL_Renderer *renderer,
		CellState value,
		int32_t row, int32_t col,
		int32_t offset_x, int32_t offset_y
);

/**
 * Draw the cell selection cursor located at position (row x col)
 *
 * @param renderer The renderer used to draw
 * @param font The font to use to draw
 * @param row The row of the cell
 * @param col The column of the cell
 * @param offset_x The x-axis offset at which to start drawing
 * @param offset_y The y-axis offset at which to start drawing
 */
void draw_cursor(
		SDL_Renderer *renderer,
		TTF_Font *font,
		int32_t row, int32_t col,
		int32_t offset_x, int32_t offset_y
);

/**
 * Draw the game board
 *
 * @param renderer The renderer used to draw
 * @param board_state The board to draw
 * @param offset_x The x-axis offset at which to start drawing
 * @param offset_y The y-axis offset at which to start drawing
 */
void draw_board(
		SDL_Renderer *renderer,
		const BoardState *board_state,
		int32_t offset_x, int32_t offset_y
);

/**
 * Draw the string text at position (x, y)
 *
 * @param renderer The renderer used to draw
 * @param font The font to use to draw
 * @param text The text to display
 * @param x The x-axis offset at which to start drawing
 * @param y The y-axis offset at which to start drawing
 * @param alignment The text alignment
 * @param color The color of the text
 */
void draw_string(
		SDL_Renderer *renderer,
		TTF_Font *font,
		const char *text,
		int32_t x, int32_t y,
		TextAlignment alignment,
		Color color
);

/**
 * Draw the game scoreboard
 *
 * @param renderer The renderer used to draw
 * @param game_state The game state
 * @param font The font to use to draw
 * @param offset_x The x-axis offset at which to start drawing
 * @param offset_y The y-axis offset at which to start drawing
 */
void draw_scoreboard(
		SDL_Renderer *renderer,
		const GameState *game_state,
		TTF_Font *font,
		int32_t offset_x, int32_t offset_y
);

/**
 * Draw the help notice
 *
 * @param renderer The renderer used to draw
 * @param font The font to use to draw
 * @param game_state The current game state
 * @param offset_x The x-axis offset at which to start drawing
 * @param offset_y The y-axis offset at which to start drawing
 */
void draw_help(
		SDL_Renderer *renderer,
		TTF_Font *font,
		GameState *game_state,
		int32_t offset_x, int32_t offset_y
);
