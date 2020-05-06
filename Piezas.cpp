//Piezas.cpp
//CSCI 430 Quiz 03
//Brendan Allen

#include "Piezas.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

const bool debug = true; //debugger boolean

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
    // initalize vector board to "Blank" Pieces
    for(int i = 0; i < BOARD_ROWS; i++)
    {
        std::vector<Piece> columns;
        for(int j = 0; j < BOARD_COLS; j++)
        {
            columns.push_back(Blank);
        }//for j
        board.push_back(columns);
    }//for i

    turn = Piece::X; //specify that it is X's turn first

    if(debug)
    {
        for(int i = (int)board.size(); i >= 0; i--)
        {
            for(int j = 0; j < (int)board[i].size(); j++)
            {
                // cout << board[i][j] << " ";
                cout << "[" << i << ","<<j<<"] ";
            }//for j
            cout << endl;
        }//for i
    }//debug
}//Piezas()

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    // reset board to have blank pieces
    for(int i = 0; i < BOARD_ROWS; i++)
    {
        for(int j = 0; j < BOARD_COLS; j++)
        {
            board[i][j] = Blank;
        }//for j
    }//for i
}//reset()

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
    //if the placement is out of bounds, it will not be allowed and is 'Invalid'
    if(column + 1 > BOARD_COLS) return Invalid;

    Piece current_piece = turn; //grab the correct piece for whose turn it is
    turn = turn == X ? O : X; //toggle whice Piece's turn it is
    for(int i = 0; i < BOARD_COLS; i++)
    {
        //place the piece in the first 'Blank' space
        if(board[i][column] == Blank)
        {
            if(debug)
            {
                cout << "Placing " << current_piece << " at " << board[i][column] << endl;
            }
            return board[i][column] = current_piece;
        }//if
    }//for i
    return Blank; //case of the column being full
}//dropPiece()

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    return (row + 1 > BOARD_ROWS || column + 1 > BOARD_COLS) ? Invalid : board[row][column];
}//pieceAt()

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
    // Check to make sure all of the spaces have been filled
    for(int i = 0; i < BOARD_ROWS; i++)
    {   
        for(int j = 0; j < BOARD_COLS; j++)
        {
            if(board[i][j] == Blank) return Invalid;
        }//for j
    }//for i

    // declare some global variables to maintain highest 
    int x_global = 0;
    int o_global = 0;

    // Scan each row and find the max consecutive X's & O'x
    for(int i = 0; i < BOARD_ROWS; i++)
    {
        int x_local = 0;
        int o_local = 0;
        for(int j = 0; j < BOARD_COLS; j++)
        {
            Piece cur = board[i][j];
            if(cur == X)
            {
                x_local++;
                o_global = (o_local > o_global) ? o_local : o_global;
                o_local = 0;
            }//if
            else if(cur == O)
            { 
                o_local++;
                x_global = (x_local > x_global) ? x_local : x_global;
                x_local = 0;
            }//else if
        }//for j
        x_global = x_local;
        o_global = o_local;
    }//for i


    // Only proceeed if neither of them is equal to 4
    // 4 is the highest number of consecutive pieces
    // you can have
    if(x_global != 4 && o_global != 4)
    {
        for(int i = 0; i < BOARD_COLS; i++)
        {
            int x_local = 0;
            int o_local = 0;
            for(int j = 0; j < BOARD_ROWS; j++)
            {
                Piece cur = board[j][i];
                if(cur == X)
                {
                    x_local++;
                    o_global = (o_local > o_global) ? o_local : o_global;
                    o_local = 0;
                }//if
                else if(cur == O)
                { 
                    o_local++;
                    x_global = (x_local > x_global) ? x_local : x_global;
                    x_local = 0;
                }//else if
            }//for j
            x_global = (x_local > x_global) ? x_local : x_global;
            o_global = (o_local > o_global) ? o_local : o_global;
        }//for i
    }//if

    if(o_global > x_global)
    {
        return O;
    }//if
    else if(x_global > o_global)
    {
        return X;
    }//else if
    
    return Blank;
}


// //empty main to check compilation
// int main() {
//     Piezas g;
//     g.dropPiece(3);//x
//     g.dropPiece(2);//o
//     g.dropPiece(1);//x
//     g.dropPiece(3);//o
//     g.dropPiece(3);//x
//     g.dropPiece(0);//o
//     g.dropPiece(1);//x
//     g.dropPiece(0);//o
//     g.dropPiece(0);//x
//     g.dropPiece(2);//o
//     g.dropPiece(1);//x
//     g.dropPiece(2);//o
//     cout << g.gameState() << endl;
//     return 0;
// }