//
// Created by Raulin Nicolas on 02.01.24.
//

#pragma once

#include <stdint.h>


// typedef enum { CELL_DEAD, CELL_ALIVE } CellState;
typedef uint8_t CellState;

typedef struct {
	CellState *data;			/* values of the cells: alive => 1, dead => 0 */

	int32_t width;				/* width of the board */
	int32_t height;				/* height of the board */
} BoardState;

/**
 * Initialize a new board
 *
 * Returns NULL if the allocation fails
 *
 * @param width The width of the board
 * @param height The height of the board
 * @return An empty board of size width x height
 */
BoardState *board_state_init(int32_t width, int32_t height);

/**
 * Destroy a board
 *
 * @param board_state The board to destroy
 */
void board_state_free(BoardState *board_state);

/**
 * Display the state of a board
 *
 * @param board_state The board to display
 */
void board_state_display(BoardState *board_state);

/**
 * Retrieve the value of the cell located at position (row, col) on a board
 *
 * @param board_state The board where the cell is located
 * @param row The row the cell is located
 * @param col The column the cell is located
 * @return The value of the cell
 */
CellState board_state_get(const BoardState *board_state, int32_t row, int32_t col);

/**
 * Set the value of the cell located at position (row, col) on a board
 *
 * @param board_state The board where the cell is located
 * @param row The row the cell is located
 * @param col The column the cell is located
 * @param value The value the cell should have
 */
void board_state_set(BoardState *board_state, int32_t row, int32_t col, CellState value);

/**
 * Flip the value of the cell located at position (row, col) on a board
 *
 * @param board_state The board where the cell is located
 * @param row The row the cell is located
 * @param col The column the cell is located
 */
void board_state_flip(BoardState *board_state, int32_t row, int32_t col);

/**
 * Compute the amount of live neighbors for cell located at (row, col)
 *
 * @param board_state The board where the cell is located
 * @param row The row the cell is located
 * @param col The column the cell is located
 * @return The number of live neighbors the cell has
 */
uint8_t compute_live_neighbors(BoardState *board_state, int32_t row, int32_t col);

/**
 * Update the board going forward one generation
 *
 * @param board_state The board to update
 * @return The updated board state
 */
BoardState *board_state_update(BoardState *board_state);
