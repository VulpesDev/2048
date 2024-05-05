#ifndef GRID_UTILITY_H
# define GRID_UTILITY_H
# include "algorithm.h"
# include "frontend.h"
# include <ncurses.h>

int main();
int game_status(int board[][BOARD_SIZE], int out);

/*grid utility*/
int check_end_conditions(int board[][4]);
void init_board(int board[][BOARD_SIZE]);
void spawn_new_tile(int board[][4]);

/*front*/
void hexToRGB(const char* hexColor, int* r, int* g, int* b);
void init_colors();
char* print_ascii_digit(char array[][11], int num, int size);
int digit_count(int n);
void draw_board(int board[][BOARD_SIZE]);

/*alg*/
int (*move_left_right(int board[][4], int x, int y))[BOARD_SIZE];
int (*move_up_down(int board[][4], int x, int y))[BOARD_SIZE];
int (*merge_up_down(int board[][4], int x_pos, int y_pos, int found, int dir))[BOARD_SIZE];
int (*merge_left_right(int board[][4], int x_pos, int y_pos, int found, int dir))[BOARD_SIZE];
int (*search_tiles(int board[][4], int(*(*merge_tiles)(int[][4], int, int, int, int))[], int(*(*move_tiles)(int[][4], int, int))[] , int dir_x, int dir_y, int cur_move))[BOARD_SIZE];

#endif