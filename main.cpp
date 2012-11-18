#include <iostream>
#include <stdint.h>

#include "mm.h"


static const uint64_t RIGHT_3_BITS = ((1 << 24) - 1);

static uint64_t game_count=0;

static inline
void incr_counter(void (*cb)()) {
    game_count++;
    if (! (game_count & RIGHT_3_BITS)) {
        std::cout << "Running; count is " << game_count << std::endl;
        if (cb != NULL)
            (*cb)();
    }
}


#ifdef MAIN_IS_PRINT

    void print_board(const Board &b) {
        b.print_board();
    }

    void main_print_boards() {
        Board::iter_boards(print_board);
    }

    void (*mmain)() = main_print_boards;

#endif


#ifdef MAIN_IS_PLAY

    static const int MAX_MOVES = 16; /* should be enough */

    static uint64_t histogram[MAX_MOVES] = {};

    void print_histogram() {
        int max_moves_with_games;

        for (max_moves_with_games = MAX_MOVES - 1;
             max_moves_with_games > 0; /* > instead of >= is intentional */
             max_moves_with_games --)
        {
            if (histogram[max_moves_with_games])
                break;
        }

        for (int m = 0;  m <= max_moves_with_games;  m++) {
            std::cout << " games[" << m << " moves]"
                         " = " << histogram[m] << std::endl;
        }
    }

    void moves_to_histogram(const Board &b) {
        int moves = play(b);
        assert(moves < MAX_MOVES);
        histogram[moves] ++;
        incr_counter(print_histogram);
    }

    void main_play_boards() {
        Board::iter_boards(moves_to_histogram);
        std::cout << "Done." << std::endl;
        print_histogram();
    }

    void (*mmain)() = main_play_boards;

#endif


#ifdef MAIN_IS_COUNT

    void incr(const Board &b) {
        incr_counter(0);
    }

    void main_count_boards() {
        Board::iter_boards(incr);
        std::cout << "Done! Count is " << game_count<< std::endl;
    }

    void (*mmain)() = main_count_boards;

#endif


int
main(int argc, char **argv) {
    mmain();
    return 0;
}
