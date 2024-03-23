#include "so_long.h"

t_play empty_game()
{
	t_play game;
	game.num_move = 0;
	game.num_collectable = 0;
	game.error = NULL;
	game.map = NULL;
	game.width = UNSET;
	game.height = UNSET;
	game.player_row = UNSET;
	game.player_column = UNSET;
	game.is_exit_open = UNSET;
	game.game_state = UNSET;
	return (game);
}

int are_empty_lines(char *raw_map)
{
	int i;

	i = 0;
	while (raw_map[i])
	{
		if (raw_map[i + 1] && raw_map[i] == NEWLINE &&
			raw_map[i + 1] == NEWLINE)
			return (1);
		i++;
	}
	return (0);
}

int	are_valid_map_objects(char *raw_map)
{
	int i;

	i = 0;
	while (raw_map[i])
	{
		if (raw_map[i] && (raw_map[i] != WALL && raw_map[i] != NEWLINE &&
			 raw_map[i] != PATH && raw_map[i] != EXIT &&
			 raw_map[i] != COLLECTABLE && raw_map[i] != PLAYER) &&
			 raw_map[i] > 31)
			return (0);
		i++;
	}
	return (1);
}

char **validate_map(char *filepath)
{
	char	*raw_map;
	char 	**map;

	raw_map = read_map_file(filepath);
	if (!raw_map)
		raw_map_exit(raw_map,  strerror(errno));
	if (!are_valid_map_objects(raw_map))
		raw_map_exit(raw_map,  "Map contains invalid objects.");
	if (are_empty_lines(raw_map))
		raw_map_exit(raw_map,  "Map can not contains empty lines.");
	map = ft_split(raw_map, '\n');
	free(raw_map);
	if (!map)
		return (
			ft_printf("Failed to Parse the map\n"), exit(EXIT_FAILURE), NULL
		);
	return map;
}

t_play	parse_map(char *filepath)
{
	char 	**map;
	t_play	game;

	map = validate_map(filepath);
	game = validate_game(map);
	if (game.error != NULL)
		map_exit(map, game.error);
	game.map = map;
	return (game);
}
