Chess AI Engine using the minimax algorithm and written in C.

No ChatGPT, no googling-copying-pasting, 100% my code.

Currently searching up to 5 moves ahead.

Lower case letters imply white pieces. Upper case letters imply black pieces.

"k", "K" => King
"q", "Q" => Queen
"b", "B" => Bishop
"n", "N" => Knight
"r", "R" => Rook
"p", "P" => Pawn

Possible commands:

1) "letter-number-letter-number" to move a piece. For example, "a2a4" will move whatever is in a2 to a4, if the move is possible.

2) "back" will take back the last move.

3) "eval" returns an evaluation of the current position.

4) "void' empties the board.

5) "s-letter-number-piece" will set piece to letter-number. For example, "sa1k" will put a white king to square a1.

6) "caiw" will call ai to play for white.

7) "caib" will call ai to play for black
