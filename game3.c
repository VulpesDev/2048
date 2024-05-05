#include <stdio.h>
#include <ncurses.h>

#define BOARD_SIZE 4
#define RIGHT_X 3
#define LEFT_X 0
#define UP_Y 0
#define DOWN_Y 3

#define UP_LIMIT 4
#define DOWN_LIMIT 0

#define RIGHT_LIMIT 0
#define LEFT_LIMIT 4

#define U 0
#define D 1
#define L 0
#define R 1

void draw_board(int board[][BOARD_SIZE]) 
{
	// clear();
	// int x = 0, y = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                mvprintw(i * 2 + 1, j * 6 + 1, "%d", board[i][j]);
            }
        }
}

int (*move_left_right(int board[][4], int x, int y))[BOARD_SIZE]
{
	int i = 1;
	int op = (x == LEFT_X ? 1 : -1);
	int x_start = x;

	while (y < BOARD_SIZE)
	{
		x = x_start;
		while (x < BOARD_SIZE && x >= RIGHT_LIMIT)
		{
			if (!board[y][x])
			{
				i = 1;
				while ((x + i * op < BOARD_SIZE && x + i * op >= RIGHT_LIMIT) && !board[y][x + i * op])
					i++;
				if ((x + i * op < BOARD_SIZE) && (x + i * op >= RIGHT_LIMIT) && board[y][x + i * op])
				{
					board[y][x] = board[y][x + i * op];
					board[y][x + i * op] = 0;
				}
			}
			x += op;			
		}
		y++;
	}
	return (board);
}

int (*move_up_down(int board[][4], int x, int y))[BOARD_SIZE]
{
	int i = 1;
	int op = (y == UP_Y? 1 : -1);
	int y_start = y;

	while (x < BOARD_SIZE)
	{
		y = y_start;
		while (y < BOARD_SIZE && y >= DOWN_LIMIT)
		{
			if (!board[y][x])
			{
				i = 1;
				while ((y + i*op < BOARD_SIZE && y + i * op >= DOWN_LIMIT) && !board[y + (i * op)][x])
					i++;
				if ((y + i * op < BOARD_SIZE) && (y + i * op >= DOWN_LIMIT) && board[y + (i * op)][x])
				{
					board[y][x] = board[y + (i * op)][x];
					board[y + (i * op)][x] = 0;
				}				
			}
			y += op;
		}
		x++;
	}
	return (board);
}

int (*merge_up_down(int board[][4], int x_pos, int y_pos, int found, int dir))[BOARD_SIZE]
{
	if (dir == U && y_pos > 0 && board[--y_pos][x_pos] == found)
	{
		board[y_pos][x_pos] = 2 * found;
		board[y_pos + 1][x_pos] = 0;
		return (board);
	} 
	else if (dir == D && y_pos < 3 && board[++y_pos][x_pos] == found)
	{
		board[y_pos][x_pos] = 2 * found;
		board[y_pos - 1][x_pos] = 0;
		return (board);
	}
	return (board);
}

// right merge doesnt work correctly

int (*merge_left_right(int board[][4], int x_pos, int y_pos, int found, int dir))[BOARD_SIZE]
{
	if (dir == L && x_pos > 0 && board[y_pos][--x_pos] == found)
	{
		board[y_pos][x_pos] = 2 * found;
		board[y_pos][x_pos+1] = 0;
		return (board);
	} 
	else if (dir == R && x_pos < 3 && board[y_pos][++x_pos] == found)
	{
		board[y_pos][x_pos] = 2 * found;
		board[y_pos][x_pos - 1] = 0;
		return (board);
	}
	return (board);
}


int search_tiles(int board[][4], int(*(*merge_tiles)(int[][4], int, int, int, int))[], int(*(*move_tiles)(int[][4], int, int))[] , int dir_x, int dir_y, int cur_move)
{
	clear();
	refresh();
	int x = dir_x;
	int y = dir_y;
	board = move_tiles(board, dir_x, dir_y);
	while ((!dir_x && x < 4) || (dir_x && x  >= 0))
	{
		y = dir_y == 0? 0 : 3;
		while ((!dir_y && y < 4) || (dir_y && y >= 0))
		{
			if (board[y][x])
			{
				board = merge_tiles(board, x, y, board[y][x], cur_move);
			}
			y += dir_y == 0? 1 : -1;
		}
		x += dir_x == 0 ? 1 : -1;
	}
	board = move_tiles(board, dir_x, dir_y);
	draw_board(board);

	return(0);

}

// {  {2, 2, 2, 2},
						// {0, 0, 0, 16},
						// {0, 8, 0, 16},
						// {2, 0, 0, 2}};


int main()
{
    int board[][4] = {  {2, 2, 2, 2},
						{0, 0, 16, 16},
						{0, 8, 0, 16},
						{2, 2, 2, 2}};

	initscr();
    raw();
    noecho();
	curs_set(0);
	keypad(stdscr, TRUE);

	draw_board(board);
	while (1) {
		int ch = getch();
        switch (ch) {
            case KEY_UP:
			printf("keyup\n");
                search_tiles(board, merge_up_down, move_up_down, 0, UP_Y, U);
                break;
            case KEY_DOWN:
				printf("key down");
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
	}
	endwin();
	return (0);
}