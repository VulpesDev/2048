#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 4
#define RIGHT_X 3
#define LEFT_X 0
#define UP_Y 0
#define DOWN_Y 3

#define UP_LIMIT 4
#define DOWN_LIMIT 0

#define RIGHT_LIMIT 0
#define LEFT_LIMIT 4

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
	if (dir == UP_Y && y_pos > 0 && board[--y_pos][x_pos] == found)
	{
		board[y_pos][x_pos] = 2 * found;
		board[y_pos + 1][x_pos] = 0;
		return (board);
	} 
	else if (dir == DOWN_Y && y_pos < 3 && board[++y_pos][x_pos] == found)
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
	if (dir == LEFT_X && x_pos > 0 && board[y_pos][--x_pos] == found)
	{
		board[y_pos][x_pos] = 2 * found;
		board[y_pos][x_pos+1] = 0;
		return (board);
	} 
	else if (dir == RIGHT_X && x_pos < 3 && board[y_pos][++x_pos] == found)
	{
		board[y_pos][x_pos] = 2 * found;
		board[y_pos][x_pos - 1] = 0;
		return (board);
	}
	return (board);
}


int search_tiles(int board[][4], int(*(*merge_tiles)(int[][4], int, int, int, int))[], int(*(*move_tiles)(int[][4], int, int))[] , int dir_x, int dir_y)
{
	clear();
	refresh();
	int x = dir_x;
	int y = dir_y;
	board = move_tiles(board, dir_x, dir_y);
	while ((!dir_x && x < 4) || (dir_x && x  >= 0))
	{
		y = 0;
		while ((!dir_y && y < 4) || (dir_y && y >= 0))
		{
			if (board[y][x])
			{
				board = merge_tiles(board, x, y, board[y][x], dir_y);
			}
			y += dir_y == 0? 1 : -1;
			// y++;
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


enum e_const
{
	WIN_VALUE = 2048
};

int check_end_conditions(int board[][4]) {
    int end_cond = 0, has_empty = 0, can_combine = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == WIN_VALUE)
				end_cond = 1;
			if (board[i][j] == 0)
				has_empty = 1;
			if ((j < 3 && board[i][j] == board[i][j + 1]) || (i < 3 && board[i][j] == board[i + 1][j])) {
				can_combine = 1;
			}
		}
	}
	if (end_cond) {
		return (1);
	}
	else if (has_empty || can_combine) {
		return (0);
	}
	return (-1);
}

typedef struct s_vector {
    int x;
    int y;
} t_vector;

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
	int x = rand() % BOARD_SIZE;
	int y = rand() % BOARD_SIZE;
	while (board[y][x] != 0)
	{
		x = rand() % BOARD_SIZE;
		y = rand() % BOARD_SIZE;
	}
	board[y][x] = 2;
}

int main()
{
    int board[BOARD_SIZE][BOARD_SIZE] = {{2, 0, 0, 2},
										{16, 0, 16, 2},
										{16, 8, 0, 2},
										{2, 2, 2, 2}};
	init_board(board);

	initscr();
    raw();
    noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	
	draw_board(board);

	int out = 0;
	while (1) {
		if (out)
			break;
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
				break;
		}

		int ch = getch();
        switch (ch) {
            case KEY_UP:
			printf("keyup\n");
                search_tiles(board, merge_up_down, move_up_down, 0, UP_Y);
                break;
            case KEY_DOWN:
				printf("key down");
                search_tiles(board, merge_up_down, move_up_down, 0, DOWN_Y);
                break;
            case KEY_LEFT:
                search_tiles(board, merge_left_right, move_left_right, LEFT_X, 0);
                break;
            case KEY_RIGHT:
                search_tiles(board, merge_left_right, move_left_right, RIGHT_X, 0);
                break;
			case 'q':
				endwin();
				return (0);
            default:
                break;
		}
		spawn_new_tile(board);
		draw_board(board);
	}
	getch();
	endwin();
	return (0);
}