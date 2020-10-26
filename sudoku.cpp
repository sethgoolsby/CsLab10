#include "sudoku.h"
#include <iostream>

using namespace std;

Sudoku::Sudoku(int puzzle[9][9]) {
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      board[i][j] = puzzle[i][j];
    }
  }
}

Sudoku::~Sudoku() {
}

bool Sudoku::verify() {
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      if(!isValid(i, j)) {
        cout << "INVALID PUZZLE at " <<i<<" , "<< j<< endl;
        return false;
      }
    }
  }
  cout << "VALID PUZZLE" << endl;
  return true;
}

void Sudoku::print() {
  for (int row=0; row<9; row++) {
      if (row % 3== 0) {
      std::cout << "-------------------------------" << std::endl;
    }
    
    for (int col=0; col<9; col++) {
      if (col % 3 == 0) {
        std::cout << "|";
      }
    
        if (board[row][col] != 0) {
        std::cout << " " << board[row][col] << " ";
      } else {
        std::cout << " . ";
      }
      
    }
    
    std::cout << "|" << std::endl;
  }
  std::cout << "-------------------------------" << std::endl;
}

bool Sudoku::isValid(int row, int col) {


  int value = board[row][col];

  for (int i=0; i<9; i++) {
    if (i == row) {
    continue;
    }
    
    int temp = board[i][col];
    if (temp == value) {
      return false;
    }
  }
  
  for (int i=0; i<9; i++) {
      if (i == col) {
      continue;
    }
    
    int temp = board[row][i];
    if (temp == value) {
      return false;
    }
  }
  
  int box_row = row / 3; 
  int box_col = col / 3; 
  
  for (int i=box_row * 3; i < box_row * 3 + 3; i++) {
    for (int j=box_col * 3; j < box_col * 3 + 3; j++) {
      if (i == row && j == col) {
        continue;
      }
      
      int temp = board[i][j];
      if (temp == value) {
        return false;
      }
    }
  }
  
  return true;
}

void Sudoku::solve(){
  solveHelper(0, 0);
}


bool Sudoku::solveHelper(int row, int col) {
  // TODO: IMPLEMENT THIS
  if(row > 8)
    {
      return true;
    }
  if(this->board[row][col] == 0)
  {
    int newcol = col + 1;
    int newrow = row;
    if(newcol > 8)
    {
      newcol = 0;
      newrow++;
    }
    bool flag = true;
    for(int x = 1; x <=9; x++) // for placement num = x
    {
      board[row][col] = x;
        if(isValid(row,col))
        {
            //print();
            //std::cout<<std::endl<<std::endl<<"Now Calling solveHelper on: Row = "<<newrow<<" And Column = "<<newcol<<std::endl;
            flag = solveHelper(newrow, newcol);
            if(flag)
            {
              return true;
            }
        }
        else //backtrack within the same loop
        {
          board[row][col] = 0;
        }
    }
    board[row][col] = 0;
    return false;
  //if we get to the end of the loop and the answer is still not complete
    //backtrack to the last level of itteration
      std::cout<<"I got lost on Row: "<<row<<"and on column: "<<col<<std::endl;
  }
  else // iterate to the next square
  {
    col++;
    if(col > 8)
    {
      col = 0;
      row++;
    }
      solveHelper(row, col);
  }
  
} 