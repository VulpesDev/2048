#ifndef FRONTEND_H
# define FRONTEND_H
# define BOARD_SIZE 4
# include <string.h>
# include <stdlib.h>
# include <ncurses.h>
# include <time.h>
# include <stdio.h>

# define BOARD_SIZE 4

# define COLOR_TWO 8
# define COLOR_FOUR 9
# define COLOR_EIGHT 10
# define COLOR_SIXTEEN 11
# define COLOR_THIRTY2 12
# define COLOR_SIXTY4 13
# define COLOR_ONE28 14
# define COLOR_TWO56 15
# define COLOR_FIVE12 16
# define COLOR_TEN24 17
# define COLOR_TWENTY48 18
# define COLOR_EMPTY 19

void draw_board(int board[][BOARD_SIZE]);

#endif
