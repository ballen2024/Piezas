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
		}
	}
}

TEST(PiezasTest, checkCorrectTurn)
{
	Piezas obj; //create game object
	Piece first_turn = obj.dropPiece(0); //drop an X in column 0
	ASSERT_EQ(first_turn, X);
}

/***** Testing of reset() *****/

TEST(PiezasTest, resetBoard)
{
	Piezas obj; //create game object
	Piece first_turn = obj.dropPiece(0); //drop an X in column 0
	obj.reset(); //reset the board
	ASSERT_EQ(obj.pieceAt(0,0), Blank); //assert that the X we just dropped has been reset
}
