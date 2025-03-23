#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "chess_board.h"
#include "extr_var.h"
#include "chess_eval.h"
#include "chess_ai.h"


chessboard call_hal(chessboard cab, int the_depth, int initial_depth){

	if (cab.move_legit == 0) {

		return cab;

	}

	if (the_depth == 0){ // end of the tree, evaluate and return

		cab.score = evaluate_position(cab);
		return cab;

	}

	if (abs(evaluate_position(cab))>100) { // a checkmate has happened, no need to explore further

		cab.score = evaluate_position(cab);
		return cab;

	}

	int first_move;
	chessboard next_move;
	chessboard current_move;
	chessboard* this_cab = &cab;

	if (the_depth == initial_depth){ // this tells the move generator to save the first move so it can be played by the AI

		first_move = 1;

	} else {

		first_move = 0;

	}

	next_move = call_hal(generate_next_move(this_cab, first_move), the_depth-1, initial_depth); // create at least one move

	while (cab.all_moves_explored == 0){

		current_move = call_hal(generate_next_move(this_cab, first_move), the_depth-1, initial_depth);

		if (cab.next_to_play < 0){ // black to move

			if (current_move.score < next_move.score && current_move.move_legit == 1) {

				next_move = current_move;

			}

		}

		else { // white to move

			if (current_move.score > next_move.score && current_move.move_legit == 1) {

				next_move = current_move;

			}

		}

	}
	
	return next_move;

}

chessboard generate_next_move(chessboard* cab, int first_move){

	int test_x = -1; // the attempted moves
	int test_y = -1;
	int i=-1;
	int j=-1;

	chessboard tempo = *cab;

	for (i=0; i<8; i++){

		for (j=0; j<8; j++){ // scan each square for pieces

			if (cab->check_brd[j][i] == 1) continue; // if checked move to the next

			if (cab->brd[j][i] == 'r' && cab->next_to_play == 1) { // white rook found and white to play

				while (cab->moves_checked != 28) { // check all the 28 possible white rook moves

					if (cab->moves_checked < 7){ // [0, 6]

						cab->moves_checked++;
						test_x = i+cab->moves_checked;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 14){ // [7, 13]

						cab->moves_checked++;
						test_x = i+7-cab->moves_checked;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 21){ // [14, 20]

						cab->moves_checked++;
						test_x = i;
						test_y = j-14+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else { // [21, 27]

						cab->moves_checked++;
						test_x = i;
						test_y = j+21-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}

					if (tempo.move_legit == 1){

						if (first_move == 1) {

							tempo.start_a = i;
							tempo.start_b = j;
							tempo.stop_a = test_x;
							tempo.stop_b = test_y;

						}

						tempo.all_moves_explored = 0;
						tempo.moves_checked=0;
						tempo.next_to_play = -cab->next_to_play;

						for (int x=0; x<8; x++) {

							for (int y=0; y<8; y++) {

								tempo.check_brd[x][y] = 0;

							}

						}
						
						return tempo;

					}

				}

				if (cab->moves_checked == 28) { // if all the possible moves have been checked, move on

					cab->check_brd[j][i] = 1;
					cab->moves_checked = 0;
					continue;

				}

			}

			if (cab->brd[j][i] == 'R' && cab->next_to_play == -1) { // black rook found and black to play

				while (cab->moves_checked !=28) { // check all the 28 possible white rook moves

					if (cab->moves_checked < 7){ // [0, 6]

						cab->moves_checked++;
						test_x = i+cab->moves_checked;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 14){ // [7, 13]

						cab->moves_checked++;
						test_x = i+7-cab->moves_checked;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 21){ // [14, 20]

						cab->moves_checked++;
						test_x = i;
						test_y = j-14+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else { // [21, 27]

						cab->moves_checked++;
						test_x = i;
						test_y = j+21-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}

					if (tempo.move_legit == 1){

						if (first_move == 1) {

							tempo.start_a = i;
							tempo.start_b = j;
							tempo.stop_a = test_x;
							tempo.stop_b = test_y;

						}

						tempo.all_moves_explored = 0;
						tempo.moves_checked=0;
						tempo.next_to_play = -cab->next_to_play;

						for (int x=0; x<8; x++) {

							for (int y=0; y<8; y++) {

								tempo.check_brd[x][y] = 0;

							}

						}

						return tempo;

					}

				}

				if (cab->moves_checked == 28) { // if all the possible moves have been checked, move on

					cab->check_brd[j][i] = 1;
					cab->moves_checked = 0;
					continue;

				}

			}

			if (cab->brd[j][i] == 'k' && cab->next_to_play == 1) { // white king found and white to play

				while (cab->moves_checked !=10) { // check all the 10 possible white king moves

					if (cab->moves_checked == 0){

						cab->moves_checked++;
						test_x = i+cab->moves_checked;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 1){

						cab->moves_checked++;
						test_x = i-1+cab->moves_checked;
						test_y = j-1+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 2){

						cab->moves_checked++;
						test_x = i;
						test_y = j-2+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 3){

						cab->moves_checked++;
						test_x = i+3-cab->moves_checked;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 4){

						cab->moves_checked++;
						test_x = i+4-cab->moves_checked;
						test_y = j+4-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 5){

						cab->moves_checked++;
						test_x = i;
						test_y = j+5-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 6){

						cab->moves_checked++;
						test_x = i+6-cab->moves_checked;
						test_y = j-6+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 7){

						cab->moves_checked++;
						test_x = i-7+cab->moves_checked;
						test_y = j+7-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 8){

						cab->moves_checked++;
						test_x = i+2;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else {

						cab->moves_checked++;
						test_x = i-2;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}

					if (tempo.move_legit == 1){

						if (first_move == 1) {

							tempo.start_a = i;
							tempo.start_b = j;
							tempo.stop_a = test_x;
							tempo.stop_b = test_y;

						}

						tempo.all_moves_explored = 0;
						tempo.moves_checked=0;
						tempo.next_to_play = -cab->next_to_play;

						for (int x=0; x<8; x++) {

							for (int y=0; y<8; y++) {

								tempo.check_brd[x][y] = 0;

							}

						}

						return tempo;

					}

				}

				if (cab->moves_checked == 10) { // if all the possible moves have been checked, move on

					cab->check_brd[j][i] = 1;
					cab->moves_checked = 0;
					continue;

				}

			}

			if (cab->brd[j][i] == 'K' && cab->next_to_play == -1) { // black king found and black to play

				while (cab->moves_checked !=10) { // check all the 10 possible white rook moves

					if (cab->moves_checked == 0){

						cab->moves_checked++;
						test_x = i+cab->moves_checked;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 1){

						cab->moves_checked++;
						test_x = i-1+cab->moves_checked;
						test_y = j-1+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 2){

						cab->moves_checked++;
						test_x = i;
						test_y = j-2+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 3){

						cab->moves_checked++;
						test_x = i+3-cab->moves_checked;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 4){

						cab->moves_checked++;
						test_x = i+4-cab->moves_checked;
						test_y = j+4-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 5){

						cab->moves_checked++;
						test_x = i;
						test_y = j+5-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 6){

						cab->moves_checked++;
						test_x = i+6-cab->moves_checked;
						test_y = j-6+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 7){

						cab->moves_checked++;
						test_x = i-7+cab->moves_checked;
						test_y = j+7-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 8){

						cab->moves_checked++;
						test_x = i+2;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else {

						cab->moves_checked++;
						test_x = i-2;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}

					if (tempo.move_legit == 1){

						if (first_move == 1) {

							tempo.start_a = i;
							tempo.start_b = j;
							tempo.stop_a = test_x;
							tempo.stop_b = test_y;

						}

						tempo.all_moves_explored = 0;
						tempo.moves_checked=0;
						tempo.next_to_play = -cab->next_to_play;

						for (int x=0; x<8; x++) {

							for (int y=0; y<8; y++) {

								tempo.check_brd[x][y] = 0;

							}

						}

						return tempo;

					}

				}

				if (cab->moves_checked == 10) { // if all the possible moves have been checked, move on

					cab->check_brd[j][i] = 1;
					cab->moves_checked = 0;
					continue;

				}

			}

			if (cab->brd[j][i] == 'p' && cab->next_to_play == 1) { // white pawn found and white to play

				while (cab->moves_checked !=4) { // check all the 4 possible white pawn moves

					if (cab->moves_checked == 0){

						cab->moves_checked++;
						test_x = i;
						test_y = j+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 1){

						cab->moves_checked++;
						test_x = i;
						test_y = j+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 2){

						cab->moves_checked++;
						test_x = i+1;
						test_y = j-2+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else {

						cab->moves_checked++;
						test_x = i-1;
						test_y = j-3+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);	

					}

					if (tempo.move_legit == 1){

						if (first_move == 1) {

							tempo.start_a = i;
							tempo.start_b = j;
							tempo.stop_a = test_x;
							tempo.stop_b = test_y;

						}

						tempo.all_moves_explored = 0;
						tempo.moves_checked=0;
						tempo.next_to_play = -cab->next_to_play;

						for (int x=0; x<8; x++) {

							for (int y=0; y<8; y++) {

								tempo.check_brd[x][y] = 0;

							}

						}

						return tempo;

					}

				}

				if (cab->moves_checked == 4) { // if all the possible moves have been checked, move on

					cab->check_brd[j][i] = 1;
					cab->moves_checked = 0;
					continue;

				}

			}

			if (cab->brd[j][i] == 'P' && cab->next_to_play == -1) { // black pawn found and black to play

				while (cab->moves_checked !=4) { // check all the 4 possible black pawn moves

					if (cab->moves_checked == 0){

						cab->moves_checked++;
						test_x = i;
						test_y = j-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 1){

						cab->moves_checked++;
						test_x = i;
						test_y = j-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 2){

						cab->moves_checked++;
						test_x = i+1;
						test_y = j+2-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else {

						cab->moves_checked++;
						test_x = i-1;
						test_y = j+3-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);	

					}

					if (tempo.move_legit == 1){

						if (first_move == 1) {

							tempo.start_a = i;
							tempo.start_b = j;
							tempo.stop_a = test_x;
							tempo.stop_b = test_y;

						}

						tempo.all_moves_explored = 0;
						tempo.moves_checked=0;
						tempo.next_to_play = -cab->next_to_play;

						for (int x=0; x<8; x++) {

							for (int y=0; y<8; y++) {

								tempo.check_brd[x][y] = 0;

							}

						}

						return tempo;

					}

				}

				if (cab->moves_checked == 4) { // if all the possible moves have been checked, move on

					cab->check_brd[j][i] = 1;
					cab->moves_checked = 0;
					continue;

				}

			}

			if (cab->brd[j][i] == 'n' && cab->next_to_play == 1) { // white knight found and white to play

				while (cab->moves_checked !=8) { // check all the 8 possible white knight moves

					if (cab->moves_checked == 0){

						cab->moves_checked++;
						test_x = i+1;
						test_y = j+2;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 1){

						cab->moves_checked++;
						test_x = i+2;
						test_y = j+1;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 2){

						cab->moves_checked++;
						test_x = i+2;
						test_y = j-1;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 3){

						cab->moves_checked++;
						test_x = i+1;
						test_y = j-2;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 4){

						cab->moves_checked++;
						test_x = i-1;
						test_y = j-2;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 5){

						cab->moves_checked++;
						test_x = i-2;
						test_y = j-1;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 6){

						cab->moves_checked++;
						test_x = i-2;
						test_y = j+1;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else {

						cab->moves_checked++;
						test_x = i-1;
						test_y = j+2;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}

					if (tempo.move_legit == 1){

						if (first_move == 1) {

							tempo.start_a = i;
							tempo.start_b = j;
							tempo.stop_a = test_x;
							tempo.stop_b = test_y;

						}

						tempo.all_moves_explored = 0;
						tempo.moves_checked=0;
						tempo.next_to_play = -cab->next_to_play;

						for (int x=0; x<8; x++) {

							for (int y=0; y<8; y++) {

								tempo.check_brd[x][y] = 0;

							}

						}

						return tempo;

					}

				}

				if (cab->moves_checked == 8) { // if all the possible moves have been checked, move on

					cab->check_brd[j][i] = 1;
					cab->moves_checked = 0;
					continue;

				}

			}

			if (cab->brd[j][i] == 'N' && cab->next_to_play == -1) { // black knight found and black to play

				while (cab->moves_checked !=8) { // check all the 8 possible black knight moves

					if (cab->moves_checked == 0){

						cab->moves_checked++;
						test_x = i+1;
						test_y = j+2;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 1){

						cab->moves_checked++;
						test_x = i+2;
						test_y = j+1;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 2){

						cab->moves_checked++;
						test_x = i+2;
						test_y = j-1;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 3){

						cab->moves_checked++;
						test_x = i+1;
						test_y = j-2;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 4){

						cab->moves_checked++;
						test_x = i-1;
						test_y = j-2;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 5){

						cab->moves_checked++;
						test_x = i-2;
						test_y = j-1;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked == 6){

						cab->moves_checked++;
						test_x = i-2;
						test_y = j+1;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else {

						cab->moves_checked++;
						test_x = i-1;
						test_y = j+2;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}

					if (tempo.move_legit == 1){

						if (first_move == 1) {

							tempo.start_a = i;
							tempo.start_b = j;
							tempo.stop_a = test_x;
							tempo.stop_b = test_y;

						}

						tempo.all_moves_explored = 0;
						tempo.moves_checked=0;
						tempo.next_to_play = -cab->next_to_play;

						for (int x=0; x<8; x++) {

							for (int y=0; y<8; y++) {

								tempo.check_brd[x][y] = 0;

							}

						}

						return tempo;

					}

				}

				if (cab->moves_checked == 8) { // if all the possible moves have been checked, move on

					cab->check_brd[j][i] = 1;
					cab->moves_checked = 0;
					continue;

				}

			}

			if (cab->brd[j][i] == 'b' && cab->next_to_play == 1) { // white bishop found and white to play

				while (cab->moves_checked != 28) { // check all the 28 possible white bishop moves

					if (cab->moves_checked < 7){ // [0, 6]

						cab->moves_checked++;
						test_x = i+cab->moves_checked;
						test_y = j+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 14){ // [7, 13]

						cab->moves_checked++;
						test_x = i+7-cab->moves_checked;
						test_y = j+7-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 21){ // [14, 20]

						cab->moves_checked++;
						test_x = i+14-cab->moves_checked;
						test_y = j-14+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else { // [21, 27]

						cab->moves_checked++;
						test_x = i-21+cab->moves_checked;
						test_y = j+21-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}

					if (tempo.move_legit == 1){

						if (first_move == 1) {

							tempo.start_a = i;
							tempo.start_b = j;
							tempo.stop_a = test_x;
							tempo.stop_b = test_y;

						}

						tempo.all_moves_explored = 0;
						tempo.moves_checked=0;
						tempo.next_to_play = -cab->next_to_play;

						for (int x=0; x<8; x++) {

							for (int y=0; y<8; y++) {

								tempo.check_brd[x][y] = 0;

							}

						}
						
						return tempo;

					}

				}

				if (cab->moves_checked == 28) { // if all the possible moves have been checked, move on

					cab->check_brd[j][i] = 1;
					cab->moves_checked = 0;
					continue;

				}

			}

			if (cab->brd[j][i] == 'B' && cab->next_to_play == -1) { // black bishop found and black to play

				while (cab->moves_checked != 28) { // check all the 28 possible black bishop moves

					if (cab->moves_checked < 7){ // [0, 6]

						cab->moves_checked++;
						test_x = i+cab->moves_checked;
						test_y = j+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 14){ // [7, 13]

						cab->moves_checked++;
						test_x = i+7-cab->moves_checked;
						test_y = j+7-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 21){ // [14, 20]

						cab->moves_checked++;
						test_x = i+14-cab->moves_checked;
						test_y = j-14+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else { // [21, 27]

						cab->moves_checked++;
						test_x = i-21+cab->moves_checked;
						test_y = j+21-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}

					if (tempo.move_legit == 1){

						if (first_move == 1) {

							tempo.start_a = i;
							tempo.start_b = j;
							tempo.stop_a = test_x;
							tempo.stop_b = test_y;

						}

						tempo.all_moves_explored = 0;
						tempo.moves_checked=0;
						tempo.next_to_play = -cab->next_to_play;

						for (int x=0; x<8; x++) {

							for (int y=0; y<8; y++) {

								tempo.check_brd[x][y] = 0;

							}

						}
						
						return tempo;

					}

				}

				if (cab->moves_checked == 28) { // if all the possible moves have been checked, move on

					cab->check_brd[j][i] = 1;
					cab->moves_checked = 0;
					continue;

				}

			}

			if (cab->brd[j][i] == 'q' && cab->next_to_play == 1) { // white queen found and white to play

				while (cab->moves_checked != 56) { // check all the 56 possible white queen moves

					if (cab->moves_checked < 7){ // [0, 6]

						cab->moves_checked++;
						test_x = i+cab->moves_checked;
						test_y = j+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 14){ // [7, 13]

						cab->moves_checked++;
						test_x = i+7-cab->moves_checked;
						test_y = j+7-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 21){ // [14, 20]

						cab->moves_checked++;
						test_x = i+14-cab->moves_checked;
						test_y = j-14+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if ((cab->moves_checked < 28)){ // [21, 27]

						cab->moves_checked++;
						test_x = i-21+cab->moves_checked;
						test_y = j+21-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 35){ // [28, 34]

						cab->moves_checked++;
						test_x = i-28+cab->moves_checked;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 42){ // [35, 41]

						cab->moves_checked++;
						test_x = i+35-cab->moves_checked;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 49){ // [42, 48]

						cab->moves_checked++;
						test_x = i;
						test_y = j-42+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else { // [49, 55]

						cab->moves_checked++;
						test_x = i;
						test_y = j+49-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}

					if (tempo.move_legit == 1){

						if (first_move == 1) {

							tempo.start_a = i;
							tempo.start_b = j;
							tempo.stop_a = test_x;
							tempo.stop_b = test_y;

						}

						tempo.all_moves_explored = 0;
						tempo.moves_checked=0;
						tempo.next_to_play = -cab->next_to_play;

						for (int x=0; x<8; x++) {

							for (int y=0; y<8; y++) {

								tempo.check_brd[x][y] = 0;

							}

						}
						
						return tempo;

					}

				}

				if (cab->moves_checked == 56) { // if all the possible moves have been checked, move on

					cab->check_brd[j][i] = 1;
					cab->moves_checked = 0;
					continue;

				}

			}

			if (cab->brd[j][i] == 'Q' && cab->next_to_play == -1) { // black queen found and black to play

				while (cab->moves_checked != 56) { // check all the 56 possible black queen moves

					if (cab->moves_checked < 7){ // [0, 6]

						cab->moves_checked++;
						test_x = i+cab->moves_checked;
						test_y = j+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 14){ // [7, 13]

						cab->moves_checked++;
						test_x = i+7-cab->moves_checked;
						test_y = j+7-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 21){ // [14, 20]

						cab->moves_checked++;
						test_x = i+14-cab->moves_checked;
						test_y = j-14+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if ((cab->moves_checked < 28)){ // [21, 27]

						cab->moves_checked++;
						test_x = i-21+cab->moves_checked;
						test_y = j+21-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 35){ // [28, 34]

						cab->moves_checked++;
						test_x = i-28+cab->moves_checked;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 42){ // [35, 41]

						cab->moves_checked++;
						test_x = i+35-cab->moves_checked;
						test_y = j;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else if (cab->moves_checked < 49){ // [42, 48]

						cab->moves_checked++;
						test_x = i;
						test_y = j-42+cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}	else { // [49, 55]

						cab->moves_checked++;
						test_x = i;
						test_y = j+49-cab->moves_checked;
						tempo = move_piece(*cab, i, j, test_x, test_y, 0);

					}

					if (tempo.move_legit == 1){

						if (first_move == 1) {

							tempo.start_a = i;
							tempo.start_b = j;
							tempo.stop_a = test_x;
							tempo.stop_b = test_y;

						}

						tempo.all_moves_explored = 0;
						tempo.moves_checked=0;
						tempo.next_to_play = -cab->next_to_play;

						for (int x=0; x<8; x++) {

							for (int y=0; y<8; y++) {

								tempo.check_brd[x][y] = 0;

							}

						}
						
						return tempo;

					}

				}

				if (cab->moves_checked == 56) { // if all the possible moves have been checked, move on

					cab->check_brd[j][i] = 1;
					cab->moves_checked = 0;
					continue;

				}

			}
		
		}

	}

	cab->all_moves_explored = 1;

	tempo.move_legit = 0;

	return tempo;

}