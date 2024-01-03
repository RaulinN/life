//
// Created by Raulin Nicolas on 02.01.24.
//

#include "board.h"
#include <stdlib.h>
#include <stdio.h>

#include "log.h"


BoardState *board_state_init(int32_t width, int32_t height) {
	BoardState *board_state = (BoardState*) calloc(1, sizeof(BoardState));
	if (board_state == NULL) {
		LOG_ERROR("memory allocation failed");
		return NULL;
	}

	CellState *data = (CellState*) calloc(width * height, sizeof(CellState));
	if (data == NULL) {
		LOG_ERROR("memory allocation failed");
		free(board_state);
		return NULL;
	}

	board_state->data = data;
	board_state->width = width;
	board_state->height = height;

	return board_state;
}

void board_state_free(BoardState *board_state) {
	free(board_state->data);
	board_state->data = NULL;
	free(board_state);
}

void board_state_display(BoardState *board_state) {
	printf("----- Board state -----\n");
	for (uint32_t row = 0; row < board_state->height; row += 1) {
		for (uint32_t col = 0; col < board_state->width; col += 1) {
			const CellState value = board_state_get(board_state, row, col);
			if (value) {
				printf("[%d] ", value);
			} else {
				printf("[ ] ");
			}
		}
		printf("\n");
	}
}

CellState board_state_get(const BoardState *board_state, int32_t row, int32_t col) {
	return board_state->data[row * board_state->width + col];
}

void board_state_set(BoardState *board_state, int32_t row, int32_t col, CellState value) {
	board_state->data[row * board_state->width + col] = value;
}

void board_state_flip(BoardState *board_state, int32_t row, int32_t col) {
	const CellState value = board_state_get(board_state, row, col);
	board_state_set(board_state, row, col, (value) ? 0 : 1);
}

uint8_t compute_live_neighbors(BoardState *board_state, int32_t row, int32_t col) {
	uint8_t count = 0;
	for (int32_t w_row = row - 1; w_row <= row + 1; w_row += 1) {
		if (w_row < 0 || w_row >= board_state->height) continue;
		for (int32_t w_col = col - 1; w_col <= col + 1; w_col += 1) {
			if (w_col < 0 || w_col >= board_state->width) continue;
			if (w_row == row && w_col == col) continue;
			count += board_state_get(board_state, w_row, w_col);
		}
	}

	return count;
}

BoardState *board_state_update(BoardState *board_state) {
	BoardState *new_board = board_state_init(board_state->width, board_state->height);
	if (new_board == NULL) {
		return NULL;
	}

	for (int32_t row = 0; row < board_state->height; row += 1) {
		for (int32_t col = 0; col < board_state->width; col += 1) {
			const CellState value = board_state_get(board_state, row, col);
			const uint8_t num_neighbors = compute_live_neighbors(board_state, row, col);

			CellState new_value;
			if (value) {
				// if the cell is live
				new_value = (num_neighbors == 2 || num_neighbors == 3) ? 1 : 0;
			} else {
				// if the cell is dead
				new_value = (num_neighbors == 3) ? 1 : 0;
			}

			board_state_set(new_board, row, col, new_value);
		}
	}

	new_board->width = board_state->width;
	new_board->height = board_state->height;

	return new_board;
}
