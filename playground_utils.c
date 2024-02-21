#include "so_long.h"

t_play empty_playground()
{
	t_play playground;
	playground.playground = NULL;
	playground.width = -1;
	playground.height = -1;
	playground.num_collectable = 0;
	playground.player_x = -1;
	playground.player_y = -1;
	playground.is_exit_open = -1;
	playground.is_valid = -1;

	return (playground);
}

// void print_playground(t_play playground)
// {
// 	printf("num_collectable: %d\n", playground.num_collectable);
// 	printf("player_x: %d\n", playground.player_x);
// 	printf("player_x: %d\n", playground.player_y);
// 	printf("is_exit_open: %d\n", playground.is_exit_open);
// }

// void write_playground(int fd, char **playground, int width)
// {
// 	int i = 0;

// 	while(playground[i])
// 	{
// 		write(fd, playground[i], width);
// 		write(fd, "\n", 1);
// 		i++;
// 	}
// }
