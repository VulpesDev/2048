#include <ncurses.h>
#include <unistd.h>

void resize_grid() {
    int height, width;
    getmaxyx(stdscr, height, width);

    // Calculate the new size of each cell
    int cell_width = width / 4;
    int cell_height = height / 4;

    // Clear the current grid
    clear();

    // Draw the new grid
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            // Calculate the position of each cell
            int x =  cell_width/2 + j * cell_width;
            int y = cell_height/2 + i * cell_height;
            // Draw the cell
            mvaddch(y, x, '#');
        }
    }

    // Refresh the screen to show the updated grid
    refresh();
}


int main() {
    // Initialize ncurses
    initscr(); // Initialize the window
    raw(); // Line buffering disabled
    noecho(); // Don't echo() while we do getch
    keypad(stdscr, TRUE); // Enable special keys
    curs_set(FALSE); // Don't display cursor

    // Your grid creation and manipulation code goes here
    // Inside your main function, after initializing ncurses

    // Clear the screen

    // Create a 4x4 grid
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            mvaddch(i, j, '#'); // Move to position (i, j) and print '#'
        }
    }

    // Refresh the screen to show the grid
    // Call resize_grid periodically
    while(1) {
        resize_grid();
        napms(100); // Wait for 100 milliseconds before checking again
    }

    endwin();
    return 0;
}
