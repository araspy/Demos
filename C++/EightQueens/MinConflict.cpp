//Solve Eight Queens Problem Using Artificial Intelligence Algorithm: "Min-Conflict"
#include <iostream>


void initializeBoard(int board[8][8]);
int countConflict(int board[8][8]);
int countConflict(int board[8][8], int row, int col); //overloading for counting conflict of specific location
int solveBoard(int board[8][8]);
int findMinRow(int numRowConflict[8]);
void displayBoard(int board[8][8]);	//for debugging



int main(int argc, char* argv[])
{
	//declare data structures and local variables
	int queenBoard[8][8]; 	//array giving the row (0-7) for queen in each column (0-7)
	int numSteps = 0;		//number of iterations required to reach solution
	srand(time(NULL));		// seeding random number for first queen placement


	//initialize board (place queens)
	initializeBoard(queenBoard);

	//min-conflict search, step count, loop until is final state
	numSteps = solveBoard(queenBoard);

	//print solution
	std::cout << "Number of steps to reach solution = " << numSteps << std::endl;
	std::cout << "Final rows of queens: ";
	for (int idx = 0; idx < 8; idx++) {
		std::cout << " " << queenBoard[idx];
	}
	std::cout << std::endl;



	system("pause");
	return 0;
}


/*
calculate and return number of conflicts queen has (vertical, horizontal, diagonal)
this function just takes the board
*/
int countConflict(int board[8][8]) {
	int conflicts = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == 1) {
				conflicts += countConflict(board, i, j);
			}
		}
	}

	return conflicts;
}


/*
calculate and return number of conflicts queen has (vertical, horizontal, diagonal)
this function takes the board, row, and col
*/
int countConflict(int board[8][8], int row, int col) {
	int conflicts = 0;

	//loop through columns to find row conflicts
	for (int j = 0; j < 8; j++) {
		if (board[row][j] == 1 && j != col) {//found queen while checking independent position
			conflicts++;
			break;
		}
	}

	//detect diagonal conflict
	//first search down and to the left
	for (int i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--) {
		if (board[i][j] == 1) {
			conflicts++;
			break;
		}
	}

	//next search up and to the right
	for (int i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++) {
		if (board[i][j] == 1) {
			conflicts++;
			break;
		}
	}

	//detect diagonal conflict
	//first up and to the left
	for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == 1) {
			conflicts++;
			break;
		}
	}

	//next search down and to the right
	for (int i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++) {
		if (board[i][j] == 1) {
			conflicts++;
			break;
		}
	}

	return conflicts;
}

/*
Initialize queen rows upon the chess board
TODO: use min-detection for following placements
*/
void initializeBoard(int board[8][8]) {
	//initialize empty board representing empty spaces with 0
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = 0;
		}
	}
	//initialize queen starting points
	board[rand() % 8][0] = 1;	//setting first queen in random row
	board[2][1] = 1;
	board[4][2] = 1;
	board[1][3] = 1;
	board[6][4] = 1;
	board[5][5] = 1;
	board[7][6] = 1;
	board[3][7] = 1;

}

/*
Use min-conflict algorithm to move pieces to solution state.
Return number of steps required to reach solution state.

iterate column to detect queen, count conflicts,
if conflict > 0, count conflicts for every row in current column, move queen
to lowest conflict row. then go to next column and repeat (with assumption of one queen per column)
*/
int solveBoard(int board[8][8]) {
	int stepCnt = 0;
	int numConflict;
	int minRow;
	bool conflictsFound;
	int numRowConflict[8];

	do {
		conflictsFound = false;
		for (int j = 0; j < 8; j++)
		{
//			displayBoard(board);
			for (int i = 0; i < 8; i++) { //find queen in current column
				if (board[i][j] == 1) { //when found
					numConflict = countConflict(board, i, j); //count current conflicts
					if (numConflict > 0) { //if conflicts exist
						conflictsFound = true;
						board[i][j] = 0; //pick up queen
						numRowConflict[i] = numConflict; //set conflict value at current queen position
						for (int row = 0; row < 8; row++) {
							if (row != i) { //check the conflicts for every row other than the one queen is already in
								board[row][j] = 1;  //place queen down
								numRowConflict[row] = countConflict(board, row, j); //check conflicts in new position
								board[row][j] = 0;   //pick queen up
							}
						}
						minRow = findMinRow(numRowConflict);
						for (int idx = 0; idx < 8; idx++) {
							if (idx != i) {
								if (numRowConflict[idx] <= numRowConflict[minRow]) {
									board[idx][j] = 1;
									break;
								}
							}
							if (idx == i) {
								minRow++;
							}
						}
						stepCnt++;
						break;  //exit row loop
					}
				}
			}
		}
	} while (conflictsFound);

	return stepCnt;
}



int findMinRow(int numRowConflict[8]) {
	int minimum = 0;
	for (int idx = 1; idx < 8; idx++) {
		if (numRowConflict[idx] < numRowConflict[minimum]) {
			minimum = idx;
		}
	}
	return minimum;
}  




void displayBoard(int board[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << board[i][j] << " ";
		}
		std::cout << std::endl;
	}
}














