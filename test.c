#include <stdio.h>


#define BOARD_SIZE 4

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
	board = move_up(board);
	draw_board(board);
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			if (board[y][x])
			{
				board = search_up(board, x, y, board[y][x]);
				draw_board(board);
			}
			y++;
		}
		x++;
	}
		board = move_up(board);
		draw_board(board);

	return(0);

}

int main()
{
    int board[][4] = {  {2, 2, 2, 2},
						{4, 0, 0, 16},
						{8, 8, 0, 16},
						{2, 0, 0, 2}};
	search_tiles(board);

	return (0);

}

