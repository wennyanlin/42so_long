#include "so_long.h"

t_play empty_playground()
{
	t_play playground;
	playground.playground = NULL;
	playground.width = -1;
	playground.num_collectable = 0;
	playground.player_x = -1;
	playground.player_y = -1;
	playground.is_exit_open = -1;

	return (playground);
}

void print_playground(t_play playground)
{
	printf("num_collectable: %d\n", playground.num_collectable);
	printf("player_x: %d\n", playground.player_x);
	printf("player_x: %d\n", playground.player_y);
	printf("is_exit_open: %d\n", playground.is_exit_open);
}

t_play	is_playground_shape_valid(char **arr)
{
	int	i;
	int	j;
	int	width;
	t_play	playground;

	i = 0;
	j = 0;
	width = 0;
	playground = empty_playground();
	while (arr[i])
	{
		j = 0;
		if (i == 0 || arr[i + 1] == NULL) //is first or last row?
		{
			while (arr[i][j])
			{
				if (arr[i][j] != '1')
					return (playground);
				j++;
			}
		}
		else
		{
			if (arr[i][0] != '1' || arr[i][width - 1] != '1')
				return (playground);
			while (arr[i][j])
			{
				 if (arr[i][j] == 'C')
					playground.num_collectable++;
				else if (arr[i][j] == 'P')
				{
					if (playground.player_x == -1) // is first player found?
					{
						playground.player_x = i;
						playground.player_y = j;
					} else { //more then one player
						playground.player_x = -2;
						playground.player_y = -2;
					}
				}
				else if (arr[i][j] == 'E')
				{
					if (playground.is_exit_open == -1)
						playground.is_exit_open = 0;
					else
						playground.is_exit_open = -2;
				}
				j++;
			}
		}
		if (i == 0)
			width = j;
		if (j != width)
			return (playground);
		i++;
	}
	if (i < 3 || width < 3)
		return (playground);
	return (playground);
}

void	test_playground_check()
{
	// char **playground = buildPlayground(3, 4);
	// printf("\nShould return success when playground is valid:\n");
	// write_playground(STDOUT_FILENO, playground, 4);
	// printf("expected: 1, actual result: %d\n", is_playground_shape_valid(playground));

	// printf("\n");
	// playground = buildPlayground(4, 2);
	// printf("\nShould return error code when playground width is invalid:\n");
	// write_playground(STDOUT_FILENO, playground, 2);
	// printf("expected: 0, actual result: %d\n", is_playground_shape_valid(playground));

	// playground = buildPlayground(2, 4);
	// printf("\nShould return error code when playground height is invalid:\n");
	// write_playground(STDOUT_FILENO, playground, 4);
	// printf("expected: 0, actual result: %d\n", is_playground_shape_valid(playground));


	// playground = read_file("maps/not_rectangle.ber");
	// printf("\nShould return error code when playground is not a rectangle:\n");
	// write_playground(STDOUT_FILENO, playground, 7);
	// printf("expected: 0, actual result: %d\n", is_playground_shape_valid(playground));

	// playground = read_file("maps/invalid_wall.ber");
	// printf("\nShould return error code when playground wall is not valid:\n");
	// write_playground(STDOUT_FILENO, playground, 5);
	// printf("expected: '0', actual result: '%d'\n", is_playground_shape_valid(playground));

	print_playground(is_playground_shape_valid(read_file("maps/playground_detail.ber")));
	print_playground(is_playground_shape_valid(read_file("maps/more_than_one_player.ber")));
	print_playground(is_playground_shape_valid(read_file("maps/more_than_one_exit.ber")));
}


