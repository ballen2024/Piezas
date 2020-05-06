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
}

/***** Testing of Constructor Piezas() ******/

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

TEST(PiezasTest, checkCorrectTurn)
{
	Piezas obj; //create game object
	Piece first_turn = obj.dropPiece(0); //drop an X in column 0
	ASSERT_EQ(first_turn, X);
}//checkCorrectTurn

/***** Testing of reset() *****/

TEST(PiezasTest, resetBoard)
{
	Piezas obj; //create game object
	Piece first_turn = obj.dropPiece(0); //drop an X in column 0
	obj.reset(); //reset the board
	ASSERT_EQ(obj.pieceAt(0,0), Blank); //assert that the X we just dropped has been reset
}//resetBoard


/***** Testing of dropPiece() *****/

TEST(PiezasTest, outofBounds)
{
	Piezas obj; //create game object
	Piece dropped = obj.dropPiece(4); //drop an X in column 4 (out of bounds)
	ASSERT_EQ(dropped, Invalid);
}//outofBounds

TEST(PiezasTest, turnToggling)
{
	Piezas obj; //create game object
	Piece first_turn = obj.dropPiece(0); //drop an X in column 0
	Piece second_turn = obj.dropPiece(0); //drop an O in column 0
	ASSERT_EQ(second_turn, O);
}//turnToggling

/***** Testing of pieceAt() *****/

/***** Testing of gameState() *****/