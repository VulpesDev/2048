#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 4

#include <stdio.h>

// char ascii_art[][11] = {
//     " ██████ ",
//     "██    ██",
//     "██    ██",
//     "██    ██",
//     " ██████ ",

//     "    ██",
//     "   ███",
//     "    ██",
//     "    ██",
//     "    ██",
    
//     "██████ ",
//     "     ██",
//     " █████ ",
//     "██     ",
//     "███████",

//     "██████ ",
//     "     ██",
//     "█████ ",
//     "     ██",
//     "██████ ",

//     "██   ██",
//     "██   ██",
//     "███████",
//     "     ██",
//     "     ██",

//     "███████",
//     "██     ",
//     "███████",
//     "     ██",
//     "███████",

//     " ██████",
//     "██     ",
//     "███████ ",
//     "██    ██",
//     " ██████ ",

//     "███████",
//     "     ██",
//     "    ██ ",
//     "   ██  ",
//     "   ██  ",

//     " █████ ",
//     "██   ██",
//     " █████ ",
//     "██   ██",
//     " █████ ",

//     " █████ ",
//     "██   ██",
//     " █████ ",
//     "    ██ ",
//     " █████ "

// };



char ascii_art[][11] = {
    " 0000",
    "00  00",
    "00  00",
    "00  00",
    " 0000",

    "1111",
    "  11",
    "  11",
    "  11",
    "111111",

    " 2222",
    "22  22",
    "   22",
    "  22",
    "222222",

    " 3333",
    "33  33",
    "   333",
    "33  33",
    " 3333",

    "44  44",
    "44  44",
    "444444",
    "    44",
    "    44",

    "555555",
    "55",
    "55555",
    "    55",
    "55555",

    " 6666",
    "66",
    "66666",
    "66  66",
    " 6666",

    "777777",
    "   77",
    "  77",
    " 77",
    "77",

    " 8888",
    "88  88",
    " 8888",
    "88  88",
    " 8888",

    " 9999",
    "99  99",
    " 99999",
    "    99",
    " 9999",

    ""
};


                                                                           

#include <string.h>
#include <stdlib.h>
char* print_ascii_digit(char array[][11], int num, int size, int cell_width, int cell_height) {
    char *result = calloc(1, sizeof(char) * size*size*2);
    if (result == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        strcat(result, array[num * size + i]);
        strcat(result, "\n");
    }
    return result;
}

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

    // for (int i = 0; i < BOARD_SIZE; i++) {
    //     for (int j = 0; j < BOARD_SIZE; j++) {
    //         if ((i == sq1.x && j == sq1.y) || (i == sq2.x && j == sq2.y))
    //             board[i][j] = rand() % 6 == 0 ? 4 : 2;
    //     }
    // }
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

int digit_count(int n) {
    int result = 0;
    while (n != 0) {
        n /= 10;
        result++;
    }
    return result;
}

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
                int size = 5;
                int temp = board[i][j];
                int y_offset = 0, x_offset = 0;
                int count = digit_count(temp);
                if (count*(size + 2) > cell_width || size > cell_height) {
                    mvprintw(y + cell_height / 2 + y_offset , x + x_offset + cell_width/2, "%d", board[i][j]);
                }
                else {
                    while (temp != 0) {
                        y_offset = 0;
                        for (int k = 0; k < size; k++) {
                                if (board[i][j] != 0){
                                    mvprintw(y + cell_height / 2 - size / 2 + y_offset , x + x_offset-size/2 + cell_width/2 + (count*(size + 2))/2 - size/2, "%s", ascii_art[(temp % 10) * size + k]);
                                }
                                y_offset += 1;
                        }
                        temp /= 10;
                        x_offset -= size + 2;
                    }
                }
            }
        }       
                //increase y value
    }
    // Refresh the screen to show the updated grid
    refresh();
}

int main() {
    initscr();
    raw();
    noecho();

    int board[BOARD_SIZE][BOARD_SIZE] = {10, 10, 10, 100, 32, 64, 128, 256, 512, 1024, 2048, 65536, 8192, 16384, 32768, 4096};
    //  int board[BOARD_SIZE][BOARD_SIZE] = {2048};
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
