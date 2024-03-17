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

t_play	get_playground_new_status(t_data frontend_state, char command)
{
	int	row;
	int	column;

	row = frontend_state.playground_state.player_row;
	column = frontend_state.playground_state.player_column;
	if (command == UP)
		frontend_state.playground_state = update_command(frontend_state, (row - 1), column);
	else if (command == DOWN)
		frontend_state.playground_state = update_command(frontend_state, (row + 1), column);
	else if (command == LEFT)
		frontend_state.playground_state = update_command(frontend_state, row, (column - 1));
	else if (command == RIGHT)
		frontend_state.playground_state = update_command(frontend_state, row, (column + 1));
	else if (command == QUIT)
		frontend_exit(frontend_state, exit_failure);
	return (frontend_state.playground_state);
}

t_play	update_command(t_data frontend_state, int newplayer_x, int newplayer_y)
{
	char	**playground;
	int		num_collectable;
	int		row;
	int		column;
	t_play	playground_state;

	playground_state = frontend_state.playground_state;
	playground = frontend_state.playground_state.playground;
	row = playground_state.player_row;
	column = playground_state.player_column;
	num_collectable = playground_state.num_collectable;
	if (playground[newplayer_x][newplayer_y] == PATH || playground[newplayer_x][newplayer_y] == COLLECTABLE
		|| (playground[newplayer_x][newplayer_y] == EXIT && num_collectable == 0))
	{
		if (playground[newplayer_x][newplayer_y] == COLLECTABLE)
			playground_state.num_collectable--;
		if (playground[newplayer_x][newplayer_y] == EXIT && num_collectable == 0)
		{
			playground_state.is_exit_open = POSITIVE;
			frontend_exit(frontend_state, exit_success);
		}
		playground[row][column] = PATH;
		playground[newplayer_x][newplayer_y] = PLAYER;
		playground_state.player_row = newplayer_x;
		playground_state.player_column = newplayer_y;
		playground_state.num_move++;
		ft_printf("You made: %i step/s\n", playground_state.num_move);
	}
	return (playground_state);
}

t_play	get_playground(char *filepath)
{
	char	*string_playground;
	char 	**array_playground;
	t_play	playground_state;

	if (check_file_extension(filepath) == INVALID)
	{
		ft_printf("Error\n");
		ft_printf("Not a valid file type\n");
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
