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

char **buildPlayground(int height, int width)
{
	char **playground;
	int i = 0;
	int	j = 0;

	playground = malloc((sizeof(char*)) * (height + 1));
	if (!playground)
		return (NULL);
	while (i < height)
	{
        playground[i] = malloc(sizeof(char) * (width + 1));
		if (!playground[i])
			return (NULL);

		if (i == 0 || i == (height - 1))
		{
			j = 0;
			while (j < width)
				playground[i][j++] = '1';
		}
		else
		{
			playground[i][0] = '1';
			playground[i][width - 1] = '1';
			j = 1;
			while (j != 0 && j != (width - 1))
			{
				playground[i][j++] = '0';
			}
		}
		playground[i][width] = '\0';
		i++;
	}
	playground[i] = NULL;
	return (playground);
}


void print_playground(t_play playground)
{
	printf("num_collectable: %d\n", playground.num_collectable);
	printf("player_x: %d\n", playground.player_x);
	printf("player_x: %d\n", playground.player_y);
	printf("is_exit_open: %d\n", playground.is_exit_open);
}

void write_playground(int fd, char **playground, int width)
{
	int i = 0;

	while(playground[i])
	{
		write(fd, playground[i], width);
		write(fd, "\n", 1);
		i++;
	}
}
