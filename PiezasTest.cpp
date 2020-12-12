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

//**** PIECEAT TESTS *
//will check 4 corner for out of bounds
//expected: should return invalid for all 4
TEST(PiezasTest, pieceOutOfBounds){
	Piezas play;
	Piece test = Invalid;
	//ASSERT_TRUE(test == Invalid);
	ASSERT_EQ(test, play.pieceAt(-1, 2));
	ASSERT_EQ(test, play.pieceAt(3, 2));
	ASSERT_EQ(test, play.pieceAt(1, 5));
	ASSERT_EQ(test, play.pieceAt(1, -1));
}
//will check every value inside the valid board
//if we get an invalid, that will break test
//else we are on the board
TEST(PiezasTest, randomPieceInBound){
	Piezas play;
	Piece test = Invalid;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 3; j++){
			ASSERT_NE(test, play.pieceAt(j, i));
		}
	}
}

//will confirm X is going first, will place a piece
//confirm o's turn, and confirm X piece at bottom of column, goes through 2 turns
TEST(PiezasTest, placeOneCheckTurn){
	Piezas play;
	Piece xturn = X;
	Piece oturn = O;
	//assert first piece played was x
	Piece firstpiece = play.dropPiece(2);
	ASSERT_EQ(firstpiece, play.pieceAt(0, 2));
	ASSERT_EQ(xturn, firstpiece);
	ASSERT_EQ(oturn, play.dropPiece(2));
	ASSERT_EQ(oturn, play.pieceAt(1, 2));
}

//tests reset game function, does NOT change the turn
//play a piece, reset the board, confirm the spot is blank,
//and play a new piece down that row and confirm that the droppiece
//didnt break
TEST(PiezasTest, resetGame){
	Piezas play;
	Piece turn = X;
	ASSERT_EQ(turn, play.dropPiece(0));
	ASSERT_EQ(turn, play.pieceAt(0, 0));
	play.reset();
	ASSERT_NE(turn, play.pieceAt(0, 0));
	turn = O;
	ASSERT_EQ(turn, play.dropPiece(0));
	ASSERT_EQ(turn, play.pieceAt(0, 0));

}