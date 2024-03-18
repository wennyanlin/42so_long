#include "so_long.h"

char	validate_direction_command(int keycode)
{
	if (keycode == 13)
		return (UP);
	else if (keycode == 1)
		return (DOWN);
	else if (keycode == 0)
		return (LEFT);
	else if (keycode == 2)
		return (RIGHT);
	else if (keycode == 53)
		return (QUIT);
	return (0);
}

t_play	get_playground_new_status(t_play playground_state, char command)
{
	int	row;
	int	column;

	row = playground_state.player_row;
	column = playground_state.player_column;
	if (command == UP)
		playground_state = update_command(playground_state, (row - 1), column);
	else if (command == DOWN)
		playground_state = update_command(playground_state, (row + 1), column);
	else if (command == LEFT)
		playground_state = update_command(playground_state, row, (column - 1));
	else if (command == RIGHT)
		playground_state = update_command(playground_state, row, (column + 1));
	return (playground_state);
}

int	can_move(t_play playground_state, int newplayer_row, int newplayer_column)
{
	char	new_position;

	new_position = playground_state.playground[newplayer_row][newplayer_column];
	if (new_position == PATH || new_position == COLLECTABLE
		|| (new_position == EXIT && playground_state.num_collectable == 0))
		return (POSITIVE);
	else
		return (INVALID);
}

t_play	update_command(t_play playground_state, int newplayer_row, int newplayer_column)
{
	char	**playground;
	char	new_position;

	playground = playground_state.playground;
	new_position = playground[newplayer_row][newplayer_column];
	if (can_move(playground_state, newplayer_row, newplayer_column) == POSITIVE)
	{
		if (new_position == EXIT && playground_state.num_collectable == 0)
			playground_state.game_state = PLAYER_WIN;
		if (new_position == COLLECTABLE)
			playground_state.num_collectable--;
		playground[playground_state.player_row][playground_state.player_column] = PATH;
		playground[newplayer_row][newplayer_column] = PLAYER;
		playground_state.player_row = newplayer_row;
		playground_state.player_column = newplayer_column;
		playground_state.num_move++;
		ft_printf("You made: %i step/s\n", playground_state.num_move);
		ft_printf("You made: %i step/s\n", playground_state.num_move);
	}
	return (playground_state);
}

// t_play	update_player(t_data frontend_state, int newplayer_row, int newplayer_column)
// {

// }

t_play	get_playground(char *filepath)
{
	char	*string_playground;
	char 	**array_playground;
	t_play	playground_state;

	if (check_file_extension(filepath) == INVALID)
	{
		ft_printf("Error\nNot a valid file type\n");
		exit(EXIT_FAILURE);
	}
	string_playground = read_map_file(filepath);
	if (!string_playground)
		string_playground_exit(string_playground, error(INVALID,  strerror(errno)));
	if (are_empty_lines(string_playground))
		string_playground_exit(string_playground, error(INVALID,  "Map contains a empty line."));
	array_playground = ft_split(string_playground, '\n');
	if (array_playground == NULL)
		array_playground_exit(array_playground, error(INVALID, "Failed to parse the map"));
	playground_state = playground_validation(array_playground);
	if (playground_state.error.error_code == INVALID)
		array_playground_exit(array_playground, playground_state.error);
	playground_state.playground = array_playground;
	return (playground_state);
}

int	main(int argc, char **argv)
{
	t_play	playground_state;
	t_data	frontend_state;
	char 	*filepath;

	if (argc != 2)
		return (0);
	filepath = argv[1];
	playground_state = get_playground(filepath);
	frontend_state = start_game(playground_state);
	frontend_exit(frontend_state, exit_success);
}
