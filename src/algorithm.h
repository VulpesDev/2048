#ifndef ALGORITHM_H
# define ALGORITHM_H
# include <stdio.h>
# include <ncurses.h>
# include <stdlib.h>
# include <time.h>
# include "frontend.h"

# define BOARD_SIZE 4
# define RIGHT_X 3
# define LEFT_X 0
# define UP_Y 0
# define DOWN_Y 3

# define UP_LIMIT 4
# define DOWN_LIMIT 0

# define RIGHT_LIMIT 0
# define LEFT_LIMIT 4

# define U 0
# define D 1
# define L 0
# define R 1

enum e_const
{
	WIN_VALUE = 2048
};

typedef struct s_vector {
    int x;
    int y;
} t_vector;

int (*move_left_right(int board[][4], int x, int y))[BOARD_SIZE];
int (*move_up_down(int board[][4], int x, int y))[BOARD_SIZE];
int (*merge_up_down(int board[][4], int x_pos, int y_pos, int found, int dir))[BOARD_SIZE];
int (*merge_left_right(int board[][4], int x_pos, int y_pos, int found, int dir))[BOARD_SIZE];

#endif