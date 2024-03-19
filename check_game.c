#include "so_long.h"

void	validate_map_border(char **arr, t_play *game, int row)
{
	int	j;

	j = 0;
	if (row == 0 || arr[row + 1] == NULL)
	{
		while (arr[row][j])
		{
			if (arr[row][j] != WALL)
				game->error = "Map border missing wall.";
			j++;
		}
	}
	else if (arr[row][0] != WALL || arr[row][game->width - 1] != WALL)
		game->error = "Map border missing wall.";
}


void	validate_map_objects(char **arr, t_play *game, int row, int column)
{
	if (arr[row][column] == COLLECTABLE)
		game->num_collectable++;
	else if (arr[row][column] == PLAYER)
	{
		if (game->player_row == UNSET)
		{
			game->player_row = row;
			game->player_column = column;
		}
		else
			game->error = "Map contains more than one player.";
	}
	else if (arr[row][column] == EXIT)
	{
		if (game->is_exit_open == UNSET)
			game->is_exit_open = CLOSED;
		else
			game->error = "Map contains more than one exit.";
	}
}

t_play	final_check(t_play game)
{
	if (game.height > MAX_MAP_HEIGHT || game.width > MAX_MAP_WIDTH)
		return (set_error("Map size exceed maximum size.", game));
	else if (game.player_row == UNSET || game.player_column == UNSET)
		return (set_error("Map doesn't contain a player.", game));
	else if (game.num_collectable == 0)
	 	return (set_error("Map doesn't contain any collectable.", game));
	else if (game.is_exit_open == UNSET)
		return (set_error("Map doesn't contain any exit.", game));
	else if (check_exist_path(game, game.map) == INVALID)
		return (set_error("Map doesn't contain a valid route.", game));
	else
		return (game);
}
int	check_exist_path(t_play game, char **array)
{
	char 	**filled_array;
	int		i = 0;
	int		j = 0;

	filled_array = flood_fill(game, array);
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

t_play	validate_game(char **arr)
{
	int	i;
	int	j;
	t_play	game;

	i = -1;
	j = -1;
	game = empty_game();
	while (arr[++i] && game.error == NULL)
	{
		j = -1;
		validate_map_border(arr, &game, i);
		while (arr[i][++j])
			validate_map_objects(arr, &game, i, j);
		if (i == 0)
			game.width = j;
		if (j != game.width)
			return (set_error("All rows must have the same width.", game));
	}
	game.height = i;
	game.map = arr;
	return (final_check(game));
}
