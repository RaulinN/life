#include <stdio.h>

#include "game.h"
#include "log.h"

#define DEFAULT_N_ROWS 12
#define DEFAULT_N_COLS 12


int main(int argc, char *argv[]) {

	int32_t n_rows = DEFAULT_N_ROWS;
	int32_t n_cols = DEFAULT_N_COLS;

	if (argc != 3) {
		FLOG_INFO("Usage: ./life <n_rows> <n_cols>");
		FLOG_INFO("Using default n_rows=%d, n_cols=%d", n_rows, n_cols);
	}

	if (argc == 3) {
		// correct amount of arguments
		if (sscanf(argv[1], "%i", &n_rows) != 1) {
			FLOG_WARN("argument <n_rows> could not be parsed as integer => defaulting to n_rows=%d", n_rows);
		}
		if (sscanf(argv[2], "%i", &n_cols) != 1) {
			FLOG_WARN("argument <n_cols> could not be parsed as integer => defaulting to n_cols=%d", n_cols);
		}
	}

	FLOG_INFO("Starting the game with n_rows=%d, n_cols=%d", n_rows, n_cols);

	start_game(n_rows, n_cols);
	return 0;
}
