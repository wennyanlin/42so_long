#include "so_long.h"

t_play empty_playground()
{
	t_play playground;
	playground.playground = NULL;
	playground.width = UNSET;
	playground.height = UNSET;
	playground.num_collectable = 0;
	playground.num_move = 0;
	playground.player_row = UNSET;
	playground.player_column = UNSET;
	playground.is_exit_open = UNSET;
	playground.is_valid = UNSET;
	playground.error.error_code = UNSET;
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
		if (playground->player_row == UNSET) // is first player found?
		{
			playground->player_row = row;
			playground->player_column = column;
		}
		else
			playground->error = error(INVALID, "Map contains more than one player.");
	}
	else if (arr[row][column] == EXIT)
	{
		if (playground->is_exit_open == UNSET)
			playground->is_exit_open = 0;
		else
			playground->error = error(INVALID, "Map contains more than one exit.");
	}
}

t_play	final_check(t_play playground)
{
	if (playground.height > MAX_MAP_HEIGHT || playground.width > MAX_MAP_WIDTH)
		return (set_error(INVALID, "Map size exceed maximum size.", playground));
	else if (playground.player_row == UNSET || playground.player_column == UNSET)
		return (set_error(INVALID, "Map doesn't contain a player.", playground));
	else if (playground.num_collectable == 0)
	 	return (set_error(INVALID, "Map doesn't contain any collectable.", playground));
	else if (playground.is_exit_open == UNSET)
		return (set_error(INVALID, "Map doesn't contain any exit.", playground));
	else if (check_exist_path(playground, playground.playground) == INVALID)
		return (set_error(INVALID, "Map doesn't contain a valid route.", playground));
	else
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
				return (INVALID);
			j++;
		}
		i++;
	}
	free_array(filled_array);
	return (1);
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
	playground.playground = arr;
	return (final_check(playground));
}
