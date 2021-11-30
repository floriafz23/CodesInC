/* 
 * Purpose: Create a code in C that utilizes arrays, loops, and relational statements.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARDROWS 9
#define BOARDCOLS 11

bool dumpComputer = true; //causes dump of computer board before game if true (for debugging)

// boards. 0 means empty, non-zero means ship is there, number is size, -tive means hit on a ship
int playerBoard[BOARDROWS+1][BOARDCOLS+1];
int computerBoard[BOARDROWS+1][BOARDCOLS+1];
int compShotBoard[BOARDROWS+1][BOARDCOLS+1];

int getRand(int lowval,int highval){
    return (rand()%(highval+1-lowval) + lowval);
}




int getShot(bool fromUser, int board[BOARDROWS+1][BOARDCOLS+1]){
    int row,col;
    
    while(1){
        if(fromUser){
            printf("Give a shot (row, col):");
            scanf("%d%d",&row,&col);
            if(col<1 || col > BOARDCOLS || row < 1 || row > BOARDROWS)
                printf("Invalid input\n");
            else  //valid input
                break;
        }
        else { //computer generated
            row=getRand(1,BOARDROWS);
            col=getRand(1,BOARDCOLS);
            if(compShotBoard[row][col]==0) { //make sure haven't shot here before
                compShotBoard[row][col]=1; //valid shot
                break;
            }
        }
    } //will leave this loop with valid input
    if(board[row][col] != 0){
        if(board[row][col]>0)
            board[row][col]= -1*board[row][col]; //make sure is -tive
        return -1*board[row][col]; //a hit!
    }
    return 0; //miss
}
            

bool allShipsNotHit(int board[BOARDROWS+1][BOARDCOLS+1]){
    for(int i=1;i<=BOARDROWS;i++){
        for(int j=1;j<=BOARDCOLS;j++){
            if(board[i][j]>0) //ship and not hit
                return(true);
        }
    }
    return (false); //no ships found not all hit
}

bool noneLeft(int valueToFind,int board[BOARDROWS+1][BOARDCOLS+1]){
    for(int i=1;i<=BOARDROWS;i++){
        for(int j=1;j<=BOARDCOLS;j++){
            if(board[i][j]==valueToFind) //ship and not hit
                return(false);
        }
    }
    return (true); //no ships found, all hit
}


void populateBoard(bool getUserInput, int board[BOARDROWS+1][BOARDCOLS+1]){

	// declaring all variables and initializing populate board program
	int row, column, orientation;
	bool continueProgram;
	
	// print header information
	if(getUserInput == true){
		printf("Rows are 1 - 9, Columns are 1 - 11\n");
		printf("Orientation is 0 for across, 1 for down\n");
	}
	int i=5;
	//enter while loop to get input from ship sizes 5 to 1
	while(i>=1){
		
		// first board is player's board (get input from keyboard)
		if(getUserInput == true){
			printf("Give starting row, starting column and orientation (3 inputs) for ship of size=%d:", i);
			scanf("%d %d %d", &row, &column, &orientation);
		}
		
		//second board is computer (random inputs)
		else if(getUserInput == false){
			row = getRand(1,9);
			column = getRand(1,11);
			orientation = getRand(0,1);
		}
			
		// check validity of values (if values are within range and inside the board), if not, invalid
		if (row < 1 || row > 9 || column < 1 || column > 11 || orientation < 0 || orientation > 1 || (orientation == 0 && column+i>12) || (orientation == 1 && row+i>10)) {
			if(getUserInput==true){
				printf("Invalid Input\n");
			}
		}
		
		// check if input is overlapping with existing ships, if yes then invalid
		else {
			continueProgram=true;
			if(orientation == 0){
				for(int a=0; a<1; a++){
					if(board[row][column+a] != 0){
						continueProgram=false;
					}
				}
			}
			if(orientation == 1){
				for(int d=0; d<1; d++){
					if(board[row+d][column] != 0){
						continueProgram=false;
						
					}
				}
			}

			if (continueProgram==false){
                  if (getUserInput == true) {
                    printf("Conflicts with ship already placed\n");
                  }
            }
			// if no issues with inputs, then assign values to board
			else if (continueProgram==true){
				if(orientation == 0){
					for(int a=column; a<column+i; a++){
						board[row][a] = i;
					}
				}
				if(orientation == 1){
					for(int d=row; d<i+row; d++){
						board[d][column] = i;
					}
				}        
				// next ship size
				i--;
			}
		}
	}
}

void showBoard(int board[BOARDROWS+1][BOARDCOLS+1]){
    printf("   Cols\n");
    printf("    1  2  3  4  5  6  7  8  9 10 11\n");
    printf("     ________________________________\n");
    for(int i=1;i<=BOARDROWS;i++){
        printf("R%d|",i);
        for(int j=1;j<=BOARDCOLS;j++){
            if(board[i][j]>=0)
                printf(" ");
            printf("%d ",board[i][j]);
        }
        printf("|\n");
    }
    printf("  __________________________________\n");
}

int main(int argc, char **argv)
{
    bool playerBoardOK,computerBoardOK;
    
    // initialize the seed randomly. 

     	srand(time(NULL)); 

    //init the boards
    for(int i=0;i<BOARDROWS;i++){
        for(int j=0;j<BOARDCOLS;j++){
            playerBoard[i][j]=0;
            computerBoard[i][j]=0;
            compShotBoard[i][j]=0;
        }
    }

    populateBoard(true,playerBoard);
    populateBoard(false,computerBoard);
    printf("Your board is\n");
    showBoard(playerBoard);
    if(dumpComputer){
        printf("\n\nComputer board is\n");
        showBoard(computerBoard);
    }

    // play starts here
    playerBoardOK=true;
    computerBoardOK=true;
    while(playerBoardOK && computerBoardOK){
        int hit=getShot(true,computerBoard); //shot from user
        if(hit){
            printf("HIT on size %d\n",hit);
            if(noneLeft(hit,computerBoard))
                printf("Sunk computer's %d\n",hit);
        }
        else
            printf("MISS!!\n");
        hit=getShot(false,playerBoard);
        if(hit){
            printf("Computer hits! Size=%d\n", hit);
            if(noneLeft(hit,computerBoard))
                printf("Sunk your %d\n",hit);
        }
        else
            printf("Computer miss!\n");
        playerBoardOK = allShipsNotHit(playerBoard);
        computerBoardOK = allShipsNotHit(computerBoard);
//    showBoard(playerBoard); //debug
//    showBoard(computerBoard); //debug
   }
   if(playerBoardOK)
       printf("You win!\n");
    else
        printf("You lose.\n");
    showBoard(computerBoard);

	return 0;
}
