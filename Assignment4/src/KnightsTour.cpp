/*
 * File: KnightsTour.cpp
 * ---------------------
 * This program find a knight's tour on an N x M chessboard.
 */

#include <iostream>
#include <iomanip>
#include "grid.h"

using namespace std;

/* Function prototypes */

void solveKnightsTour(int n, int m);
void displayBoard(Grid<int> & board);
bool findKnightsTour(Grid<int> & board, int row, int col, int seq);
bool isWithLimit(Grid<int> & board,int x,int y);
int countStep(Grid<int> & board,int x,int y);

const int step[8][2]={{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2}};

/* Test program */

int test2() {
   solveKnightsTour(8, 8);
   return 0;
}

/*
 * Function: solveKnightsTour
 * Usage: solveKnightsTour(n, m);
 * ------------------------------
 * Solves the knight's tour problem for a n x m chessboard.
 */

void solveKnightsTour(int n, int m) {
   Grid<int> board(n, m);
   if (findKnightsTour(board, 0, 0, 1)) {
      displayBoard(board);
   } else {
      cout << "No tour exists for this board." << endl;
   }
}

/*
 * Function: displayBoard
 * Usage: displayBoard(board);
 * ---------------------------
 * Displays each of the squares in the board along with its sequence
 * number in the tour.
 */

void displayBoard(Grid<int> & board) {
   for (int i = board.numRows() - 1; i >= 0; i--) {
      for (int j = 0; j < board.numCols(); j++) {
         cout << " " << setw(2) << board[i][j];
      }
      cout << endl;
   }
}

bool isWithLimit(Grid<int> & board, int x,int y){
    return !(x<0||x>board.numRows()-1||y<0||y>board.numCols()-1);
}

int countStep(Grid<int> & board,int x,int y){
    if(!isWithLimit(board,x,y)||board[x][y]!=0){
        return 8;
    }
    int count = 0;
    for (int i=0;i<8;i++){
        if(isWithLimit(board,x+step[i][0],y+step[i][1])&&board[x+step[i][0]][y+step[i][1]]==0){
            count++;
        }
    }
    return count;
}

/*
 * Function: findKnightsTour
 * Usage: flag = findKnightsTour(board, row, col, seq);
 * ----------------------------------------------------
 * This function looks for a tour on the board, starting at
 * the position indicated by row and col. The seq parameter is
 * the sequence number of this move and is needed to keep
 * track of the steps on the tour. The function returns true
 * if a tour is found and false otherwise.
 *
 * This function begins by checking for three simple cases:
 *
 * 1. The position is off the board.
 * 2. The position has been previously visited.
 * 3. The tour is complete.
 *
 * In the first two cases, there can be no tour that begins
 * from that position on the board. In the last case, the
 * function can immediately return true.
 *
 * If the simple cases do not apply, the function marks the
 * current square and then tries all possible moves. If it
 * finds a tour from the resulting position, the function
 * returns true to the next highest level. If no moves lead
 * to a tour, the function must back out of this move and try
 * again at a higher level of the recursion.
 *
 * The for loops in this implementation are a little tricky.
 * They compute the row and column offsets for the next position by
 * noting that the row and column offsets add to 3 (either +1 and +2
 * or +2 and +1) and you need all four possible sign combinations.
 */

bool findKnightsTour(Grid<int> & board, int row, int col, int seq) {
    //TODO
    if (!isWithLimit(board,row,col)){return false;}
    if (board[row][col]==0){
        board[row][col]=seq;
        if (seq>=board.numRows()*board.numCols()){
            return true;
        }
        int stepCount[8];
        for (int i=0;i<8;i++){
            stepCount[i]=countStep(board,row+step[i][0],col+step[i][1]);
        }
        for (int i=0;i<8;i++){
            int minStep=9,next=0;
            for (int j=0;j<8;j++){
                if (minStep>stepCount[j]){
                    minStep=stepCount[j];
                    next=j;
                }
            }
            if (findKnightsTour(board,row+step[next][0],col+step[next][1],seq+1)){
                return true;
            }else{
                stepCount[next]=8;
            }
        }
        return false;
    }else{return false;}
}
