#pragma once

#include <stdint.h>

static const int NUM_POSSIBLE_VALUES = 8;

static const char POSSIBLE_VALUES[NUM_POSSIBLE_VALUES]
    = {
        /* should be numerically sequential */
        'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h',
      };

static const char FIRST_POSSIBLE_VALUE = 'a';

static const int BOARD_SIZE = 16;

class Board {
    public:
        typedef void (*board_iterator)(const Board&);

        uint8_t cells[BOARD_SIZE + 1]; /* last element of cells[] is a null */

        bool is_valid() const;
        void print_board() const;

	static void iter_boards(board_iterator);

        Board() {
            for (int i=0;  i < (BOARD_SIZE + 1);  i++)
                cells[i] = 0;
        }
};

int play(Board &b);
