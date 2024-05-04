#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 10

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

// void draw_board(int board[][BOARD_SIZE]) {
//     clear();
//     for (int i = 0; i < BOARD_SIZE; i++) {
//             for (int j = 0; j < BOARD_SIZE; j++) {
//                 mvprintw(i * 2 + 1, j * 6 + 1, "%d", board[i][j]);
//             }
//         }
//     refresh();
// }

void draw_board(int board[][BOARD_SIZE]) {
    int height, width;
    getmaxyx(stdscr, height, width);

    // Calculate the new size of each cell
    int cell_width = width / (BOARD_SIZE + 1);
    int cell_height = height / (BOARD_SIZE + 1);

    // Clear the current grid
    clear();

    if (height < BOARD_SIZE*2 + 2) {
        mvprintw(0 , 0, "smoll");
        refresh();
        return;
    }

    // Draw the new grid
    for (int i = 0; i <= BOARD_SIZE; ++i) {
        for (int j = 0; j <= BOARD_SIZE; ++j) {
            // Calculate the position of each cell
            int x = cell_width / 2 + j * cell_width;
            int y = cell_height / 2 + i * cell_height;

            // Draw the cell
            mvaddch(y, x, '#');

            // Draw horizontal line to the right
            if (j < BOARD_SIZE) {
                int next_x = cell_width / 2 + (j + 1) * cell_width;
                mvhline(y, x + 1, '-', next_x - x - 1);
            }

            // Draw vertical line downwards
            if (i < BOARD_SIZE) {
                int next_y = cell_height / 2 + (i + 1) * cell_height;
                mvvline(y + 1, x, '|', next_y - y - 1);
            }
            if (i < BOARD_SIZE && j < BOARD_SIZE){
                int number = i * BOARD_SIZE + j + 1; // Calculate the number (1 to 9)
                mvprintw(y + cell_height / 2, x + cell_width / 2 - 1, "%d", board[i][j]);
            }
        }
    }
    // Refresh the screen to show the updated grid
    refresh();
}

int main() {
    initscr();
    raw();
    noecho();

    int board[BOARD_SIZE][BOARD_SIZE] = {0};
    init_board(board);

    while (1) {
        clear();
        draw_board(board);
        napms(100);
        
        
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
        refresh();
    }
    getch();
    endwin();
    return 0;
}
