
#include "grid_utility.h"

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
		x = 0;
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

int check_end_conditions(int board[][4])
{
    int end_cond = 0, has_empty = 0, can_combine = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == WIN_VALUE)
				end_cond = 1;
			if (board[i][j] == 0)
				has_empty = 3;
			if ((j < 3 && board[i][j] == board[i][j + 1]) || (i < 3 && board[i][j] == board[i + 1][j])) {
				can_combine = 2;
			}
		}
	}
	if (end_cond) {
		return (1);
	}
	else if (has_empty || can_combine) {
		return (has_empty + can_combine);
	}
	return (-1);
}

void init_board(int board[][BOARD_SIZE]) 
{
    srand(time(NULL));
    
    t_vector sq1, sq2;
    sq2.x = 0, sq2.y =0;
    sq1.x = rand() % BOARD_SIZE;
    sq1.y = rand() % BOARD_SIZE;
    while (sq2.x == sq1.x)
        sq2.x = rand() % BOARD_SIZE;
    while (sq2.y == sq1.y)
        sq2.y = rand() % BOARD_SIZE;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((i == sq1.x && j == sq1.y) || (i == sq2.x && j == sq2.y))
                board[i][j] = rand() % 6 == 0 ? 4 : 2;
        }
    }
}

void spawn_new_tile(int board[][4]) 
{
	if (check_end_conditions(board) >= 3)
	{
		int x = rand() % BOARD_SIZE;
		int y = rand() % BOARD_SIZE;
		while (board[y][x] != 0)
		{
			x = rand() % BOARD_SIZE;
			y = rand() % BOARD_SIZE;
		}
		board[y][x] = 2;
	}
}