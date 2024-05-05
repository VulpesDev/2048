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


void copy_board(int board[][BOARD_SIZE], int new_board[][BOARD_SIZE])
{
	int y = 0;
	int x = 0;
	while (y < BOARD_SIZE)
	{
		while (x < BOARD_SIZE)
		{
			new_board[y][x] = board[y][x];
			x++;
		}
		y++;
	}
}

int compare_board(int board[][BOARD_SIZE], int prev_board[][BOARD_SIZE])
{
	int y = 0;
	int x = 0;
	while (y < BOARD_SIZE)
	{
		while (x < BOARD_SIZE)
		{
			if (board[y][x] != prev_board[y][x])
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int main()
{
    int board[BOARD_SIZE][BOARD_SIZE] = {0};
	init_board(board);
	int prev_board[BOARD_SIZE][BOARD_SIZE] = {0};

	initscr();
    raw();
    noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	
	draw_board(board);

	int out = 0;
	while (1) {
		if ((out = game_status(board, out)) == 1)
			break;
		copy_board(board, prev_board);
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
			case 'q':
				endwin();
				return (0);
            default:
                break;
		}
		if (compare_board(board, prev_board))
			spawn_new_tile(board);
		draw_board(board);
	}
	getch();
	endwin();
	return (0);
}
