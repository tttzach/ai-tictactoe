#include <stdio.h>
#include <stdbool.h>

int human = -1;
int robot = 1;
int size = 9;

// full(board) determines if all spaces on the board
// are occupied and returns true, otherwise false
bool full(int board[9]) {
  for (int i = 0; i < size; i++) {
    if (board[i] == 0) { // if any of the spaces are empty, it is not full
      return false;
    }
  }
  return true;
}

// win(board, player) determines if the game is at terminal
// state in favor of the player specified
bool win(int board[9], int player) {
  if ((board[0] == player &&
       board[3] == player &&
       board[6] == player) ||
      (board[1] == player &&
       board[4] == player &&
       board[7] == player) ||
      (board[2] == player &&
       board[5] == player &&
       board[8] == player) ||
      (board[0] == player &&
       board[1] == player &&
       board[2] == player) ||
      (board[3] == player &&
       board[4] == player &&
       board[5] == player) ||
      (board[6] == player &&
       board[7] == player &&
       board[8] == player) ||
      (board[0] == player &&
       board[4] == player &&
       board[8] == player) ||
      (board[2] == player &&
       board[4] == player &&
       board[6] == player)) { // 8 possible win combinations
    return true;
  } else {
    return false;
  }
}

// score(board) determines the score of a particular state
int score(int board[9]) {
  if (win(board, robot)) {
    return 10;
  } else if (win(board, human)) {
    return -10;
  } else {
    return 0;
  }
}

// minimax(board, scoreboard, player) recursively updates
// scoreboard
// effects: mutates scoreboard
void minimax(int board[9], int scoreboard[9], int player) {
  int copyboard[9] = {0,1,2,3,4,5,6,7,8};
  for (int i = 0; i < size; i++) {
    copyboard[i] = board[i];
  }
  for (int i = 0; i < size; i++) {
    if (board[i] == 0) {
      copyboard[i] = player;
      scoreboard[i] = score(copyboard);
      copyboard[i] = 0;
    }
  }
}

// move(board, scoreboard) executes the move which is most 
// favorable for the robot
// effects: mutates board
//          mutates scoreboard
void move(int board[9], int scoreboard[9]) {
  int indsofar = -100;
  int maxsofar = -100;
  for (int i = 0; i < size; i++) {
    if (scoreboard[i] > maxsofar) {
      maxsofar = scoreboard[i];
      indsofar = i;
    }
  }
  board[indsofar] = robot;
  for (int i = 0; i < size; i++) {
    scoreboard[i] = 0;
  }
}

void print(int board[9]) {
  int column = 0;
  for (int i = 0; i < size; i++) {
    if (board[i] == human) {
      printf("\u25EF");
    } else if (board[i] == robot) {
      printf("\u2573");
    } else {
      printf("\u3000");
    }
    if (column == 2) {
      printf("\n");
      column = 0;
    } else {
      printf(" ");
      column++;
    }
  }
}

int main(void) {
  int ogboard[9] = {-1,0,1,1,0,0,1,-1,-1};
  int sboard[9] = {0};
  print(ogboard);
  minimax(ogboard, sboard, robot);
  move(ogboard, sboard);
  if (win(ogboard, human)) {
    printf("You win!\n");
  } else if (win(ogboard, robot)) {
    printf("You lose!\n");
  } else if (full(ogboard)) {
    printf("Tie!\n");
  } else {
    printf("Keep going!\n");
  }
}