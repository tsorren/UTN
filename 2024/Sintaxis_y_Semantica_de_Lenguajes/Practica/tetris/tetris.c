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

#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define COLOR_RED "\x1B[31m"
#define COLOR_GRN "\x1B[32m"
#define COLOR_YEL "\x1B[33m"
#define COLOR_BLU "\x1B[34m"
#define COLOR_MAG "\x1B[35m"
#define COLOR_CYN "\x1B[36m"
#define COLOR_WHT "\x1B[37m"
#define COLOR_RESET "\x1B[0m"

enum keypress
{
    LEFT,
    RIGHT,
    SDROP,
    HDROP,
    RL,
    RR,
    F,
    H,
    Q,
    N
};

enum keypress getKey(uint8_t buf[])
{
    if (buf[0] == 27 && buf[1] == 91)
    {
        switch (buf[2])
        {
        case 68:
            return LEFT;

        case 67:
            return RIGHT;

        case 66:
            return SDROP;
        }
    }
    switch (buf[0])
    {
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

void wait()
{
    int framerate = 10;
    usleep(1000 / framerate * 1000);
    return;
}


void *readInputFunction(void *vargp)
{
    enum keypress *key = (enum keypress*)vargp;

    uint8_t buf[20];
    ssize_t bytes;
    bytes = read(STDIN_FILENO, buf, 20);
    *key = getKey(buf);
    
    while(*key != Q)
    {
        wait();
        bytes = read(STDIN_FILENO, buf, 20);
        *key = getKey(buf);
    }

    return NULL;
}

void initBoard(int board[][10])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            board[i][j] = 0;
        }
    }
}

void clearScreen()
{
    for (int i = 0; i < 50; i++)
    {
        printf("\n");
    }
}

void showScreen(char board[][10], float time)
{
    clearScreen();
    printf(" ----------- \n");
    for (int i = 0; i < 20; i++)
    {
        printf("| ");
        for (int j = 0; j < 10; j++)
        {
            printf("%c", board[i][j]);
        }
        printf(" |");
        printf("\n");
    }
    printf(" ----------- \n");
    printf("%f\n", time);
}

void showPiece(char piece)
{
    switch (piece)
    {
        case 'I':
            printf(COLOR_CYN "%c" COLOR_RESET, piece);
            break;

        case 'O':
            printf(COLOR_YEL "%c" COLOR_RESET, piece);
            break;

        case 'L':
            printf(COLOR_WHT "%c" COLOR_RESET, piece);
            break;
            
        case 'J':
            printf(COLOR_BLU "%c" COLOR_RESET, piece);
            break;
            
        case 'S':
            printf(COLOR_GRN "%c" COLOR_RESET, piece);
            break;
            
        case 'Z':
            printf(COLOR_RED "%c" COLOR_RESET, piece);
            break;
        
        case 'T':
            printf(COLOR_MAG "%c" COLOR_RESET, piece);
            break;
            
    }
}

void changePos(int *pY, int *pX, int kPress)
{
    printf(" - %d -", kPress);
    switch (kPress)
    {
    case 0:
        *pX = 4;
    case 1:
        *pX = 5;
    }
    *pY = *pY + 1;
}

void setupConsole()
{
    struct termios attr;
    tcgetattr(STDIN_FILENO, &attr);
    attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

int main(int argc, char **argv)
{
    setupConsole();

    const int boardW = 10;
    const int boardH = 20;

    char bag[7] = {'I', 'O', 'L', 'J', 'S', 'Z', 'T'};

    int board[boardH + 1][boardW + 1];
    float time = 0;
    int posX = 0;
    int posY = 0;

    initBoard(board);

    enum keypress key;

    pthread_t input_thread;
    pthread_create(&input_thread, NULL, readInputFunction, &key);

    while (key != Q)
    {
        // TODO: PROCESS KEY INPUT INTO MOVEMENT
        // board[posY][posX] = 0;
        // changePos(&posY, &posX, key);
        // board[posY][posX] = 1;

        // fflush(stdout);
        // showScreen(board, time);

        printf("%d\n", key);
        showPiece(bag[key]);
        printf("\n");
        wait();
        /* Show key pressed

        for (size_t i = 0; i < bytes; i++) {
            printf("%zd: %hhu\n", i, buf[i]);
        }

        printf("%d\n\n", key

        */
    }
    pthread_join(input_thread, NULL);;
    return 0;
}
