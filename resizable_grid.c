#include <ncurses.h>
#include <unistd.h>

void draw_board() {
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
            if (i < 3 && j < 3){
                int number = i * 3 + j + 1; // Calculate the number (1 to 9)
                mvprintw(y + cell_height / 2, x + cell_width / 2 - 1, "%d", number);
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

    // Call draw_board periodically
    while(1) {
        draw_board();
        napms(100); // Wait for 100 milliseconds before checking again
        if (getch() == 'q') break;
    }

    endwin();
    return 0;
}
