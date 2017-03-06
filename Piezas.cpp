#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
	for(int i = 0; i < BOARD_COLS; i++)
	{
		std::vector<Piece> aBoard;
		for(int j = 0; j < BOARD_ROWS; j++)
		{
			Piece p = Blank; 
			aBoard.push_back(p);
		}	
		board.push_back(aBoard);
	}
	turn = X;
	
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
	while(!board.empty())
	{
		board.pop_back();
	}	

	for(int i = 0; i < BOARD_COLS; i++)
	{
		std::vector<Piece> aBoard;
		for(int j = 0; j < BOARD_ROWS; j++)
		{
			Piece p = Blank; 
			aBoard.push_back(p);
		}	
		board.push_back(aBoard);
	}
		
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
	Piece currentTurn = turn;
	std::vector<Piece> toBeSwapped;
	std::vector<Piece> tmp;
	tmp = board[column-1];
	Piece p = tmp.back();
	tmp.pop_back();
	while(p != Blank)
	{
		toBeSwapped.push_back(p);	
		p = tmp.back();
		tmp.pop_back();
	}
	if(toBeSwapped.size() == 4)
	{
			return Blank;
	}

	toBeSwapped.push_back(turn);
	while(toBeSwapped.size() != 4)
	{
		toBeSwapped.push_back(Blank); 
	}
	board[column-1].swap(toBeSwapped);
	if(turn == X)
	{
		turn = O;
	}
	else
	{
		turn = X;
	}
	return currentTurn;
	
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
	if((row <= BOARD_ROWS) && (column <= BOARD_COLS)) 
	{
		return board[row][column];		
	}
	return Invalid; 
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
	int oScore = 0; 
	int xScore = 0;
	int xFlag = 5;
	int oFlag = 5;
	for(int i = 0; i < BOARD_COLS; i++) 
	{
		for(int j = 0; j < BOARD_ROWS; j++) 
		{
			if(board[i][j] == X)
			{
				if((j == xFlag)	|| (j == xFlag + 1) || (j == xFlag - 1))
				{
					xScore +=1; 
				}	
				xFlag = j; 
			}		
			else if(board[i][j] == O)
			{
				if((j == oFlag)	|| (j == oFlag + 1) || (j == oFlag - 1))
				{
					oScore +=1; 
				}	
				oFlag = j; 

			}
		}
	}

	if(checkProgress())
	{
		if(oScore < xScore)
		{
			return X;
		}
		else if(oScore > xScore)
		{
			return O;
		}
		else if(oScore == xScore)
		{
			return Blank;
		}
	}

	return Invalid;
}

bool Piezas::checkProgress()
{
	for(int i = 0; i < BOARD_COLS; i++) 
	{
		for(int j = 0; j < BOARD_ROWS; j++)
		{
			if(board[i][j] == Blank)
			{
				return false;
			}
		}
	}
	return true; 
}	
