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
#define L 1
#define D 0
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

int (*merge_up_down(int board[][4], int x_pos, int y_pos, int dir))[BOARD_SIZE]
{
	int op = (dir == U? 1 : -1);
	int x = 0;
	int y = (dir == U? 0 : 3);
	int found = 0;

	while (x < BOARD_SIZE)
	{
		y = (dir == U? 0 : 3);
		while (y < BOARD_SIZE && y >= DOWN_LIMIT)
		{
			if (board[y][x])
			{
				found = board[y][x];
				if (dir == U && y_pos > 0 && board[--y_pos][x_pos] == found)
				{
					board[y_pos][x_pos] = 2 * found;
					board[y_pos + 1][x_pos] = 0;
				}
				else if (dir == D && y_pos < 3 && board[++y_pos][x_pos] == found)
				{
					board[y_pos][x_pos] = 2 * found;
					board[y_pos - 1][x_pos] = 0;
				}
			}
			y += op;
		}
		x++;
	}
	return (board);	
}



// int (*merge_up_down(int board[][4], int x_pos, int y_pos, int found, int dir))[BOARD_SIZE]
// {
// 	if (dir == UP_Y && y_pos > 0 && board[--y_pos][x_pos] == found)
// 	{
// 		board[y_pos][x_pos] = 2 * found;
// 		board[y_pos + 1][x_pos] = 0;
// 		return (board);
// 	} 
// 	else if (dir == DOWN_Y && y_pos < 3 && board[++y_pos][x_pos] == found)
// 	{
// 		board[y_pos][x_pos] = 2 * found;
// 		board[y_pos - 1][x_pos] = 0;
// 		return (board);
// 	}
// 	return (board);
// }

// right merge doesnt work correctly

// int (*merge_left_right(int board[][4], int x_pos, int y_pos, int found, int dir))[BOARD_SIZE]
// {
// 	if (dir == LEFT_X && x_pos > 0 && board[y_pos][--x_pos] == found)
// 	{
// 		// printf("left\n\n");
// 		board[y_pos][x_pos] = 2 * found;
// 		board[y_pos][x_pos + 1] = 0;
// 		return (board);
// 	} 
// 	else if (dir == RIGHT_X && x_pos < 3 && board[y_pos][++x_pos] == found)
// 	{
// 		board[y_pos][x_pos] = 2 * found;
// 		board[y_pos][x_pos - 1] = 0;
// 		return (board);
// 	}
// 	return (board);
// }

int (*merge_left_right(int board[][4], int x_pos, int y_pos, int dir))[BOARD_SIZE]
{
	int op = (dir == L? 1 : -1);
	int x = (dir == L? 0 : 3);
	int y = 0;
	int found = 0;

	while (y < BOARD_SIZE)
	{
		x = (dir == L? 0 : 3);
		while (x < BOARD_SIZE && x >= RIGHT_LIMIT)
		{
			if (board[y][x])
			{
				found = board[y][x];
				if (dir == L && x_pos > 0 && board[y_pos][--x_pos] == found)
				{
					board[y_pos][x_pos] = 2 * found;
					board[y_pos][x_pos + 1] = 0;
				}
				else if (dir == R && x_pos < 3 && board[y_pos][++x_pos] == found)
				{	
					board[y_pos][x_pos] = 2 * found;
					board[y_pos][x_pos - 1] = 0;
				}
			}
			x += op;
		}
		y++;
	}
	return (board);
}


// int (*merge_down_right(int board[][4], int x_pos, int y_pos, int dir))[BOARD_SIZE]
// {
// 	int x = 3;
// 	int y = 3;
// 	int found = 0;

// 	while (x >= RIGHT_LIMIT)
// 	{
// 		y = 3;
// 		while (y >= DOWN_LIMIT)
// 		{
// 			if (board[y][x])
// 			{
// 				found = board[y][x];
// 				if (dir == D && y_pos < 3 && board[++y_pos][x_pos] == found)
// 				{
// 					// printf("down\n\n");
// 					board[y_pos][x_pos] = 2 * found;
// 					board[y_pos - 1][x_pos] = 0;
// 					// return (board);
// 				}
// 				else if (dir == R && x_pos < 3 && board[y_pos][++x_pos] == found)
// 				{	
// 					// printf("right\n\n");
// 					board[y_pos][x_pos] = 2 * found;
// 					board[y_pos][x_pos - 1] = 0;
// 					// return (board);
// 				}
// 			}
// 			y--;
// 		}
// 		x--;
// 	}
// 	return (board);
// }


// int (*merge_up_left(int board[][4], int x_pos, int y_pos, int dir))[BOARD_SIZE]
// {
// 	int x = 0;
// 	int y = 0;
// 	int found = 0;

// 	while (x < BOARD_SIZE)
// 	{
// 		y = 0;
// 		while (y < BOARD_SIZE)
// 		{
// 			if (board[y][x])
// 			{
// 				found = board[y][x];
// 				if (dir == U && y_pos > 0 && board[--y_pos][x_pos] == found)
// 				{
// 					printf("up\n\n");
// 					board[y_pos][x_pos] = 2 * found;
// 					board[y_pos + 1][x_pos] = 0;
// 					// return (board);
// 				}
// 				else if (dir == L && x_pos > 0 && board[y_pos][--x_pos] == found)
// 				{
// 					printf("left\n\n");
// 					board[y_pos][x_pos] = 2 * found;
// 					board[y_pos][x_pos + 1] = 0;
// 					// return (board);
// 				} 
// 			}
// 			y++;
// 		}
// 		x++;
// 	}
// 	return (board);
// }

int search_tiles(int board[][4], int(*(*merge_tiles)(int[][4], int, int, int))[], int(*(*move_tiles)(int[][4], int, int))[] , int dir_x, int dir_y, int cur_move)
{
	clear();
	refresh();
	int x = 0;
	int y = 0;
	board = move_tiles(board, dir_x, dir_y);
	board = merge_tiles(board, x, y, cur_move);
	// (void)merge_tiles(board, x, y, cur_move);


	// while (x < 4)
	// {
	// 	y = 0;
	// 	while (y < 4)
	// 	{
	// 		if (board[y][x])
	// 		{
	// 			board = merge_tiles(board, x, y, board[y][x], dir_y);
	// 		}
	// 		y++;
	// 	}
	// 	x++;
	// }
	board = move_tiles(board, dir_x, dir_y);
	draw_board(board);

	return(0);

}


int main()
{
    int board[][4] = {  {2, 2, 2, 2},
						{0, 0, 0, 2},
						{0, 0, 0, 2},
						{2, 0, 0, 4}};

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