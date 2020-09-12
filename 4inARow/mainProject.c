




#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

/*************** Board ***************/
#define ROWS 6
#define COLS 7
char board[ROWS][COLS];


/*********** Declarations ************/

/// This function initializes the game board by assigning each cell
/// with ' ' (resulting with an empty game board).
void initBoard();

/// This function gets a row number and a column number (a cell),
/// and returns the character in that cell (could be 'X', 'O' or ' ').
/// For example:
/// char c = getCell(1, 1);
char getCell(int row, int col);

/// This function gets a row number, a column number and a sign,
/// and assigns the cell with the given sign.
/// For example:
/// setCell(1, 1, 'X');
void setCell(int row, int col, char sign);

/// This function clears the screen.
void clearScreen();

///This function gets a char, a row, and a column number,
///and returns true if the player represented by this char is victorious
///only downwards (4 in a row downwise).
bool isVictoriousDown(char ch, int row, int col);

///This function gets a char, a row, and a column number,
///and returns true if the player represented by this char is victorious
///only vertically (4 in a row to either side).
bool isVictoriousVertical(char ch, int row, int col);

///This function gets a char, a row, and a column number,
///and returns true if the player represented by this char is victorious
///only to the up and right or down and left .
bool isVictoriousCrossA(char ch, int row, int col);

///This function gets a char, a row, and a column number,
///and returns true if the player represented by this char is victorious
///only to the up and left or down and right .
bool isVictoriousCrossB(char ch, int row, int col);

///This function gets a char, a row, and a column number,
///and returns true if the player representer by this char is victorious
///using all of the other fuctions.
bool isVictorious(char ch, int row, int col);

///This function check if the board if full,
///and returns true if it is or flase otherwise
bool isBoardFull();

///This function prints the board.
void printBoard();

///This function fills the board with 'X'
void fillBoard();
/*************** Main ****************/
//4 in a row game
void main()
{
	int i; //indicates for the first avaible place in the column
	int player = 1; //indicates which player is playing
	int playerInput; //the player input (column number)
	initBoard(); //start with empty board
	printBoard(); //print the board
	//the game loop, goes on until the board is full (happens when someone wins)
	while (!(isBoardFull()))
	{
		i = ROWS + 1;
		printf("\nPlayer number %d:\nPlease enter column input(a number between 1 - 7) :", player);
		scanf("%d", &playerInput); //first input for player 1

		//check valid input
		if (playerInput > ROWS+1 || playerInput <= 0 || getCell(1,playerInput) != ' ') 
		{
			clearScreen();
			printBoard();
			printf("Not a valid input, Try AGAIN!");
		}

		//turns
		else
		{
			//check for the valid place in the column
			while (getCell(i, playerInput) != ' ') 
			{
				i--;
			}
			//player 1 turn
			if (player == 1)
			{
				setCell(i, playerInput, 'X');
				//check for victory
				if (isVictorious('X', i, playerInput))
				{
					clearScreen();
					printBoard();
					printf("\nThe Victory belongs to player 1! Congrats!! :)");
					fillBoard(); //to stop the game
				}
				//check for tie
				else if (isBoardFull()) {
					clearScreen();
					printBoard();
					printf("It's a tie!");
				}
				//continue for next turn
				else
				{
					clearScreen();
					printBoard();
					player = 2;
				}
			}
			//player 2 turn
			else 
			{
				setCell(i, playerInput, 'O');
				//check for victory
				if (isVictorious('O', i, playerInput))
				{
					clearScreen();
					printBoard();
					printf("\nThe Victory belongs to player 2! Congrats!! :)");
					fillBoard(); // to stop the game
				}
				//check for tie
				else if (isBoardFull()) {
					clearScreen();
					printBoard();
					printf("It's a tie!");
				}
				//continue for next turn
				else
				{
					clearScreen();
					printBoard();
					player = 1;
				}
			
			}		
		
		}

	}
}//main


/********** Implementations **********/
char getCell(int row, int col)
{
	return board[row - 1][col - 1];
}

void setCell(int row, int col, char sign)
{
	board[row - 1][col - 1] = sign;
}

void initBoard()
{
	int i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			setCell(i + 1, j + 1, ' ');
		}
	}
}

void clearScreen()
{
	system("cls");
}

bool isVictoriousDown(char ch, int row, int col)
{
	int count = 0;
	if (row <= ROWS - 3) {
		if (getCell(row + 1, col) == ch)
			count++;
		if (getCell(row + 2 ,col) == ch)
			count++;
		if (getCell(row + 3, col) == ch)
			count++;
	}
	return (count == 3);
}

bool isVictoriousVertical(char ch, int row, int col)
{
	int counterA = 0;
	if (col + 1 < COLS && getCell(row, col + 1) == ch) {
		counterA++;
		if (col + 2 < COLS && getCell(row, col + 2) == ch) {
			counterA++;
			if (col + 3 < COLS && getCell(row, col + 3) == ch)
				return true;
		}
	}
	if (col - 1 > 0 && getCell(row, col - 1) == ch) {
		counterA++;
		if (col - 2 > 0 && getCell(row, col - 2) == ch) {
			counterA++;
			if (col - 3 > 0 && getCell(row, col - 3) == ch)
				return true;
		}
	}
	return (counterA >= 3);
}

bool isVictoriousCrossA(char ch, int row, int col)
{
	int counterA = 0;
	if ((row - 1 >= 0) && (col + 1 <= COLS) && (getCell(row - 1, col + 1) == ch)) {
		counterA++;
		if ((row - 2 >= 0) && (col + 2 <= COLS) && (getCell(row - 2, col + 2) == ch)) {
			counterA++;
			if ((row - 3 >= 0) && (col + 3 <= COLS) && (getCell(row - 3, col + 3) == ch))
				return true;
		}
	}
	if ((row + 1 <= ROWS) && (col - 1 >= 0) && (getCell(row + 1, col - 1) == ch)) {
		counterA++;
		if ((row + 2 <= ROWS) && (col - 2 >= 0) && (getCell(row + 2, col - 2) == ch)){
			counterA++;
			if ((row + 3 <= ROWS) && (col - 3 >= 0) && (getCell(row + 3, col - 3) == ch)) 
				return true;
			}
	}
	return (counterA >= 3);
}

bool isVictoriousCrossB(char ch, int row, int col)
{
	int counterA = 0;
	if ((row + 1 <= ROWS) && (col + 1 <= COLS) && (getCell(row + 1, col + 1) == ch)) {
		counterA++;
		if ((row + 2 <= ROWS) && (col + 2 <= COLS) && (getCell(row + 2, col + 2) == ch)) {
			counterA++;
			if ((row + 3 <= ROWS) && (col + 3 <= COLS) && (getCell(row + 3, col + 3) == ch))
				return true;
		}
	}
	if ((row - 1 >= 0) && (col - 1 >= 0) && (getCell(row - 1, col - 1) == ch)) {
		counterA++;
		if ((row - 2 >= 0) && (col - 2 >= 0) && (getCell(row - 2, col - 2) == ch)) {
			counterA++;
			if ((row - 3 >= 0) && (col - 3 >= 0) && (getCell(row - 3, col - 3) == ch))
				return true;
		}
	}
	return (counterA >= 3);
}

bool isVictorious(char ch, int row, int col)
{
	return(isVictoriousCrossA(ch, row, col) || isVictoriousCrossB(ch, row, col) || isVictoriousDown(ch, row, col) || isVictoriousVertical(ch, row, col));
}

bool isBoardFull() 
{
	int i = 0;
	int count = 0;
	for (i; i < COLS; i++) {
		if (board[0][i] != ' ')
			count++;
	}
	return(count == COLS);
}

void printBoard() {
	int i = 0, j = 0;
	for (i; i < ROWS + 1; i++) {
		for (j; j < COLS + 1; j++) {
			if (i == 0) 
			{
				if (j == 0)
					printf("    ");
				else
					printf("%d   ", j);
			}
			else
			{
				if (j == 0)
					printf("%c   ", 'A' + i - 1);
				else
					printf("%c   ", board[i-1][j-1]);
			}

		}
		printf("\n\n");
		j = 0;
	}
}

void fillBoard()
{
	int i , j;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			setCell(i + 1, j + 1, 'X');
		}
	}
}
