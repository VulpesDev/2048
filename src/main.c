#include "algorithm.h"
#include "frontend.h"
#include "grid_utility.h"
#include <ncurses.h>

int game_status(int board[][BOARD_SIZE], int out)
{
	switch (check_end_conditions(board)) {
		case 0:
			break;
		case 1:
			mvprintw(10, 10, "%s", "YOU WIN");
			refresh();
			break;
		case -1:
			mvprintw(10, 10, "%s", "YOU LOSE");
			refresh();
			out = 1;
			return (out);
			break;
	}
	return (0);
}

int main() {
    int board[BOARD_SIZE][BOARD_SIZE] = {0};
	init_board(board);

	initscr();
    raw();
    noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	start_color();
    init_colors();
	
	draw_board(board);

    while (1) {
        clear();
        draw_board(board);
        napms(100);
        
		if (game_status(board, 0))
			break;
		
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                search_tiles(board, merge_up_down, move_up_down, 0, UP_Y, U);
                break;
            case KEY_DOWN:
                search_tiles(board, merge_up_down, move_up_down, 0, DOWN_Y, D);
                break;
            case KEY_LEFT:
                search_tiles(board, merge_left_right, move_left_right, LEFT_X, 0, L);
                break;
            case KEY_RIGHT:
                search_tiles(board, merge_left_right, move_left_right, RIGHT_X, 0, R);
                break;
			case 27:
				endwin();
				return (0);
            default:
                break;
		}
        refresh();
    }
    while (getch() != 27)
    {;}
    endwin();
    return 0;
}
