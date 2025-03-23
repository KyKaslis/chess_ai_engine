#ifndef _CHESS_AIH_
#define _CHESS_AIH_

#include "chess_board.h"

chessboard call_hal(chessboard cab, int the_depth, int initial_depth); // ask AI for the next move, initial depth is always the first depth
chessboard generate_next_move(chessboard* cab, int first_move); // generate the next move

#endif