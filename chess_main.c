#include "chess_board.h"
#include "chess_eval.h"
#include "chess_ai.h"
#include "extr_var.h"
#include <stdio.h>
#include <string.h>

int move_counter=0; // global variable counter of moves

int main(){

	chessboard cb_stack[200]; // create a stack of 200 chessboards

	chessboard* chess_pointer = cb_stack; // set a pointer to the first board

	*chess_pointer = intlz(*chess_pointer); // initialise the first board

	print_board(*chess_pointer); // print the initial board

	char user_input[5]; // array to accept commands from the user

	int ch; // some character to save the commands

	int a; //first letter
	int b; //first number
	int c; //second letter
	int d; //second number (for example, e2e4 => a=4, b=1, a=4, b=3)

	while(1){

		chessboard temp_chess; // temporary board to be saved to the stack if it is legit
		temp_chess.move_legit=0; // by default it is not a legit board

		printf("Enter move:\n");

		fgets(user_input, 5, stdin);

		while(((ch=getchar()) != EOF) && (ch != '\n'));

		if (strcmp(user_input,"back")==0 && move_counter != 0){ // the user can go back one move at a time

			move_counter--;

		}

		else if (strcmp(user_input,"eval")==0){

			printf("Evaluation of board is %d\n", evaluate_position(temp_chess));

		}

		else if (strcmp(user_input,"void")==0){

			*(chess_pointer+move_counter) = empty_board(*chess_pointer); // empty the board

		}

		else if (*user_input == 's'){ //if the first letter of the user input is "s"

			*(chess_pointer+move_counter) = set_board(*(chess_pointer+move_counter),user_input); // set the board

		}

		else if (strcmp(user_input,"caiw")==0){

			printf("Calling ai\n");

			(chess_pointer+move_counter)->next_to_play = 1;

			temp_chess=call_hal(*(chess_pointer+move_counter),5,5);

			temp_chess = move_piece(*(chess_pointer+move_counter), temp_chess.start_a, temp_chess.start_b, temp_chess.stop_a, temp_chess.stop_b, 0);

		}

		else if (strcmp(user_input,"caib")==0){

			printf("Calling ai\n");

			(chess_pointer+move_counter)->next_to_play = -1;

			temp_chess=call_hal(*(chess_pointer+move_counter),5,5);

			temp_chess = move_piece(*(chess_pointer+move_counter), temp_chess.start_a, temp_chess.start_b, temp_chess.stop_a, temp_chess.stop_b, 0);

		}

		else {

			a=user_input[0]-'a';
			b=user_input[1]-'1';
			c=user_input[2]-'a';
			d=user_input[3]-'1';

			temp_chess=move_piece(*(chess_pointer+move_counter),a, b, c, d, 0); // attempt to make a move

		}

		if (temp_chess.move_legit == 1) { // if the move is legit increase the counter and add to the stack

			move_counter++;
			*(chess_pointer+move_counter)=temp_chess;

		}

		print_board(*(chess_pointer+move_counter)); // print the most recent legit move in any case
		printf("Move counter %d\n", move_counter);

	}

}