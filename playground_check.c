#include "so_long.h"

t_play empty_playground()
{
	t_play playground;
	playground.playground = NULL;
	playground.width = -1;
	playground.height = -1;
	playground.num_collectable = 0;
	playground.player_row = -1;
	playground.player_column = -1;
	playground.is_exit_open = -1;
	playground.is_valid = -1;

	return (playground);
}

void	validate_playground_wall(char **arr, t_play *playground, int row)
{
	int	j;

	j = 0;
	if (row == 0 || arr[row + 1] == NULL)
	{
		while (arr[row][j])
		{
			if (arr[row][j] != '1')
				playground->is_valid = -2;
			j++;
		}
	}
	else if (arr[row][0] != '1' || arr[row][playground->width - 1] != '1')
		playground->is_valid = -2;
}

void	validate_playground_objects(char **arr, t_play *playground, int row, int column)
{
	if (arr[row][column] == 'C')
		playground->num_collectable++;
	else if (arr[row][column] == 'P')
	{
		if (playground->player_row == -1) // is first player found?
		{
			playground->player_row = row;
			playground->player_column = column;
		} else { // else is more then one player
			playground->player_row = -2;
			playground->player_column = -2;
		}
	}
	else if (arr[row][column] == 'E')
	{
		if (playground->is_exit_open == -1)
			playground->is_exit_open = 0;
		else
			playground->is_exit_open = -2;
	}
}

t_play	is_playground_shape_valid(char **arr)
{
	int	i;
	int	j;
	t_play	playground;

	i = 0;
	j = 0;
	playground = empty_playground();
	while (arr[i] && playground.is_valid != -2)
	{
		j = 0;
		validate_playground_wall(arr, &playground, i);
		while (arr[i][j])
			validate_playground_objects(arr, &playground, i, j++);
		if (i == 0)
			playground.width = j;
		if (j != playground.width)
			return (playground);
		i++;
	}
	playground.height = i;
	if (playground.height < 3 || playground.width < 3 || playground.height > 17 || playground.width > 29)
		playground.is_valid = -2;
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

	// print_playground(is_playground_shape_valid(read_file("maps/playground_detail.ber")));
	// print_playground(is_playground_shape_valid(read_file("maps/more_than_one_player.ber")));
	// print_playground(is_playground_shape_valid(read_file("maps/more_than_one_exit.ber")));
}


