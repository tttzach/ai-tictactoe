#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int human = -1;
int robot = 1;
int empty = 0;
int size = 9;

int max(a, b) {
  if (a > b) return a; else return b;
}

int min(a, b) {
  if (a < b) return a; else return b;
}

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

// minimax(board, scoreboard, player) recursively updates
// scoreboard
// effects: mutates scoreboard
int minimax(int board[9], int player) {
  // if human wins
  if (win(board, human)) {
    return -10;
  }
  // if robot wins
  if (win(board, robot)) {
    return 10;
  }
  // if no spaces left and no wins
  if (full(board)) {
    return 0;
  }
  // if player is robot, maximize score
  if (player == robot) {
    int bestscore = -100;
    // traverse through the board
    for (int i = 0; i < size; i++) {
      // if there is an empty space
      if (board[i] == empty) {
        // try the space
        board[i] = robot;
        // recursively determine score at current space and aim to maximize
        bestscore = max(bestscore, minimax(board, human));
        // reset the board
        board[i] = empty;
      }
    }
    return bestscore;
  } else { // if player is human, minimize score
    int  bestscore = 100;
    // traverse through the board
    for (int i = 0; i < size; i++) {
      // if there is an empty space
      if (board[i] == empty) {
        // try the space
        board[i] = human;
        // recursively determine score at current space and aim to minimize
        bestscore = min(bestscore, minimax(board, robot));
        // reset the board
        board[i] = empty;
      }
    }
    return bestscore;
  }
}

// move(board, scoreboard) executes the move which is most 
// favorable for the robot
// effects: mutates board
//          mutates scoreboard
void move(int board[9]) {
  int index = -100;
  int bestscore = -100;
  // check that board is not full
  if (!full(board)) {
    // traverse
    for (int i = 0; i < size; i++) {
      // if space is empty
      if (board[i] == empty) {
        // pretend robot is on this tile
        board[i] = robot;
        // determine score
        int score = minimax(board, human);
        // done pretending
        board[i] = empty;
        // update bestscore and index
        if (score > bestscore) {
          index = i;
          bestscore = score;
        }
      }
    }
    board[index] = robot;
  }
}

void print(int board[9]) {
  printf("\n\n\n\n\n\n                                  TIC TAC TOE\n\n\n");
  int column = 0;
  for (int i = 0; i < size; i++) {
    if (column == 0) {
      printf("                                     ");
    }
    if (board[i] == human) {
      //printf("\u25EF");
      printf("\x001b[1mO\x1B[0m");
    } else if (board[i] == robot) {
      //printf("\u2573");
      printf("\x001b[1mX\x1B[0m");
    } else {
      printf("\x001b[31m%d\x1B[0m", i + 1);
    }
    if (column == 2) {
      printf("\n");
      column = 0;
    } else {
      printf(" ");
      column++;
    }
  }
  printf("\n\n");
}

void update(int board[9]) {
  char c = getchar();
  getchar();
  int ind = c - '0';
  if (board[ind - 1] == empty) {
    board[ind - 1] = human;
  }
}

bool restart(void) {
  char c = getchar();
  getchar();
  if (c == 'Y' || c == 'y') {
    return true;
  } else {
    return false;
  }
}

void game(int board[9]) {
  while (1) {
    int count = 0;
    for (int i = 0; i < size; i++) {
      if (board[i] != 0) {
        count++;
      }
    }
    if (count < 8) {
      system("clear");
      print(board);
      printf("                         Type a number and press enter.\n                         If you try to overwrite a box,\n                         your chance will be passed on.\n\n\n");
      printf("                                       ");
      update(board);
      move(board);
    }
    system("clear");
    print(board);
    if (count == 8) {
      for (int i = 0; i < size; i++) {
        if (board[i] == 0) {
          board[i] = human;
          continue;
        }
      }
    }
    system("clear");
    print(board);
    if (win(board, human)) {
      printf("                                   You win!\n\n");
      printf("                         Would you like to replay? Y/N\n\n");
      if (restart()) {
        for (int i = 0; i < size; i++) {
          board[i] = 0;
        }
        continue;
      } else {
        system("clear");
        break;
      }
    } else if (win(board, robot)) {
      printf("                                    You lose!\n\n");
      printf("                          Would you like to replay? Y/N\n\n");
      if (restart()) {
        for (int i = 0; i < size; i++) {
          board[i] = 0;
        }
        continue;
      } else {
        system("clear");
        break;
      }
    } else if (full(board)) {
      printf("                                      Tie!\n\n");
      printf("                         Would you like to replay? Y/N\n\n");
      if (restart()) {
        for (int i = 0; i < size; i++) {
          board[i] = 0;
        }
        continue;
      } else {
        system("clear");
        break;
      }
    }
  }
}

int main(void) {
  int ogboard[9] = {0,0,0,0,0,0,0,0,0};
  game(ogboard);
  return 0;
}