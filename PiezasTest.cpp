/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}//sanityCheck

/***** Testing of Constructor Piezas() ******/

/* Make sure that the constructor creates a blank board */
TEST(PiezasTest, startBlank)
{
	Piezas obj; //create game object
	for(int i = 0; i < BOARD_ROWS; i++)
	{
		for(int j = 0; j < BOARD_COLS; j++)
		{
			ASSERT_EQ(obj.pieceAt(i , j), Blank);
		}// for j
	}// for i
}//startBlank

/* Make sure that the constructor correctly sets the turn to X on init */
TEST(PiezasTest, checkCorrectTurn)
{
	Piezas obj; //create game object
	Piece first_turn = obj.dropPiece(0); //drop an X in column 0
	ASSERT_EQ(first_turn, X);
}//checkCorrectTurn

/* Sad test to make sure that it is never O's turn first */
TEST(PiezasTest, incorrectTurnOnInit)
{
	Piezas obj; //create game object
	Piece first_turn = obj.dropPiece(0); //drop an X in column 0
	ASSERT_NE(first_turn, O);
}//incorrectTurnOnInit

/****** End of Constructor Testing *****/


/***** Testing of reset() *****/

TEST(PiezasTest, resetBoard)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.reset(); //reset the board
	ASSERT_EQ(obj.pieceAt(0,0), Blank); //assert that the X we just dropped has been reset
}//resetBoard

/***** End of reset() Testing *****/


/***** Testing of dropPiece() *****/

/* attempt to drop the piece out of bounds */
TEST(PiezasTest, outofBounds)
{
	Piezas obj; //create game object
	Piece dropped = obj.dropPiece(4); //drop an X in column 4 (out of bounds)
	ASSERT_EQ(dropped, Invalid);
}//outofBounds

/* attempt to drop the piece at a negative index */
TEST(PiezasTest, negativeIndex)
{
	Piezas obj; //create game object
	Piece dropped = obj.dropPiece(-1); //drop an X in column 4 (out of bounds)
	ASSERT_EQ(dropped, Invalid);
}//negativeIndex

/* ensure that the turn toggles from X to O */
TEST(PiezasTest, turnTogglingO)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	Piece second_turn = obj.dropPiece(0); //drop an O in column 0
	ASSERT_EQ(second_turn, O);
}//turnTogglingO

/* ensure that the turn toggles from O to X */
TEST(PiezasTest, turnTogglingX)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop and O in column 0
	Piece third_turn = obj.dropPiece(1); //drop an X in column 1
	ASSERT_EQ(third_turn, X);
}//turnTogglingX

/* attempt to drop a piece in a full column; specifically check that it returns Blank */ 
TEST(PiezasTest, fullColumn)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop an O in column 0
	obj.dropPiece(0); //drop an X in column 0
	Piece lost_turn = obj.dropPiece(0); //attemp to drop an O in colum 0
	ASSERT_EQ(lost_turn, Blank);
}//fullColumn

/* Make sure that the turn is correctly lost and the turn toggles */
TEST(PiezasTest, loseTurn)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop an O in column 0
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //attempt to drop an O in colum 0; should lose turn
	Piece p = obj.dropPiece(1); //drop an X in column 1
	ASSERT_EQ(p, X);
}//loseTurn

/****** End of dropPiece() Testing ******/


/***** Testing of pieceAt() *****/

/* Make sure pieceAt() correctly handles an out of bounds row */
TEST(PiezasTest, rowOutOfBounds)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop an O in column 0
	Piece out_of_bounds = obj.pieceAt(4, 0); //attempt to look at a space that doesn't exist
	ASSERT_EQ(out_of_bounds, Invalid);
}//rowOutOfBounds

/* Make sure pieceAt() correctly handles an out of bounds column */
TEST(PiezasTest, columnOutOfBounds)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop an O in column 0
	Piece out_of_bounds = obj.pieceAt(0, 5); //attempt to look at a space that doesn't exist
	ASSERT_EQ(out_of_bounds, Invalid);
}//columnOutOfBounds

/* Make sure both row & column out of bounds indeces are handled correctly */
TEST(PiezasTest, bothOutOfBounds)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop an O in column 0
	Piece out_of_bounds = obj.pieceAt(4, 5); //attempt to look at a space that doesn't exist
	ASSERT_EQ(out_of_bounds, Invalid);
}//bothOutOfBounds

/* Make sure function handles negative index correctly */
TEST(PiezasTest, negativeRowIndex)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop an O in column 0
	Piece out_of_bounds = obj.pieceAt(-1, 0); //attempt to look at a space that doesn't exist
	ASSERT_EQ(out_of_bounds, Invalid);
}//negativeRowIndex

/* Make sure function handles negative index correctly */
TEST(PiezasTest, negativeColumnIndex)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop an O in column 0
	Piece out_of_bounds = obj.pieceAt(0, -1); //attempt to look at a space that doesn't exist
	ASSERT_EQ(out_of_bounds, Invalid);
}//negativeColumnIndex

/* Check for Blank space */
TEST(PiezasTest, checkBlankSpace)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop an O in column 0
	Piece blank = obj.pieceAt(0, 1);
	ASSERT_EQ(blank, Blank);
}//bothOutOfBounds

/* Check for X space */
TEST(PiezasTest, checkXSpace)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop an O in column 0
	Piece x = obj.pieceAt(0, 0);
	ASSERT_EQ(x, X);
}//bothOutOfBounds

/* Check for O space */
TEST(PiezasTest, checkOSpace)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop an O in column 0
	Piece o = obj.pieceAt(1, 0);
	ASSERT_EQ(o, O);
}//bothOutOfBounds

/***** End of pieceAt() Testing *****/


/***** Testing of gameState() *****/

/* Make sure incomplete Game is handled correctly */
TEST(PiezasTest, gameNotOver)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop an O in column 0
	Piece incompleteGame = obj.gameState();
	ASSERT_EQ(incompleteGame, Invalid);
}//gameNotOver

/* Check handling of a tie game */
TEST(PiezasTest, gameIsATie)
{
	Piezas obj; //create game object
	for(int i = 0; i < BOARD_ROWS; i++)
	{
		for(int j = 0; j < BOARD_COLS; j++)
		{
			obj.dropPiece(j); //auto populate board
		}//for j
	}// for i
	Piece tie_game = obj.gameState();
	ASSERT_EQ(tie_game, Blank);
}//gameIsATie

/* check handling of an X victory */
TEST(PiezasTest, xVictory)
{
	Piezas obj; //create game object
	obj.dropPiece(0);
	obj.dropPiece(3);
	obj.dropPiece(2);
	obj.dropPiece(3);
	obj.dropPiece(3);
	obj.dropPiece(2);
	obj.dropPiece(1);
	obj.dropPiece(2);
	obj.dropPiece(1);
	obj.dropPiece(0);
	obj.dropPiece(1);
	obj.dropPiece(0);
	Piece x_victory = obj.gameState();
	ASSERT_EQ(x_victory, X);
}//xVictory




/***** End of gameState() Testing *****/