#include "algorithm.h"
#include "grid_utility.h"


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
	spawn_new_tile(board);
	return(0);

}
