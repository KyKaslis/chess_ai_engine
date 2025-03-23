#ifndef _CHESS_BOARDH_
#define _CHESS_BOARDH_

typedef struct chessboard chessboard;

struct chessboard {

	//lower letters = white
	//capital letters = black

	char brd[8][8]; //first bracket is rows counting from down (1, 2, ..., 8), second bracket is columns (a, b, ..., h) counting from left
	int ws_castling_active; //white short castling
	int wl_castling_active; //white long castling
	int bs_castling_active; //black short castling
	int bl_castling_active; //black long castling
	int white_en_pass[8]; //write here the move counter to know if en passant is possible
	int black_en_pass[8]; //write here the move counter to know if en passant is possible
	int move_legit; // 1 if move legit, 0 otherwise
	int score; // the evaluated score of this position to be used by AI for position comparisons
	int all_moves_explored; // when this is 1 all the possible moves from this position have been explored, otherwise 0
	int next_to_play; // 1 white's turn to play, -1 for black
	int check_brd[8][8]; // used by AI to check each square for pieces, 1 = checked, 0 otherwise (if all checked, go to next position)
	int moves_checked; // used by AI to mark which possible moves of the found piece it has checked (if all checked, check_brd turns to 1)
	int start_a; // AI will store in these variables the start and finish positions of the selected move
	int start_b;
	int stop_a;
	int stop_b;
};

chessboard intlz(chessboard cab); //initialize board

void print_board(chessboard cab); //print board to screen

chessboard is_move_legal(chessboard cab, int a, int b, int c, int d, int suppress_output); // return cab.move_legit 1 if move is legal, 0 otherwise   

chessboard move_piece(chessboard cab, int a, int b, int c, int d, int extra_move); //perform a move

int square_in_danger_from_black(chessboard cab, int a, int b); // return 1 if square ab is in danger from black

int square_in_danger_from_white(chessboard cab, int a, int b); // return 1 if square ab is in danger from white

int is_white_king_in_danger(chessboard cab); // return 1 if white king is in danger

chessboard empty_board(chessboard cab); //empty the board

chessboard set_board(chessboard cab, char* the_move); //set the  board

#endif

/*

--King has 10 moves to check--

up, upright, ... , upleft, short castle, long castle

--Queen has 56 moves to check--

right 1, right 2,..., right 7, left 1, ..., left 7
up 1, ..., up 7, down 1, ..., down 7,
upright 1, ..., upright 7, downright 1, ..., downright 7
upleft 1, ..., upleft 7, downleft 1, ..., downleft 7

--Bishop has 28 moves to check--

upright 1, ..., upright 7, downright 1, ..., downright 7
upleft 1, ..., upleft 7, downleft 1, ..., downleft 7

--Rook has 28 moves to check--

right 1, right 2,..., right 7, left 1, ..., left 7
up 1, ..., up 7, down 1, ..., down 7,

--Knight has 8 moves to check--

upright, rightup, rightdown, ..., upleft

--White pawns have 4 moves to check--

up, double up, capture upleft, capture upright

--Black pawns have 4 moves to check--

down, double down, capture downleft, capture downright

*/