

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 4

typedef struct s_vector {
    int x;
    int y;
} t_vector;

void init_board(int board[][BOARD_SIZE]) {
    srand(time(NULL));
    
    t_vector sq1, sq2;
    sq2.x = 0, sq2.y =0;
    sq1.x = rand() % BOARD_SIZE;
    sq1.y = rand() % BOARD_SIZE;
    while (sq2.x == sq1.x)
        sq2.x = rand() % BOARD_SIZE;
    while (sq2.y == sq1.y)
        sq2.y = rand() % BOARD_SIZE;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((i == sq1.x && j == sq1.y) || (i == sq2.x && j == sq2.y))
                board[i][j] = rand() % 6 == 0 ? 4 : 2;
        }
    }
}

void draw_board(int board[][BOARD_SIZE]) {
    clear();
    for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                mvprintw(i * 2 + 1, j * 6 + 1, "%d", board[i][j]);
            }
        }
    refresh();
}

int main() {
    initscr();
    raw();
    noecho();

    int board[BOARD_SIZE][BOARD_SIZE] = {0};

    while (1) {
        clear();
        init_board(board);
        draw_board(board);
        
        
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                // Move tiles up
                break;
            case KEY_DOWN:
                // Move tiles down
                break;
            case KEY_LEFT:
                // Move tiles left
                break;
            case KEY_RIGHT:
                // Move tiles right
                break;
            case 'q':
                endwin();
                return 0;
            default:
                break;
        }

        // Update game state
        // Check for game over condition
        // Add new tiles to the board

        refresh();
    }
    getch();
    endwin();
    return 0;
}
