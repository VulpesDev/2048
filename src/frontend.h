#ifndef FRONTEND_H
# define FRONTEND_H
# define BOARD_SIZE 4
# include <string.h>
# include <stdlib.h>
# include <ncurses.h>
# include <time.h>
# include <stdio.h>

# define BOARD_SIZE 4

# define COLOR_EMPTY 8
# define COLOR_TWO 9
# define COLOR_FOUR 10
# define COLOR_EIGHT 11
# define COLOR_SIXTEEN 12
# define COLOR_THIRTY2 13
# define COLOR_SIXTY4 14
# define COLOR_ONE28 15
# define COLOR_TWO56 16
# define COLOR_FIVE12 17
# define COLOR_TEN24 18
# define COLOR_TWENTY48 19

void draw_board(int board[][BOARD_SIZE]);
void init_colors();

#endif
