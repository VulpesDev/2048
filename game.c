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


int (*move_up(int board[][4]))[BOARD_SIZE]
{
	int x = 0;
	int y = 0;
	int i = 1;

	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			if (!board[y][x])
			{
				i = 1;
				while ((y+i) < 4 && !board[y+i][x])
					i++;
				if(y+i < 4 && board[y+i][x])
				{
					board[y][x] = board[y+i][x];
					board[y+i][x] = 0;
				}
			}
			y++;			
		}
		x++;		
	}
	return (board);
}

int (*move_down(int board[][4]))[BOARD_SIZE]
{
	int x = 0;
	int y = 3;
	int i = 1;
	while (x < 4)
	{
		y = 3;
		while (y > 0)
		{
			if (!board[y][x])
			{
				i = 1;
				while ((y-i) > -1 && !board[y-i][x])
					i++;
				if(y-i >= 0 && board[y-i][x])
				{
					board[y][x] = board[y-i][x];
					board[y-i][x] = 0;
					printf("here\n");
				}
			}
			y--;			
		}
		x++;		
	}
	return (board);
}

int (*move_up_down(int board[][4], int x, int y))[BOARD_SIZE]
{
	int i = 1;
	int op = (y == UP_Y? 1 : -1);
	printf("op = %i\n", op);
	int y_start = y;
	
	while (x < BOARD_SIZE)
	{
		y = y_start;
		while (((y < BOARD_SIZE) && y_start == UP_Y) || ((y_start == DOWN_Y && (y >= DOWN_LIMIT)) && (y < BOARD_SIZE)))
		{
			if (!board[y][x])
			{
				i = 1;
				while (((y_start == UP_Y  && ((y + ((i+1) * op)) < BOARD_SIZE )) || (y_start == DOWN_Y && ((y + (i * op)) >= DOWN_LIMIT)))  && ((y + ((i+1) * op)) < BOARD_SIZE ) && !board[y + (i * op)][x])
				{
					printf("y = %i\n", y);
				printf("y + i = %i, y + i*op = %i\n\n", y+i, y+ (i *op));
					i++;
				}	
				printf(" value = %i\n", board[y + (i * op)][x]);
				if (((y+i < UP_LIMIT) || (y + (i *op) >= DOWN_LIMIT)) && board[y + (i * op)][x])
				{
					board[y][x] = board[y + (i * op)][x];
					board[y + (i * op)][x] = 0;
				}				
			}
				// printf("y + i = %i, y + i*op = %i\n\n", y+i, y+ (i *op));
			y += op;
		}
		x++;
	}
	return (board);
}

		

int (*search_up(int board[][4], int x_pos, int y_pos, int found))[BOARD_SIZE]
{
	if (y_pos > 0 && board[--y_pos][x_pos] == found)
	{
		//merging here
		board[y_pos][x_pos] = 2 * found;
		board[y_pos + 1][x_pos] = 0;
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
	board = move_up_down(board, 0, UP_Y);
	draw_board(board);
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			if (board[y][x])
			{
				// board = search_up(board, x, y, board[y][x]);
				draw_board(board);
			}
			y++;
		}
		x++;
	}
		// board = move_up(board);
	// board = move_up_down(board, 0, UP_Y);

		// draw_board(board);

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
