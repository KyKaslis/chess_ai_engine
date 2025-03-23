#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "chess_board.h"
#include "extr_var.h"

int move_counter;

chessboard intlz(chessboard cab){ //initialize board

	for (int i=2; i<6; i++){
		
		for (int k=0; k<8; k++){
		
			cab.brd[i][k] = 'O';

		}

	}

	for (int i=0; i<8; i++){
		
		cab.brd[6][i] = 'P';
		cab.brd[1][i] = 'p';

		for (int j=0; j<8; j++){

			cab.check_brd[i][j]=0;

		}

	}

	cab.brd[7][0] = 'R';
	cab.brd[7][7] = 'R';
	cab.brd[0][0] = 'r';
	cab.brd[0][7] = 'r';

	cab.brd[7][1] = 'N';
	cab.brd[7][6] = 'N';
	cab.brd[0][1] = 'n';
	cab.brd[0][6] = 'n';

	cab.brd[7][2] = 'B';
	cab.brd[7][5] = 'B';
	cab.brd[0][2] = 'b';
	cab.brd[0][5] = 'b';

	cab.brd[7][3] = 'Q';
	cab.brd[7][4] = 'K';
	cab.brd[0][3] = 'q';
	cab.brd[0][4] = 'k';

	cab.ws_castling_active = 1;
	cab.wl_castling_active = 1;
	cab.bs_castling_active = 1;
	cab.bl_castling_active = 1;

	for (int i=0; i<8; i++){

	cab.white_en_pass[i]=0;
	cab.black_en_pass[i]=0;

	}

	cab.move_legit = 1;
	cab.moves_checked = 0;

	cab.score = 999;
	cab.all_moves_explored = 0;
	cab.next_to_play = 1;

	cab.start_a = -1;
	cab.start_b = -1;
	cab.stop_a = -1;
	cab.stop_b = -1;

	return cab;

}

chessboard empty_board(chessboard cab){ //empty board

	for (int i=0; i<8; i++){
		
		for (int k=0; k<8; k++){
		
			cab.brd[i][k] = 'O';

		}

	}

	return cab;

}

void print_board(chessboard cab) {

	for (int i=7; i>-1; i--) {

		printf("%d ",i+1);

		for (int k=0; k<8; k++) {

			printf("%c", cab.brd[i][k]);

		}
		
		printf("\n");

	}

	printf("\n  abcdefgh\n");

}

chessboard is_move_legal(chessboard cab, int a, int b, int c, int d, int suppress_output){

	if (a<0 || a>7 || b<0 || b>7 || c<0 || c>7 || d<0 || d>7){ // check you're inside the board

		if (!suppress_output){

			printf("Illegal move\n");
			printf("Off board\n");

		}

		cab.move_legit=0;
		return cab;

	}

	if ((islower(cab.brd[b][a]) && islower(cab.brd[d][c])) || (!islower(cab.brd[b][a]) && !islower(cab.brd[d][c]) && cab.brd[d][c]!='O')){ //check you're not moving a piece to a piece of the same kind

		if (!suppress_output){

			printf("Illegal move\n");
			printf("Cannot capture same pieces\n");

		}

		cab.move_legit=0;
		return cab;

	}

	if (cab.brd[b][a]=='O'){ //check you're not moving empty square

		if (!suppress_output){

			printf("Illegal move\n");
			printf("Cannot move empty square\n");

		}

		cab.move_legit=0;
		return cab;

	}

	if (cab.brd[b][a]=='p'){ // the rule set of white pawns

		if (b==1 && d==3 && a==c && cab.brd[d][c]=='O' && cab.brd[d-1][c]=='O'){ //double initial move

			cab.white_en_pass[a]=move_counter;

		}

		else if (b==1 && d==3 && a==c && cab.brd[d][c]=='O' && cab.brd[d-1][c]!='O'){ //double initial move but someone is ahead

			if (!suppress_output){

				printf("Illegal move\n");
				printf("Someone's ahead\n");

			}

			cab.move_legit=0;
			return cab;

		}

		else if (d==b+1 && cab.brd[d][c] != 'O' && (a==c+1 || a==c-1)) {// can eat diagonally

		}

		else if (d==5 && b==4 && cab.black_en_pass[c]==move_counter-1 && (a==c+1 || a==c-1)) {// can eat diagonally if black en passanted in the previous turn

			cab.brd[d-1][c]='O';

		}

		else if (d>b+1 || a != c || d<b){ //cannot move more than two squares or diagonally or backwards

			if (!suppress_output){

				printf("Illegal move\n");
				printf("Pawns don't move like that\n");

			}

			cab.move_legit=0;
			return cab;

		}

		else if (cab.brd[d][c]!='O'){ // cannot move ahead if not empty

			if (!suppress_output){

				printf("Illegal move\n");
				printf("Someone's ahead\n");

			}

			cab.move_legit=0;
			return cab;

		}


	}

	if (cab.brd[b][a]=='P'){ // the rule set of black pawns

		if (b==6 && d==4 && a==c && cab.brd[d][c]=='O' && cab.brd[d+1][c]=='O'){ //double initial move

			cab.black_en_pass[a]=move_counter;


		}

		else if (b==6 && d==4 && a==c && cab.brd[d][c]=='O' && cab.brd[d+1][c]!='O'){ //double initial move but someone is ahead

			if (!suppress_output){

				printf("Illegal move\n");
				printf("Someone's ahead\n");

			}

			cab.move_legit=0;
			return cab;

		}

		else if (d==b-1 && cab.brd[d][c] != 'O' && (a==c+1 || a==c-1)) {// can eat diagonally

		}

		else if (d==2 && b==3 && cab.white_en_pass[c]==move_counter-1 && (a==c+1 || a==c-1)) {// can eat diagonally if white en passanted in the previous turn

			cab.brd[d+1][c]='O';

		}

		else if (d<b-1 || a != c || d>b){ //cannot move more than two squares or diagonally or backwards

			if (!suppress_output){

				printf("Illegal move\n");
				printf("Pawns don't move like that\n");

			}

			cab.move_legit=0;
			return cab;

		}

		else if (cab.brd[d][c]!='O'){ // cannot move ahead if not empty

			if (!suppress_output){

				printf("Illegal move\n");
				printf("Someone's ahead\n");

			}

			cab.move_legit=0;
			return cab;

		}


	}

	if (cab.brd[b][a]=='r' || cab.brd[b][a]=='R'){ // the rule set of rooks

		if (a!=c && b!=d){ // check that you're moving on a line

			if (!suppress_output){

				printf("Illegal move\n");
				printf("Rooks don't move like that\n");

			}

			cab.move_legit=0;
			return cab;
	
		}

		else if (a==c) {

			if (d>b+1) { // check that there is no one in between
		
				for (int i=b+1; i<d; i++){
					
					if (cab.brd[i][a]!='O'){

						if (!suppress_output){

						printf("Illegal move\n");
						printf("There's someone in between\n");

						}

						cab.move_legit=0;
						return cab;

					}

				}

			}

			if (b>d+1) { // check that there is no one in between
		
				for (int i=d+1; i<b; i++){
					
					if (cab.brd[i][a]!='O'){

						if (!suppress_output){

						printf("Illegal move\n");
						printf("There's someone in between\n");

						}

						cab.move_legit=0;
						return cab;

					}

				}

			}

		}

		else if (b==d) {

			if (a>c+1) { // check that there is no one in between
		
				for (int i=c+1; i<a; i++){
					
					if (cab.brd[b][i]!='O'){

						if (!suppress_output){

						printf("Illegal move\n");
						printf("There's someone in between\n");

						}

						cab.move_legit=0;
						return cab;

					}

				}

			}

			if (c>a+1) { // check that there is no one in between
		
				for (int i=a+1; i<c; i++){
					
					if (cab.brd[b][i]!='O'){

						if (!suppress_output){

						printf("Illegal move\n");
						printf("There's someone in between\n");

						}

						cab.move_legit=0;
						return cab;

					}

				}

			}

		}

	}

	if (cab.brd[b][a]=='b' || cab.brd[b][a]=='B'){ // the rule set of bishops

		if (abs(c-a) != abs(d-b)) { // check that you're moving diagonally

			if (!suppress_output){

				printf("Illegal move\n");
				printf("Bishops don't move like that\n");

			}

			cab.move_legit=0;
			return cab;
	
		}

		else if (c>a+1 && d>b+1) {

			for (int i=1; i<c-a; i++){
					
				if (cab.brd[b+i][a+i]!='O'){

					if (!suppress_output){

					printf("Illegal move\n");
					printf("There's someone in between\n");

					}

					cab.move_legit=0;
					return cab;

				}

			}
		}

		else if (c>a+1 && b>d+1) {

			for (int i=1; i<c-a; i++){
					
				if (cab.brd[b-i][a+i]!='O'){

					if (!suppress_output){

					printf("Illegal move\n");
					printf("There's someone in between\n");

					}

					cab.move_legit=0;
					return cab;

				}

			}
		}

		else if (a>c+1 && b>d+1) {

			for (int i=1; i<a-c; i++){
					
				if (cab.brd[b-i][a-i]!='O'){

					if (!suppress_output){

					printf("Illegal move\n");
					printf("There's someone in between\n");

					}

					cab.move_legit=0;
					return cab;

				}

			}
		}

		else if (a>c+1 && d>b+1) {

			for (int i=1; i<a-c; i++){
					
				if (cab.brd[b+i][a-i]!='O'){

					if (!suppress_output){

					printf("Illegal move\n");
					printf("There's someone in between\n");

					}

					cab.move_legit=0;
					return cab;

				}

			}
		}

	}

	if (cab.brd[b][a]=='n' || cab.brd[b][a]=='N'){ // the rule set of knights

		if (abs(c-a) == 0 || abs(d-b) == 0 || abs(c-a) + abs(d-b) !=3) { // check that you're moving knightly

			if (!suppress_output){

				printf("Illegal move\n");
				printf("Knights don't move like that\n");

			}

			cab.move_legit=0;
			return cab;
	
		}

	}

	if (cab.brd[b][a]=='q' || cab.brd[b][a]=='Q'){ // the rule set of queens

		if (abs(c-a) != 0 && abs(d-b) != 0 && abs(c-a) != abs(d-b)) { // check that you're moving queenlike

			if (!suppress_output){

				printf("Illegal move\n");
				printf("Queens don't move like that\n");

			}

			cab.move_legit=0;
			return cab;
	
		}

		else if (a==c) {

			if (d>b+1) { // check that there is no one in between
		
				for (int i=b+1; i<d; i++){
					
					if (cab.brd[i][a]!='O'){

						if (!suppress_output){

						printf("Illegal move\n");
						printf("There's someone in between\n");

						}

						cab.move_legit=0;
						return cab;

					}

				}

			}

			if (b>d+1) { // check that there is no one in between
		
				for (int i=d+1; i<b; i++){
					
					if (cab.brd[i][a]!='O'){

						if (!suppress_output){

						printf("Illegal move\n");
						printf("There's someone in between\n");

						}

						cab.move_legit=0;
						return cab;

					}

				}

			}

		}

		else if (b==d) {

			if (a>c+1) { // check that there is no one in between
		
				for (int i=c+1; i<a; i++){
					
					if (cab.brd[b][i]!='O'){

						if (!suppress_output){

						printf("Illegal move\n");
						printf("There's someone in between\n");

						}

						cab.move_legit=0;
						return cab;

					}

				}

			}

			if (c>a+1) { // check that there is no one in between
		
				for (int i=a+1; i<c; i++){
					
					if (cab.brd[b][i]!='O'){

						if (!suppress_output){

						printf("Illegal move\n");
						printf("There's someone in between\n");

						}

						cab.move_legit=0;
						return cab;

					}

				}

			}
		}

		else if (c>a+1 && d>b+1) {

			for (int i=1; i<c-a; i++){
					
				if (cab.brd[b+i][a+i]!='O'){

					if (!suppress_output){

					printf("Illegal move\n");
					printf("There's someone in between\n");

					}

					cab.move_legit=0;
					return cab;

				}

			}
		}

		else if (c>a+1 && b>d+1) {

			for (int i=1; i<c-a; i++){
					
				if (cab.brd[b-i][a+i]!='O'){

					if (!suppress_output){

					printf("Illegal move\n");
					printf("There's someone in between\n");

					}

					cab.move_legit=0;
					return cab;

				}

			}
		}

		else if (a>c+1 && b>d+1) {

			for (int i=1; i<a-c; i++){
					
				if (cab.brd[b-i][a-i]!='O'){

					if (!suppress_output){

					printf("Illegal move\n");
					printf("There's someone in between\n");

					}

					cab.move_legit=0;
					return cab;

				}

			}
		}

		else if (a>c+1 && d>b+1) {

			for (int i=1; i<a-c; i++){
					
				if (cab.brd[b+i][a-i]!='O'){

					if (!suppress_output){

					printf("Illegal move\n");
					printf("There's someone in between\n");

					}

					cab.move_legit=0;
					return cab;

				}

			}
		}

	}

	if (cab.brd[b][a]=='k' || cab.brd[b][a]=='K'){ // the rule set of kings

		if (b==0 && d==0 && a==4 && c==6 && cab.brd[0][5]=='O' && cab.brd[0][6]=='O' && cab.ws_castling_active==1  && !square_in_danger_from_black(cab, 4, 0) && !square_in_danger_from_black(cab, 5, 0) && !square_in_danger_from_black(cab, 6, 0)){ // white king short castle

			cab.ws_castling_active=0;	
			cab.brd[0][5]='r';
			cab.brd[0][7]='O';
			cab.move_legit=1;
			return cab;

		}

		if (b==0 && d==0 && a==4 && c==2 && cab.brd[0][3]=='O' && cab.brd[0][2]=='O' && cab.brd[0][1]=='O' && cab.wl_castling_active==1 && !square_in_danger_from_black(cab, 4, 0) && !square_in_danger_from_black(cab, 3, 0) && !square_in_danger_from_black(cab, 2, 0)){ //white king long castle

			cab.wl_castling_active=0;	
			cab.brd[0][3]='r';
			cab.brd[0][0]='O';
			cab.move_legit=1;
			return cab;

		}

		if (b==7 && d==7 && a==4 && c==6 && cab.brd[7][5]=='O' && cab.brd[7][6]=='O' && cab.bs_castling_active==1 && !square_in_danger_from_white(cab, 4, 7) && !square_in_danger_from_white(cab, 5, 7) && !square_in_danger_from_white(cab, 6, 7)){ // black king short castle

			cab.ws_castling_active=0;	
			cab.brd[7][5]='R';
			cab.brd[7][7]='O';
			cab.move_legit=1;
			return cab;

		}

		if (b==7 && d==7 && a==4 && c==2 && cab.brd[7][3]=='O' && cab.brd[7][2]=='O' && cab.brd[7][1]=='O' && cab.bl_castling_active==1 && !square_in_danger_from_white(cab, 4, 7) && !square_in_danger_from_white(cab, 3, 7) && !square_in_danger_from_white(cab, 2, 7)){ //black king long castle

			cab.wl_castling_active=0;	
			cab.brd[7][3]='R';
			cab.brd[7][0]='O';
			cab.move_legit=1;
			return cab;

		}

		if (abs(c-a)>1 || abs(d-b)>1){ //check that you're moving royally

			if (!suppress_output){

			printf("Illegal move\n");
			printf("Kings don't move like that\n");

			}

			cab.move_legit=0;
			return cab;

		}

	}

	if (!suppress_output){

		printf("Move legal\n");

	}

	cab.move_legit=1;
	return cab;

}

int square_in_danger_from_black(chessboard cab, int a, int b){

	cab.brd[b][a]='p';

	chessboard temp;

	for (int i=0; i<8; i++){

		for (int j=0; j<8; j++){

			if (cab.brd[i][j] == 'P' || cab.brd[i][j] == 'R' || cab.brd[i][j] == 'K' || cab.brd[i][j] == 'N' || cab.brd[i][j] == 'Q' || cab.brd[i][j] == 'B'){

				temp = is_move_legal(cab, j, i, a, b, 1);
				if (temp.move_legit==1) return 1;

			}
		}
	}

	return 0;

}

int square_in_danger_from_white(chessboard cab, int a, int b){

	cab.brd[b][a]='P';

	chessboard temp;

	for (int i=0; i<8; i++){

		for (int j=0; j<8; j++){

			if (cab.brd[i][j] == 'p' || cab.brd[i][j] == 'r' || cab.brd[i][j] == 'k' || cab.brd[i][j] == 'n' || cab.brd[i][j] == 'q' || cab.brd[i][j] == 'b'){

				temp = is_move_legal(cab, j, i, a, b, 1);
				if (temp.move_legit==1) return 1;

			}
		}
	}

	return 0;

}

int is_white_king_in_danger(chessboard cab){

	int column = -1;
	int row = -1;

	for (int i=0; i<8; i++) {
	
		for (int j=0; j<8; j++) {

			if (cab.brd[i][j] == 'k') { //find the white king

				column = i;
				row = j;
			}
		}
	}

	if (column == -1 && row == -1) return 0;

	return square_in_danger_from_black(cab, row, column);

}

int is_black_king_in_danger(chessboard cab){

	int column = -1;
	int row = -1;

	for (int i=0; i<8; i++) {
	
		for (int j=0; j<8; j++) {

			if (cab.brd[i][j] == 'K') { //find the black king

				column = i;
				row = j;
			}
		}
	}

	if (column == -1 && row == -1) return 0;

	return square_in_danger_from_white(cab, row, column);

}

chessboard move_piece(chessboard cab, int a, int b, int c, int d, int extra_move){

	//the_move is expected to be letternumberletternumber
	//this function will move letternumber to letternumber
	//the extra move is to be used only by AI for promotion

	char get_input[1]; //to be used for promotion
	int some_ch; //to be used for promotion

	chessboard tempo;
	tempo = is_move_legal(cab, a, b, c, d, 1);

	if (tempo.move_legit) { // this is where the move is written to the board

		tempo.brd[d][c]=cab.brd[b][a];
		tempo.brd[b][a]='O';

	}

	if (tempo.brd[0][0]=='O') {

		tempo.wl_castling_active = 0;

	} 
	else if (tempo.brd[0][7]=='O') {

		tempo.ws_castling_active = 0;

	}
	else if (tempo.brd[7][0]=='O') {

		tempo.bl_castling_active = 0;

	} 
	else if (tempo.brd[7][7]=='O') {

		tempo.bs_castling_active = 0;

	} 
	else if (tempo.brd[0][4]=='O') {

		tempo.ws_castling_active = 0;
		tempo.wl_castling_active = 0;

	} 
	else if (tempo.brd[7][4]=='O') {

		tempo.bs_castling_active = 0;
		tempo.bl_castling_active = 0;

	} 
/*
	for (int i=0; i<8; i++){ // check if promotion is needed for white
		
		if (tempo.brd[7][i]=='p') {

			while(1){
		
				printf("Select promotion for white (q for queen, n for knight, r for rook, b for bishop:\n");

				fgets(get_input, 2, stdin);

				while(((some_ch=getchar()) != EOF) && (some_ch != '\n'));

				if (strcmp(get_input,"q")==0 || strcmp(get_input,"n")==0 || strcmp(get_input,"r")==0 || strcmp(get_input,"b")==0) break;

			}

		tempo.brd[7][i] = *get_input;

		break;
	
		}

	}
*/
	for (int i=0; i<8; i++){ // check if promotion is needed for black/AI
		
		if (tempo.brd[0][i]=='P') {

			if (extra_move == 0) tempo.brd[0][i] = 'Q';
			if (extra_move == 1) tempo.brd[0][i] = 'R';
			if (extra_move == 2) tempo.brd[0][i] = 'B';
			if (extra_move == 3) tempo.brd[0][i] = 'N';
	
		}

	}

	for (int i=0; i<8; i++){ // check if promotion is needed for white/AI
		
		if (tempo.brd[7][i]=='p') {

			if (extra_move == 0) tempo.brd[0][i] = 'Q';
			if (extra_move == 1) tempo.brd[0][i] = 'R';
			if (extra_move == 2) tempo.brd[0][i] = 'B';
			if (extra_move == 3) tempo.brd[0][i] = 'N';
	
		}

	}


	if (is_white_king_in_danger(tempo) && move_counter % 2 == 0) { // this is to prevent endangering own king

		//tempo.move_legit=0; to be updated in later versions

	}

	if (is_black_king_in_danger(tempo) && move_counter % 2 == 1) { // this is to prevent endangering own king

		//tempo.move_legit=0; to be updated in laterr versions

	}

	return tempo;

}

chessboard set_board(chessboard cab, char* the_move){

	//the_move is expected to be s_letter_number_piece

	int a;
	int b;
	int c;
	int d;

	a=*the_move++;
	b=*the_move++-'a';
	c=*the_move++-'1';
	d=*the_move++;

	cab.brd[c][b] = d; 

	return cab;

}