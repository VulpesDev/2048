#include <ncurses.h>
#include <stdio.h>
#define COLOR_TWO 8
#define COLOR_FOUR 9
#define COLOR_EIGHT 10
#define COLOR_SIXTEEN 11
#define COLOR_THIRTY2 12
#define COLOR_SIXTY4 13
#define COLOR_ONE28 14
#define COLOR_TWO56 15
#define COLOR_FIVE12 16
#define COLOR_TEN24 17
#define COLOR_TWENTY48 18
#define COLOR_EMPTY 19

// Function to convert hex color to RGB
void hexToRGB(const char* hexColor, int* r, int* g, int* b) {
    *r = 0; *g = 0; *b = 0; 
    sscanf(hexColor, "#%02x%02x%02x", r, g, b);
}

void init_colors() {
    int r, g, b;
    hexToRGB("#cdc1b4", &r, &g, &b);
    init_color(COLOR_EMPTY, r*3*3, g*3*3, b*3*3);
    init_pair(COLOR_EMPTY, COLOR_EMPTY, COLOR_EMPTY);
    hexToRGB("#eee4da", &r, &g, &b);
    init_color(COLOR_TWO, r*3*3, g*3*3, b*3*3);
    init_pair(COLOR_TWO, COLOR_TWO, COLOR_EMPTY);
    hexToRGB("#ede0c8", &r, &g, &b);
    init_color(COLOR_FOUR, r*3*3, g*3*3, b*3*3);
    init_pair(COLOR_FOUR, COLOR_FOUR, COLOR_EMPTY);
    hexToRGB("#f2b179", &r, &g, &b);
    init_color(COLOR_EIGHT, r*3, g*3, b*3);
    init_pair(COLOR_EIGHT, COLOR_EIGHT, COLOR_EMPTY);
    hexToRGB("#f59563", &r, &g, &b);
    init_color(COLOR_SIXTEEN, r*3, g*3, b*3);
    init_pair(COLOR_SIXTEEN, COLOR_SIXTEEN, COLOR_EMPTY);
    hexToRGB("#f67c5f", &r, &g, &b);
    init_color(COLOR_THIRTY2, r*3, g*3, b*3);
    init_pair(COLOR_THIRTY2, COLOR_THIRTY2, COLOR_EMPTY);
    hexToRGB("#f65e3b", &r, &g, &b);
    init_color(COLOR_SIXTY4, r*3, g*3, b*3);
    init_pair(COLOR_SIXTY4, COLOR_SIXTY4, COLOR_EMPTY);
    hexToRGB("#edcf72", &r, &g, &b);
    init_color(COLOR_ONE28, r*3, g*3, b*3);
    init_pair(COLOR_ONE28, COLOR_ONE28, COLOR_EMPTY);
    hexToRGB("#edcc61", &r, &g, &b);
    init_color(COLOR_TWO56, r*3, g*3, b*3);
    init_pair(COLOR_TWO56, COLOR_TWO56, COLOR_EMPTY);
    hexToRGB("#edc850", &r, &g, &b);
    init_color(COLOR_FIVE12, r*3, g*3, b*3);
    init_pair(COLOR_FIVE12, COLOR_FIVE12, COLOR_EMPTY);
    hexToRGB("#edc53f", &r, &g, &b);
    init_color(COLOR_TEN24, r*3, g*3, b*3);
    init_pair(COLOR_TEN24, COLOR_TEN24, COLOR_EMPTY);
    hexToRGB("#edc22e", &r, &g, &b);
    init_color(COLOR_TWENTY48, r*3, g*3, b*3);
    init_pair(COLOR_TWENTY48, COLOR_TWENTY48, COLOR_EMPTY);
}


int main() {
    initscr();
    start_color();
    init_colors();


    init_pair(1, COLOR_WHITE, COLOR_WHITE); // Background color pair
    // Get screen dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Set background color for entire screen
    attron(COLOR_PAIR(1));
    for (int y = 0; y < max_y; ++y) {
        for (int x = 0; x < max_x; ++x) {
            mvaddch(y, x, ' '); // Fill screen with spaces
        }
    }
    attroff(COLOR_PAIR(1));
    refresh();

    attron(COLOR_PAIR(COLOR_SIXTEEN));
    mvprintw(max_y / 2, max_x / 2, "Custom Color");
    attroff(COLOR_PAIR(COLOR_SIXTEEN));
    refresh();

    getch();
    endwin();

    return 0;
}
