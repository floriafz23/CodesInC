/*
 * project_reversi_skeleton.h provided by APS105 Teaching Team
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "project_reversi_skeleton.h" // DO NOT modify this line

// ========= Function implementation ==========

/*Function:  printBoard 
 * --------------------
 * Print the whole board to the terminal window.
 */
void printBoard(char board[][26], int n) {
	
	// Declare alphabet string
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	
	// Print first line (index) based on size of board given
	printf("  ");
	for(int i=0; i<n; i++)
		printf("%c",alphabet[i]);
	printf("\n");
	
	// Print column index and board (to size given)
	for(int j=0; j<n; j++){
		printf("%c ", alphabet[j]);
		for(int k=0; k<n; k++)
			printf("%c", board[j][k]);
		printf("\n");
	}
}

/* Function:  positionInBounds 
 * --------------------
 * Checks whether the specified (row, col) lies within the board dimensions.
 */
bool positionInBounds(int n, int row, int col) {
	
	// Declare variables 
	bool inBounds;
	
	// Define out of bounds, assign value to boolean
	if(row>n-1 || row<0)
		inBounds = false;
	else if(col>n-1 || col < 0)
		inBounds = false;
	else 
		inBounds = true;
	
	// Return boolean
	return inBounds;  
}

/* Function:  checkLegalInDirection 
 * --------------------
 * Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction 
 * specified by deltaRow and deltaCol.
 */
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
	(void)n;
	
	// Declare variables
	int newRow, newColumn, i;
	bool availableDirection;
	
	// Assign values 
	i=1;
	newRow = row+i*deltaRow;
	newColumn = col+i*deltaCol;
	
	// For both cases (black and white)
	if(colour == 'B'){
		// continue only if next tile is white
		if(board[newRow][newColumn] == 'W'){
			//stay in loop as long as next tile is white
			while(board[newRow][newColumn] == 'W' && positionInBounds(n,newRow,newColumn) == true){
				i++;
				newRow = row+i*deltaRow;
				newColumn = col+i*deltaCol;
			}
			// If breaking tile is black, then direction is available
			if(board[newRow][newColumn] == 'B')
				availableDirection = true;
			else 
				availableDirection = false;
		}
		else
			availableDirection = false;
	}
	else if(colour == 'W'){
		// continue only if next tile is black
		if(board[newRow][newColumn] == 'B'){
			//stay in loop as long as next tile is black
			while(board[newRow][newColumn] == 'B'){
				i++;
				newRow = row+i*deltaRow;
				newColumn = col+i*deltaCol;
			}
			// If breaking tile is white, then direction is available
			if(board[newRow][newColumn] == 'W')
				availableDirection = true;
			else
				availableDirection = false;
		}
		else
			availableDirection = false;
	}
	// Return boolean
    return availableDirection;             
}

/*Function:  checkLegalGeneral 
 * --------------------
 * Checks LegalinDirection for all directions.
 */
bool checkLegalGeneral(char board[][26], int n, int row, int col, char colour){
	
	// Declare variables
	bool availableN, availableNE, availableE, availableSE, availableS, availableSW, availableW, availableNW;
	bool availableMove;
	
	// Check for all 8 directions
	availableN = checkLegalInDirection(board, n, row, col, colour, -1, 0);
	availableNE = checkLegalInDirection(board, n, row, col, colour, -1, 1);
	availableE = checkLegalInDirection(board, n, row, col, colour, 0, 1);
	availableSE = checkLegalInDirection(board, n, row, col, colour, 1, 1);
	availableS = checkLegalInDirection(board, n, row, col, colour, 1, 0);
	availableSW = checkLegalInDirection(board, n, row, col, colour, 1, -1);
	availableW = checkLegalInDirection(board, n, row, col, colour, 0, -1);
	availableNW = checkLegalInDirection(board, n, row, col, colour, -1, -1);
	
	// Assign true if at least one direction is legal
	if (availableN == true || availableNE == true || availableE == true || availableSE == true || availableS == true || availableSW == true || availableW == true || availableNW == true)
		availableMove = true;
	else
		availableMove = false;
	
	// Return boolean
	return availableMove;
}

/*Function:  movesAvailable 
 * --------------------
 * Check if there are any moves available.
 */
bool movesAvailable(char board[][26], int n, char colour){
	
	// Declare variables and alphabet
	int numberMoves=0;
	bool availableMove;
	
	// Print all moves that are legal in general
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			availableMove = checkLegalGeneral(board, n, i, j, colour);
			if (board[i][j] == 'U' && availableMove == true){
				numberMoves++;
			}
		}
	}
	
	if(numberMoves>0)
		availableMove = true;
	else
		availableMove = false;
	
	return availableMove;
}

/* Function:  makeMove 
 * --------------------
 * The player "turn" makes a move at (row, col).
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
 */
int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {

	// declare variables
	int numberTiles = 0;
	bool availableMove;
	bool availableMove2;
	char oppositeColour;
	int availableRows[676] = {0};
	int availableColumns[676] = {0};
	int moveCounter[676] = {0};
	int largestCounter, finalPosition;
	int moveRow, moveColumn;
	
	// copy board into newBoard (for purposes of deleting warnings)
	char newBoard[26][26];
	for(int loop=0; loop<26; loop++){
		for(int loop2=0; loop2<26; loop2++)
			newBoard[loop][loop2] = board[loop][loop2];
	}
	
	//assign computer color to "turn" and opposite color to "oppositeColour"
	if(turn == 'B'){
		oppositeColour = 'W';
	}
	else if(turn == 'W'){
		oppositeColour = 'B';
	}
	
	//finding available moves and assigning number of tiles flipped to each move
	int position=0;
	for(int r=0; r<n; r++){
		for(int c=0; c<n; c++){
			//for each combination of row and column, check if the move is legal
			availableMove = checkLegalGeneral(newBoard, n, r, c, turn);
			//if move is legal, assign that row and column and tiles flipped to corresponding arrays
			if (newBoard[r][c] == 'U' && availableMove == true){
				availableRows[position]=r;
				availableColumns[position]=c;
				//creating counter
				numberTiles = 0;
				for(int i=-1; i<2; i++){
					for(int j=-1; j<2; j++){
						availableMove2 = checkLegalInDirection(newBoard, n, r, c, turn, i, j);
						if (availableMove2 == true){
							int k=1;
							while(board[r+k*i][c+k*j] == oppositeColour){
								numberTiles++;
								k++;
							}
						}
					}
				}
				moveCounter[position] = numberTiles;
				position++;
				
			}
		}
	}
	
	//find what is the largest amount of tiles flipped
	largestCounter = moveCounter[0];
	for(int a=0; a<=position; a++){
		if(moveCounter[a]>largestCounter)
			largestCounter = moveCounter[a];
	}
	
	//find which position is the move to be made
	for(finalPosition=0; moveCounter[finalPosition] != largestCounter; finalPosition++);
	
	moveRow = availableRows[finalPosition];
	moveColumn = availableColumns[finalPosition];
	
	//assign move row and column to the pointers
	*row = moveRow;
	*col = moveColumn;

	return 0;
}

#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {
	//declare all variables
	int size;
	int playerRow, playerColumn;
	bool inBounds, availableMove, availableMove2;
	char board[26][26];
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	char computerColor, playerColor;
	char enterMove[2];
	bool moveValid = true;
	int computerRow, computerColumn;
	bool makePlayerMove, pMoveAvailable = true, cMoveAvailable = true; 
	int playerTiles = 0, computerTiles = 0;
	
	//ask input for board dimension (size by size)
	printf("Enter the board dimension: ");
	scanf("%d", &size);
	
	// Intial population of board (with U's, then add in WB BW)
	for(int i=0; i<26;i++){
		for(int j=0; j<26; j++)
			board[i][j]= 'U';
	}                                                         
	
	board[size/2-1][size/2-1] = 'W';
	board[size/2-1][size/2] = 'B';
	board[size/2][size/2-1] = 'B';
	board[size/2][size/2] = 'W';
	
	// Choose computer color and print board
	printf("Computer plays (B/W) : ");
	scanf("%s", &computerColor);
	printBoard(board,size);
	
	// Assign colours to computerColor and playerColor (corresponding) and assign value to boolean depending to see who goes first
	if(computerColor == 'B'){
		playerColor = 'W';
		makePlayerMove = false;
	}
	if(computerColor == 'W'){
		playerColor = 'B';
		makePlayerMove = true;
	}
	
	// moves can be played while the player's move is valid and there is an available move for either player
	while(moveValid == true && (pMoveAvailable == true || cMoveAvailable == true)){
		//search if there are available moves for the player
		pMoveAvailable = movesAvailable(board, size, playerColor);
		
		//if player move is available and player goes first (player is black tiles)
		if(makePlayerMove == true && pMoveAvailable){
			printf("Enter move for colour %c (RowCol): ",playerColor);
			scanf("%s", enterMove);
			
			// Assign move row and column to numbers
			if(enterMove[0] == 'a')
				playerRow = 0;
			else
				for(playerRow=0; alphabet[playerRow] != enterMove[0]; playerRow++);
			
			if(enterMove[1] == 'a')
				playerColumn = 0;
			else
				for(playerColumn=0; alphabet[playerColumn] != enterMove[1]; playerColumn++);
			
			//Check if move is valid and if so, assign to board
			inBounds = positionInBounds(size, playerRow, playerColumn);
			availableMove = checkLegalGeneral(board, size, playerRow, playerColumn, playerColor);
			
			//assign colors
			if(playerColor == 'B')
				computerColor = 'W';
			if(playerColor == 'W')
				computerColor = 'B';
			
			//if move is not in bounds or an available move, then the move is not valid
			if(inBounds == false || availableMove == false)
				moveValid = false;
			//if move in bounds and available, play move
			else if(inBounds == true && availableMove == true){
				board[playerRow][playerColumn] = playerColor;
				//Flip tiles
				for(int i=-1; i<2; i++){
					for(int j=-1; j<2; j++){
						availableMove = checkLegalInDirection(board, size, playerRow, playerColumn, playerColor, i, j);
						if (availableMove == true){
							int k=1;
							while(board[playerRow+k*i][playerColumn+k*j] == computerColor){
								board[playerRow+k*i][playerColumn+k*j] = playerColor;
								k++;							}
						}
					}
				}
				// print board
				printBoard(board,size);
				moveValid = true;
			}
		}
		// if only computer has moves available
		else if(pMoveAvailable == false && cMoveAvailable == true)
			printf("%c player has no valid move.\n", playerColor);
		else;
		
		if(playerColor == 'B')
			computerColor = 'W';
		if(playerColor == 'W')
			computerColor = 'B';
		cMoveAvailable = movesAvailable(board, size, computerColor);
		
		//if player's move is valid and there is an available move for computer
		if(moveValid == true && cMoveAvailable == true){
			//call makemove function and assign tile
			makeMove(board, size, computerColor, &computerRow, &computerColumn);
			board[computerRow][computerColumn] = computerColor;
			alphabet[0] = 'a';
			printf("Computer places %c at %c%c.\n", computerColor, alphabet[computerRow], alphabet[computerColumn]);
			
			// Flip Tiles
			for(int m=-1; m<2; m++){
				for(int n=-1; n<2; n++){
					availableMove2 = checkLegalInDirection(board, size, computerRow, computerColumn, computerColor, m, n);
					if (availableMove2 == true){
						int k=1;
						while(board[computerRow+k*m][computerColumn+k*n] == playerColor){
							board[computerRow+k*m][computerColumn+k*n] = computerColor;
							k++;
						}
					}
				}
			}
			
			printBoard(board,size);
		}
		pMoveAvailable = movesAvailable(board, size, playerColor);
		if (cMoveAvailable == false && pMoveAvailable == true)
			printf("%c player has no valid move.\n", computerColor);
			
		makePlayerMove = true;
	}
	//if player's move invalid, computer wins
	if(moveValid == false){
		printf("Invalid move.\n");
		printf("%c player wins.\n", computerColor);
	}
	//if there are no more moves available, count how many tiles each color has
	cMoveAvailable = movesAvailable(board, size, computerColor);
	if(pMoveAvailable == false && cMoveAvailable == false){
		for(int rowCounter = 0; rowCounter < size*size; rowCounter++){
			for(int colCounter = 0; colCounter < size*size; colCounter++){
				if (board[rowCounter][colCounter] == playerColor)
					playerTiles++;
				else if(board[rowCounter][colCounter] == computerColor)
					computerTiles++;
			}
		}
		if(playerTiles>computerTiles)
			printf("%c player wins.\n", playerColor);
		else if(computerTiles>playerTiles)
			printf("%c player wins.\n", computerColor);
		else
			printf("Draw!\n");
		
	}
	
    return 0;
}
#endif // DO NOT DELETE THIS LINE
