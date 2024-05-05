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

void draw_board(int board[][BOARD_SIZE]) 
{
    for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
				printf("%i  ", board[i][j]);
            }
				printf("\n");
        }
				printf("\n\n");

}


// int (*move_up(int board[][4]))[BOARD_SIZE]
// {
// 	int x = 0;
// 	int y = 0;
// 	int i = 1;

// 	while (x < 4)
// 	{
// 		y = 0;
// 		while (y < 4)
// 		{
// 			if (!board[y][x])
// 			{
// 				i = 1;
// 				printf("x = %i, y = %i, i = %i\n", x, y, i);
// 				while ((y+i) < 4 && !board[y+i][x])
// 					i++;
// 				if( y+i < 4 && board[y+i][x])
// 				{
// 					board[y][x] = board[y+i][x];
// 					board[y+i][x] = 0;
// 				}
// 			}
// 			y++;			
// 		}
// 		x++;		
// 	}
// 	return (board);
// }

// int (*move_down(int board[][4]))[BOARD_SIZE]
// {
// 	int x = 0;
// 	int y = 3;
// 	int i = 1;
// 	while (x < 4)
// 	{
// 		y = 3;
// 		while (y > 0)
// 		{
// 			if (!board[y][x])
// 			{
// 				i = 1;
// 				while ((y-i) > -1 && !board[y-i][x])
// 					i++;
// 				if(y-i >= 0 && board[y-i][x])
// 				{
// 					board[y][x] = board[y-i][x];
// 					board[y-i][x] = 0;
// 					printf("here\n");
// 				}
// 			}
// 			y--;			
// 		}
// 		x++;		
// 	}
// 	return (board);
// }

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
			i = 1;
			while ((x + i * op < BOARD_SIZE && x + i * op >= RIGHT_LIMIT) && !board[y][x + i * op])
				i++;
			if ((x + i * op < BOARD_SIZE) && (x + i * op >= RIGHT_LIMIT) && board[y][x + i * op])
			{
			printf("x = %i\n", x);
				board[y][x] = board[y][x + i * op];
				board[y][x + i * op] = 0;
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

		

// int (*merge_up(int board[][4], int x_pos, int y_pos, int found))[BOARD_SIZE]
// {

// 	if (y_pos > 0 && board[--y_pos][x_pos] == found)
// 	{
// 		//merging here
// 		board[y_pos][x_pos] = 2 * found;
// 		board[y_pos + 1][x_pos] = 0;
// 		return (board);
// 	}
// 	return (board);
// }

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
		printf("here\n");
		board[y_pos][x_pos] = 2 * found;
		board[y_pos - 1][x_pos] = 0;
		return (board);
	}
	return (board);
}


int search_tiles(int board[][4])
{
	int x = 0;
	int y = 0;
	//up direction
	// board = move_up(board);
	// board = move_down(board);
	// board = move_up_down(board, 0, DOWN_Y);
	board = move_left_right(board, RIGHT_X, 0);
	// draw_board(board);
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			if (board[y][x])
			{
				// board = search_up(board, x, y, board[y][x]);
				// board = merge_up_down(board, x, y, board[y][x], DOWN_Y);
				draw_board(board);
			}
			y++;
		}
		x++;
	}
	// board = move_up_down(board, 0, DOWN_Y);

		// board = move_up(board);
	// board = move_up(board);

		draw_board(board);

	return(0);

}

// int search_up_down(int board[][4], int x, int y)
// {
	
// }

// int	start_game(int board[][BOARD_SIZE])
// {

//         int ch = getch();
//         switch (ch) {
//             case KEY_UP:
//                 search_tiles(board, 0, UP_Y);
//                 break;
//             case KEY_DOWN:
//                 // Move tiles down
//                 break;
//             case KEY_LEFT:
//                 // Move tiles left
//                 break;
//             case KEY_RIGHT:
//                 // Move tiles right
//                 break;
//             default:
//                 break;
// 		}
// 	return (0);
// }



int main()
{
    int board[][4] = {  {2, 2, 2, 2},
						{0, 0, 0, 16},
						{0, 8, 0, 16},
						{2, 0, 0, 2}};
	search_tiles(board);

	return (0);

}