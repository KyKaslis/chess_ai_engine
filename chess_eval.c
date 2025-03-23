#include "chess_eval.h"
#include "chess_board.h"

/*

	Probably the simplest possible evaluation scheme.
	A generally accepted value is given to each piece and 
	whoever has the highest score is in a better position.

*/

int evaluate_position(chessboard cab) {

	int position_evaluation = 0;

	for (int i=0; i<8; i++){

		for (int j=0; j<8; j++){
		
			if (cab.brd[i][j]=='k') position_evaluation += 1000;
			if (cab.brd[i][j]=='K') position_evaluation -= 1000;

			if (cab.brd[i][j]=='q') position_evaluation += 10;
			if (cab.brd[i][j]=='Q') position_evaluation -= 10;

			if (cab.brd[i][j]=='r') position_evaluation += 5;
			if (cab.brd[i][j]=='R') position_evaluation -= 5;

			if (cab.brd[i][j]=='n') position_evaluation += 3;
			if (cab.brd[i][j]=='N') position_evaluation -= 3;

			if (cab.brd[i][j]=='b') position_evaluation += 3;
			if (cab.brd[i][j]=='B') position_evaluation -= 3;

			if (cab.brd[i][j]=='p') position_evaluation += 1;
			if (cab.brd[i][j]=='P') position_evaluation -= 1;


		}

	}

	return position_evaluation;

}