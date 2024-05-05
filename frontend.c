#include "frontend.h"

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

// Function to convert hex color to RGB
void hexToRGB(const char* hexColor, int* r, int* g, int* b) {
    *r = 0; *g = 0; *b = 0; 
    sscanf(hexColor, "#%02x%02x%02x", r, g, b);
}

void init_colors() {
    int r, g, b;
    hexToRGB("#cdc1b4", &r, &g, &b);
    init_color(COLOR_EMPTY, r*3, g*3, b*3);
    init_pair(COLOR_EMPTY, COLOR_EMPTY, COLOR_EMPTY);
    hexToRGB("#eee4da", &r, &g, &b);
    init_color(COLOR_TWO, r*3, g*3, b*3);
    init_pair(COLOR_TWO, COLOR_TWO, COLOR_TWO);
    hexToRGB("#ede0c8", &r, &g, &b);
    init_color(COLOR_FOUR, r*3, g*3, b*3);
    init_pair(COLOR_FOUR, COLOR_FOUR, COLOR_FOUR);
    hexToRGB("#f2b179", &r, &g, &b);
    init_color(COLOR_EIGHT, r*3, g*3, b*3);
    init_pair(COLOR_EIGHT, COLOR_EIGHT, COLOR_EIGHT);
    hexToRGB("#f59563", &r, &g, &b);
    init_color(COLOR_SIXTEEN, r*3, g*3, b*3);
    init_pair(COLOR_SIXTEEN, COLOR_SIXTEEN, COLOR_SIXTEEN);
    hexToRGB("#f67c5f", &r, &g, &b);
    init_color(COLOR_THIRTY2, r*3, g*3, b*3);
    init_pair(COLOR_THIRTY2, COLOR_THIRTY2, COLOR_THIRTY2);
    hexToRGB("#f65e3b", &r, &g, &b);
    init_color(COLOR_SIXTY4, r*3, g*3, b*3);
    init_pair(COLOR_SIXTY4, COLOR_SIXTY4, COLOR_SIXTY4);
    hexToRGB("#edcf72", &r, &g, &b);
    init_color(COLOR_ONE28, r*3, g*3, b*3);
    init_pair(COLOR_ONE28, COLOR_ONE28, COLOR_ONE28);
    hexToRGB("#edcc61", &r, &g, &b);
    init_color(COLOR_TWO56, r*3, g*3, b*3);
    init_pair(COLOR_TWO56, COLOR_TWO56, COLOR_TWO56);
    hexToRGB("#edc850", &r, &g, &b);
    init_color(COLOR_FIVE12, r*3, g*3, b*3);
    init_pair(COLOR_FIVE12, COLOR_FIVE12, COLOR_FIVE12);
    hexToRGB("#edc53f", &r, &g, &b);
    init_color(COLOR_TEN24, r*3, g*3, b*3);
    init_pair(COLOR_TEN24, COLOR_TEN24, COLOR_TEN24);
    hexToRGB("#edc22e", &r, &g, &b);
    init_color(COLOR_TWENTY48, r*3, g*3, b*3);
    init_pair(COLOR_TWENTY48, COLOR_TWENTY48, COLOR_TWENTY48);
}

char* print_ascii_digit(char array[][11], int num, int size) {
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

int digit_count(int n) {
    int result = 0;
    while (n != 0) {
        n /= 10;
        result++;
    }
    return result;
}

void activate_color(int number, int activate) {
    if (activate) {
        if (number == 0) {
            attron(COLOR_PAIR(COLOR_EMPTY));
        }
        else if (number == 2) {
            attron(COLOR_PAIR(COLOR_TWO));
        }
        else if (number == 4) {
            attron(COLOR_PAIR(COLOR_FOUR));
        }
        else if (number == 8) {
            attron(COLOR_PAIR(COLOR_EIGHT));
        }
        else if (number == 16) {
            attron(COLOR_PAIR(COLOR_SIXTEEN));
        }
        else if (number == 32) {
            attron(COLOR_PAIR(COLOR_THIRTY2));
        }
        else if (number == 64) {
            attron(COLOR_PAIR(COLOR_SIXTY4));
        }
        else if (number == 128) {
            attron(COLOR_PAIR(COLOR_ONE28));
        }
        else if (number == 256) {
            attron(COLOR_PAIR(COLOR_TWO56));
        }
        else if (number == 512) {
            attron(COLOR_PAIR(COLOR_FIVE12));
        }
        else if (number == 1024) {
            attron(COLOR_PAIR(COLOR_TEN24));
        }
        else if (number >= 2048) {
            attron(COLOR_PAIR(COLOR_TWENTY48));
        }
    }
    else {
        if (number == 0) {
            attroff(COLOR_PAIR(COLOR_EMPTY));
        }
        else if (number == 2) {
            attroff(COLOR_PAIR(COLOR_TWO));
        }
        else if (number == 4) {
            attroff(COLOR_PAIR(COLOR_FOUR));
        }
        else if (number == 8) {
            attroff(COLOR_PAIR(COLOR_EIGHT));
        }
        else if (number == 16) {
            attroff(COLOR_PAIR(COLOR_SIXTEEN));
        }
        else if (number == 32) {
            attroff(COLOR_PAIR(COLOR_THIRTY2));
        }
        else if (number == 64) {
            attroff(COLOR_PAIR(COLOR_SIXTY4));
        }
        else if (number == 128) {
            attroff(COLOR_PAIR(COLOR_ONE28));
        }
        else if (number == 256) {
            attroff(COLOR_PAIR(COLOR_TWO56));
        }
        else if (number == 512) {
            attroff(COLOR_PAIR(COLOR_FIVE12));
        }
        else if (number == 1024) {
            attroff(COLOR_PAIR(COLOR_TEN24));
        }
        else if (number >= 2048) {
            attroff(COLOR_PAIR(COLOR_TWENTY48));
        }
    }
}

void draw_board(int board[][BOARD_SIZE]) {
    int height, width;
    getmaxyx(stdscr, height, width);

    // Calculate the new size of each cell
    int cell_width = width / (BOARD_SIZE + 1);
    int cell_height = height / (BOARD_SIZE + 1);

    // Clear the current grid
    clear();

    activate_color(0, 1);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            mvaddch(y, x, ' '); // Fill screen with spaces
        }
    }
    activate_color(0, 0);

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
            
            activate_color(2, 1);
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
            activate_color(2, 0);

            // Draw the number in the cell
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
                                    for (size_t z = 0; z < strlen(ascii_art[(temp % 10) * size + k]); z++)
                                    {
                                        if (ascii_art[(temp % 10) * size + k][z] != ' ')
                                            activate_color(board[i][j], 1);
                                        else
                                            activate_color(0, 1);

                                        mvprintw(y + cell_height / 2 - size / 2 + y_offset ,
                                        z + x + x_offset-size/2 + cell_width/2 + (count*(size + 2))/2 - size/2,
                                            "%c", ascii_art[(temp % 10) * size + k][z]);
                                        if (ascii_art[(temp % 10) * size + k][z] != ' ')
                                            activate_color(board[i][j], 0);
                                        else
                                            activate_color(0, 0);
                                    }
                                }
                                y_offset += 1;
                        }
                        temp /= 10;
                        x_offset -= size + 2;
                    }
                }
            }
        }       
    }
    refresh();
}
