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

//Before splitting the input playground string into an array of string, check for the empty lines, spaces and other non-related characters.
int are_empty_lines(char *storage)
{
	int i;

	i = 0;
	while (storage[i])
	{
		if (storage[i + 1] && storage[i] == NEWLINE &&
			storage[i + 1] == NEWLINE)
			return (1);
		else if (storage[i] && (storage[i] != WALL && storage[i] != NEWLINE &&
			 storage[i] != PATH && storage[i] != EXIT &&
			 storage[i] != COLLECTABLE && storage[i] != PLAYER))
			return (1);
		i++;
	}
	return (0);
}

int	are_same_width(char *raw_map)
{
	int	i;
	int	len;
	int	width;

	i = 0;
	len = 0;
	width = -1;
	while (raw_map[i])
	{
		len = 0;
		while (raw_map[i] && raw_map[i] != '\n')
		{
			len++;
			i++;
		}
		if (raw_map[i] != '\0')
			i++;
		if (width == -1)
			width = len;
		if (width != len)
			return (0);
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
	if (are_empty_lines(raw_map))
		raw_map_exit(raw_map,  "Map can not contains empty lines.");
	if (!are_same_width(raw_map))
		raw_map_exit(raw_map,  "All rows must have the same width.");
	map = ft_split(raw_map, '\n');
	free(raw_map);
	if (map == NULL)
		map_exit(map, "Failed to parse the map");
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
