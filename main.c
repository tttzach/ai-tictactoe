#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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
      copyboard[i] = board[i];
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
  printf("Scoreboard\n");
  for (int i = 0; i < size; i++) {
    printf("%d ", scoreboard[i]);
  }
  for (int i = 0; i < size; i++) {
    if (scoreboard[i] > maxsofar) {
      maxsofar = scoreboard[i];
      indsofar = i;
    }
  }
  printf("indsofar is: %d\n", indsofar);
  board[indsofar] = robot;
  for (int i = 0; i < size; i++) {
    scoreboard[i] = -100;
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
      printf("%d", i + 1);
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

void update(int board[9]) {
  char c = getchar();
  getchar();
  //int scan = scanf(" %c", &c);
  int ind = c - '0';
  if (board[ind - 1] == 0) {
    board[ind - 1] = human;
  } else {
    printf("Invalid move! You lose your turn!\n");
  }
}

int loop(int board[9], int scoreboard[9]) {
  //system("clear");
  print(board);
  printf("Type a number and press enter\n");
  printf("Before update\n");
  for (int i = 0; i < size; i++) {
    printf("%d ", board[i]);
  }
  printf("\n");
  update(board);
  minimax(board, scoreboard, robot);
  printf("Before move\n");
  for (int i = 0; i < size; i++) {
    printf("%d ", board[i]);
  }
  move(board, scoreboard);
  printf("After move\n");
  for (int i = 0; i < size; i++) {
    printf("%d ", board[i]);
  }
  printf("\n");
  //system("clear");
  print(board);
  if (win(board, human)) {
    printf("You win!\n");
    return 0;
  } else if (win(board, robot)) {
    printf("You lose!\n");
    return 0;
  } else if (full(board)) {
    printf("Tie!\n");
    return 0;
  } else {
    printf("Keep going!\n");
    loop(board, scoreboard);
    return 0;
  }
}

int main(void) {
  int ogboard[9] = {1,0,0,0,-1,0,0,0,0};
  int sboard[9] = {-100,-100,-100,-100,-100,-100,-100,-100,-100};
  loop(ogboard, sboard);
}