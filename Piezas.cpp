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
    :board(4, std::vector<Piece>(3))
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3;j++){
            board[i][j] = Blank;
        }
    }
    turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3;j++){
            board[i][j] = Blank;
        }
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
    if(column > 3 || column<0){
        return Invalid;
    }
    Piece piecePlayed = turn;
    bool valid = true;
    //play a piece in the column
    if(board[column][0]==Blank){
        board[column][0] = turn;
    }else if(board[column][1]==Blank){
        board[column][1] = turn;
    }else if(board[column][2]==Blank){
        board[column][2] = turn;
    }else {valid = false;}

    //flip turn
    if(turn == X){
        turn = O;
    }else if(turn == O){
        turn = X;
    }

    //return the piece played if play was valid
    //else return Invalid
    if(valid){return piecePlayed;}
    else{return Blank;}

    return Blank;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    if(row>2 || row<0 || column>3 || column<0){
        return Invalid;
    }
    //Piece local;
    //local = board[column][row];
    //return local;
    return board[column][row];
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
    int i, j;
    //check if board full
    for(i = 0; i < 4; i++){
        for(j = 0; j < 3;j++){
            if(board[i][j] == Blank){
                return Invalid;
            }
        }
    }

    int xnum = 0; int xmax = 0;
    int onum = 0; int omax = 0;
    Piece curr = Blank;
    //checking columns first
    for(i=0; i<4; i++){
        for(j=0; j<3; j++){
            curr = pieceAt(j, i);
            if(curr == X){
                onum=0;
                xnum++;
                if(xnum>xmax){xmax = xnum;}
            }else if(curr == O){
                xnum=0;
                onum++;
                if(onum>omax){omax = onum;}
            }
        }
    }
    onum=0; xnum=0; //reset
    //now check rows
    for(j=0; j<3; j++){
        for(i=0; i<4; i++){
            curr = pieceAt(j, i);
            if(curr == X){
                onum=0;
                xnum++;
                if(xnum>xmax){xmax = xnum;}
            }else if(curr == O){
                xnum=0;
                onum++;
                if(onum>omax){omax = onum;}
            }
        }
    } 

    if(xmax > omax){
        return X;
    }else if(omax > xmax){
        return O;
    }else{return Blank;}
}