#include <iostream>
#include <cassert>

#include "mm.h"

template<int n> /* 0 < n <= BOARD_SIZE */
void
iter(Board &b, int cell_idx,
     int *available,
     Board::board_iterator bi)
{
    for (int val_idx = 0;  val_idx < NUM_POSSIBLE_VALUES;  val_idx++) {
        if (available[val_idx]) {
            available[val_idx] --;
            b.cells[cell_idx] = POSSIBLE_VALUES[val_idx];
            iter<n-1>(b, cell_idx+1, available, bi);
            available[val_idx] ++;
        }
    }
}

template<>
inline
void
iter<0>(Board &b, int cell_idx,
        int *available,
        Board::board_iterator bi)
{
    bi(b);
}

void
Board::iter_boards(const board_iterator bi)
{
    Board b;
    int available[BOARD_SIZE];
    for (int i = 0;  i < BOARD_SIZE;  i++)
        available[i] = 2;
    iter<BOARD_SIZE>(b, 0, available, bi);
}

bool
Board::is_valid() const
{
    int seen[NUM_POSSIBLE_VALUES];
    for (int i = 0;  i < NUM_POSSIBLE_VALUES;  i++)
        seen[i] = 0;
    for (int i = 0;  i < BOARD_SIZE; i++)
        seen[this->cells[i] - POSSIBLE_VALUES[0]] ++;
    for (int i = 0;  i< NUM_POSSIBLE_VALUES;  i++)
        if (seen[i] != 2)
            return false;
    return true;
}

void
Board::print_board() const
{
    std::cout << cells << std::endl;
}

int
play(const Board &b)
{
    bool seen[NUM_POSSIBLE_VALUES] = { /* all false */ };

    int flips_good = 0,
        flips_bad = 0;

    int next_to_flip = 0;

    while (next_to_flip < BOARD_SIZE) {
        char flipa = b.cells[next_to_flip ++];
        if (seen[flipa - FIRST_POSSIBLE_VALUE]) {
            char flipb /* = the flipa we've seen before */;
            flips_good ++;
        } else {
            char flipb = b.cells[next_to_flip ++];
            if (flipa == flipb) { /* lucky */
                seen[flipa - FIRST_POSSIBLE_VALUE] = true;
                flips_good ++;
            } else {
                seen[flipa - FIRST_POSSIBLE_VALUE] = true;
                seen[flipb - FIRST_POSSIBLE_VALUE] = true;
                flips_bad ++;
            }
        }
    }

    assert(next_to_flip == BOARD_SIZE);
    for (int i = 0;  i < NUM_POSSIBLE_VALUES;  i++)
        assert(seen[i] == true);

    //return (flips_good + flips_bad);
    return flips_bad;
}

