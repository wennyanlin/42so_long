#include "so_long.h"

t_play empty_playground()
{
	t_play playground;
	playground.playground = NULL;
	playground.width = NEGATIVE;
	playground.height = NEGATIVE;
	playground.num_collectable = 0;
	playground.num_move = 0;
	playground.player_row = NEGATIVE;
	playground.player_column = NEGATIVE;
	playground.is_exit_open = NEGATIVE;
	playground.is_valid = NEGATIVE;
	playground.error.error_code = NEGATIVE;
	return (playground);
}

void	get_playground_wall(char **arr, t_play *playground, int row)
{
	int	j;

	j = 0;
	if (row == 0 || arr[row + 1] == NULL)
	{
		while (arr[row][j])
		{
			if (arr[row][j] != WALL)
				playground->error = error(INVALID, "Map border missing wall.");
			j++;
		}
	}
	else if (arr[row][0] != WALL || arr[row][playground->width - 1] != WALL)
		playground->error = error(INVALID, "Map border missing wall.");
}

void	get_playground_objects(char **arr, t_play *playground, int row, int column)
{
	if (arr[row][column] == COLLECTABLE)
		playground->num_collectable++;
	else if (arr[row][column] == PLAYER)
	{
		if (playground->player_row == NEGATIVE) // is first player found?
		{
			playground->player_row = row;
			playground->player_column = column;
		}
		else
		{ // else is more then one player
			playground->player_row = INVALID;
			playground->player_column = INVALID;
		}
	}
	else if (arr[row][column] == EXIT)
	{
		if (playground->is_exit_open == NEGATIVE)
			playground->is_exit_open = 0;
		else
			playground->is_exit_open = INVALID;
	}
}

t_play	playground_validation(char **arr)
{
	int	i;
	int	j;
	t_play	playground;

	i = -1;
	j = -1;
	playground = empty_playground();
	while (arr[++i] && playground.error.error_code != INVALID)
	{
		j = -1;
		get_playground_wall(arr, &playground, i);
		while (arr[i][++j])
			get_playground_objects(arr, &playground, i, j);
		if (i == 0)
			playground.width = j;
		if (j != playground.width)
			return (set_error(INVALID, "Invalid width, all rows must have the same width.", playground));
	}
	playground.height = i;
	if (playground.height < MIN_MAP_SIZE || playground.width < MIN_MAP_SIZE || playground.height > MAX_MAP_HEIGHT || playground.width > MAX_MAP_WIDTH)
		playground.is_valid = INVALID;
	else if (playground.player_row == NEGATIVE || playground.player_column == NEGATIVE || playground.num_collectable == 0
				|| playground.is_exit_open == NEGATIVE || check_exist_path(playground, arr) == NEGATIVE)
		playground.is_valid = INVALID;
	return (playground);
}

int	check_exist_path(t_play playground_state, char **array)
{
	char 	**filled_array;
	int		i = 0;
	int		j = 0;

	filled_array = flood_fill(playground_state, array);
	while (filled_array[i])
	{
		j = 0;
		while (filled_array[i][j])
		{
			if (filled_array[i][j] != WALL && filled_array[i][j] != PATH)
				return (-1);
			j++;
		}
		i++;
	}
	free_array(filled_array);
	return (1);
}

t_error	error(int code, char *message)
{
	t_error	error;

	error.error_code = code;
	error.error_message = message;
	return (error);
}

t_play	set_error(int code, char *message, t_play playground_state)
{
	playground_state.error = error(code, message);
	return (playground_state);
}
