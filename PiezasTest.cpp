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
//didnt breakcleear
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


//place a bunch of pieces, and then call gameState
//should return Invalid as game is not over
TEST(PiezasTest, nonEndedGameState){
	Piezas play;
	for(int i = 0; i<2; i++){
		play.dropPiece(0);
		play.dropPiece(2);
		play.dropPiece(3);
		play.dropPiece(1);
	}
	Piece gameend = Invalid;
	ASSERT_EQ(gameend, play.gameState());
}

TEST(PiezasTest, endTie){
	Piezas play;
	int i;
	for(i = 0; i<4; i++){
		play.dropPiece(i);
		play.dropPiece(i);
	}
	//fill in last 4
	for(i = 0; i < 4; i++){
		play.dropPiece(i);
	}
	Piece gameend = Blank;
	ASSERT_EQ(gameend, play.gameState());
}

//x will place pieces accross the bottom,
//O will place randomly, and x will interfere.
//will have 12 calls to dropPiece
TEST(PiezasTest, endXWinRow){
	Piezas play;
	play.dropPiece(0);//x
	play.dropPiece(0);
	play.dropPiece(1);//x
	play.dropPiece(0); // Last 0
	play.dropPiece(2);//x
	play.dropPiece(2);
	play.dropPiece(3);//x garuntees x win
	play.dropPiece(2); //Last 2
	play.dropPiece(1);//x
	play.dropPiece(3); 
	play.dropPiece(1);//x last 1
	play.dropPiece(3); //last 3
	Piece winner = X;
	ASSERT_EQ(winner, play.gameState());
}

//x will place pieces accross the bottom,
//O will place randomly, and x will interfere.
//will have 12 calls to dropPiece
//final gamestate:
// x x o x
// o o o o
// x o x x
TEST(PiezasTest, endoWinRow){
	Piezas play;
	play.dropPiece(0);//1
	play.dropPiece(0);
	play.dropPiece(0);//x 3
	play.dropPiece(1);
	play.dropPiece(2);//x 5
	play.dropPiece(1);
	play.dropPiece(1);//x 7
	play.dropPiece(2);
	play.dropPiece(3);//x 9
	play.dropPiece(3); 
	play.dropPiece(3);//x 11
	play.dropPiece(2); 
	Piece winner = O;
	ASSERT_EQ(winner, play.gameState());
}

//O should win with 3 vertical
//final gamestate:
// x o o x
// o x o o
// x x o x
TEST(PiezasTest, endOWinCol){
	Piezas play;
	play.dropPiece(1);//1
	play.dropPiece(2);
	play.dropPiece(0);//x 3
	play.dropPiece(2);
	play.dropPiece(3);//x 5
	play.dropPiece(0);
	play.dropPiece(1);//x 7
	play.dropPiece(1);
	play.dropPiece(0);//x 9
	play.dropPiece(3); 
	play.dropPiece(3);//x 11
	play.dropPiece(2); 
	Piece winner = O;
	ASSERT_EQ(winner, play.gameState());
}

//X should win with 3 vertical
//final gamestate:
// x x o o
// x o x o
// x o o x
TEST(PiezasTest, endXWinCol){
	Piezas play;
	play.dropPiece(0);//1
	play.dropPiece(2);
	play.dropPiece(0);//x 3
	play.dropPiece(1);
	play.dropPiece(0);//x 5
	play.dropPiece(1);
	play.dropPiece(3);//x 7
	play.dropPiece(3);
	play.dropPiece(2);//x 9
	play.dropPiece(3); 
	play.dropPiece(1);//x 11
	play.dropPiece(2); 
	Piece winner = X;
	ASSERT_EQ(winner, play.gameState());
}
