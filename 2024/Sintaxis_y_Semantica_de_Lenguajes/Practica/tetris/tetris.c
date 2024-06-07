/*
#include <stdio.h>

int main(void) {
  char kb_input = '\0';
  kb_input = getchar();
  while (kb_input != 'q') {
    printf("Keypress!\n");
    kb_input = getchar();
  }
  return 0;
}
*/
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

enum keypress { LEFT, RIGHT, SDROP, HDROP, RL, RR, F, H, Q, N };

enum keypress getKey(uint8_t buf[]) {
  if (buf[0] == 27 && buf[1] == 91) {
    switch (buf[2]) {
    case 68:
      return LEFT;

    case 67:
      return RIGHT;

    case 66:
      return SDROP;
    }
  }
  switch (buf[0]) {
  case 113:
    return Q;
  case 100:
    return RR;
  case 115:
    return F;
  case 119:
    return H;
  case 97:
    return RL;
  case 32:
    return HDROP;
  }

  return N;
}

void initBoard(char board[][10]) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      board[i][j] = ' ';
    }
  }
}

void clearScreen() {
  for (int i = 0; i < 50; i++) {
    printf("\n");
  }
}

void showScreen(char board[][10], float time) {
  clearScreen();
  printf(" ----------- \n");
  for (int i = 0; i < 20; i++) {
    printf("| ");
    for (int j = 0; j < 10; j++) {
      printf("%c", board[i][j]);
    }
    printf(" |");
    printf("\n");
  }
  printf(" ----------- \n");
  printf("%f\n", time);
}

void changePos(int *pY, int *pX, int kPress) {
  printf(" - %d -", kPress);
  switch (kPress) {
  case 0:
    *pX = 4;
  case 1:
    *pX = 5;
  }
  *pY = *pY + 1;
}

int main(int argc, char **argv) {
  struct termios attr;
  tcgetattr(STDIN_FILENO, &attr);
  attr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &attr);
  uint8_t buf[20];
  ssize_t bytes;

  const int boardW = 10;
  const int boardH = 20;

  char board[boardH + 1][boardW + 1];
  float time = 0;
  int framerate = 10;
  int posX = 0;
  int posY = 0;

  initBoard(board);

  enum keypress key;
  bytes = read(STDIN_FILENO, buf, 20);
  key = getKey(buf);

  while (key != Q) {
    bytes = read(STDIN_FILENO, buf, 20);
    key = getKey(buf);

    // TODO: PROCESS KEY INPUT INTO MOVEMENT
    board[posY][posX] = ' ';
    changePos(&posY, &posX, key);
    board[posY][posX] = 'O';
    // fflush(stdout);
    showScreen(board, time);
    time += 1.0 / framerate;
    usleep(1000 / framerate * 1000);
    /* Show key pressed

    for (size_t i = 0; i < bytes; i++) {
      printf("%zd: %hhu\n", i, buf[i]);
    }

    printf("%d\n\n", key

    */
  }
  return 0;
}
