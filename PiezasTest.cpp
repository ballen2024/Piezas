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
	ASSERT_NEQ(first_turn, O);
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

TEST(PiezasTest, outofBounds)
{
	Piezas obj; //create game object
	Piece dropped = obj.dropPiece(4); //drop an X in column 4 (out of bounds)
	ASSERT_EQ(dropped, Invalid);
}//outofBounds

TEST(PiezasTest, turnTogglingO)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	Piece second_turn = obj.dropPiece(0); //drop an O in column 0
	ASSERT_EQ(second_turn, O);
}//turnTogglingO

TEST(PiezasTest, turnTogglingX)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop and O in column 0
	Piece third_turn = obj.dropPiece(1); //drop an X in column 1
	ASSERT_EQ(third_turn, X);
}//turnTogglingX

TEST(PiezasTest, fullColumn)
{
	Piezas obj; //create game object
	obj.dropPiece(0); //drop an X in column 0
	obj.dropPiece(0); //drop an O in column 0
	obj.dropPiece(0); //drop an X in column 0
	Piece lost_turn = obj.dropPiece(0); //attemp to drop an O in colum 0
	ASSERT_EQ(lost_turn, Blank);
}//fullColumn

/****** End of dropPiece() Testing ******/


/***** Testing of pieceAt() *****/

/***** End of pieceAt() Testing *****/

/***** Testing of gameState() *****/

/***** End of gameState() Testing *****/