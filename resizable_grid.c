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

    if (height < 10) {
        mvprintw(0 , 0, "smoll");
        refresh();
        return;
    }

    // Draw the new grid
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // Calculate the position of each cell
            int x = cell_width / 2 + j * cell_width;
            int y = cell_height / 2 + i * cell_height;

            // Draw the cell
            mvaddch(y, x, '#');

            // Draw horizontal line to the right
            if (j < 3) {
                int next_x = cell_width / 2 + (j + 1) * cell_width;
                mvhline(y, x + 1, '-', next_x - x - 1);
            }

            // Draw vertical line downwards
            if (i < 3) {
                int next_y = cell_height / 2 + (i + 1) * cell_height;
                mvvline(y + 1, x, '|', next_y - y - 1);
            }
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

    // Call resize_grid periodically
    while(1) {
        resize_grid();
        napms(100); // Wait for 100 milliseconds before checking again
        if (getch() == 'q') break;
    }

    endwin();
    return 0;
}
