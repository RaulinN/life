//
// Created by Raulin Nicolas on 03.01.24.
//

#pragma once

#include <stdint.h>

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} Color;

typedef enum {
	COLOR_WHITE,
	COLOR_BLACK,
	COLOR_GRAY_BASE,
	COLOR_GRAY_LIGHT,
	COLOR_GRAY_DARK,
	COLOR_GRAY_BACKGROUND,
	COLOR_PURPLE_BYZANTIUM,
} COLOR_LABEL;

static const Color COLORS[] = {
		{ 0xFF, 0xFF, 0xFF, 0xFF }, // white
		{ 0x00, 0x00, 0x00, 0xFF }, // black
		{ 0x97, 0x97, 0x97, 0xFF }, // gray base
		{ 0xC5, 0xC5, 0xC5, 0xFF }, // gray light
		{ 0x69, 0x69, 0x69, 0xFF }, // gray dark
		{ 0x2B, 0x2A, 0x33, 0xFF }, // gray background
		{ 0x70, 0x29, 0x63, 0xFF }, // byzantium (purple)
};
