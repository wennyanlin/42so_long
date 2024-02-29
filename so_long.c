#include "so_long.h"

char	validate_direction_command(int keycode)
{
	if (keycode == 13)
		return ('W');
	else if (keycode == 1)
		return ('S');
	else if (keycode == 0)
		return ('A');
	else if (keycode == 2)
		return ('D');
	else if (keycode == 53)
		return ('Q');
	return (0);
}

t_play	get_playground_new_status(t_data frontend_state, char command)
{
	int	row;
	int	column;

	row = frontend_state.playground_state.player_row;
	column = frontend_state.playground_state.player_column;
	if (command == 'W')
		frontend_state.playground_state = update_command(frontend_state.playground_state, (row - 1), column);
	else if (command == 'S')
		frontend_state.playground_state = update_command(frontend_state.playground_state, (row + 1), column);
	else if (command == 'A')
		frontend_state.playground_state = update_command(frontend_state.playground_state, row, (column - 1));
	else if (command == 'D')
		frontend_state.playground_state = update_command(frontend_state.playground_state, row, (column + 1));
	else if (command == 'Q')
		frontend_exit(frontend_state, 0);
	return (frontend_state.playground_state);
}

t_play	update_command(t_play playground_state, int newplayer_x, int newplayer_y)
{
	char	**playground;
	int		num_collectable;
	int		row;
	int		column;
	// char	str_num;

	row = playground_state.player_row;
	column = playground_state.player_column;
	num_collectable = playground_state.num_collectable;
	playground = playground_state.playground;
	if (playground[newplayer_x][newplayer_y] == '0' || playground[newplayer_x][newplayer_y] == 'C'
		|| (playground[newplayer_x][newplayer_y] == 'E' && num_collectable == 0))
	{
		if (playground[newplayer_x][newplayer_y] == 'C')
			playground_state.num_collectable--;
		if (playground[newplayer_x][newplayer_y] == 'E' && num_collectable == 0)
		{
			playground_state.is_exit_open = 1;
			//handle exit program!!!
		}
		playground[row][column] = '0';
		playground[newplayer_x][newplayer_y] = 'P';
		playground_state.player_row = newplayer_x;
		playground_state.player_column = newplayer_y;
		//handle moves count
		// playground_state.num_move++;
		// str_num = malloc(sizeof(char) * (playground_state.num_move + 1));
		// str_num = ft_itoa(playground_state.num_move);
	}
	return (playground_state);
}

int	string_playground_exit(char *string_playground)
{
	free(string_playground);
	write(1, "Error\n", 6);
	exit(1);
}

void	array_playground_exit(char **array_playground, int code)
{
	if (code == 0)
	{
		free_array(array_playground);
		exit(EXIT_SUCCESS);
	}
	else if (code == 1)
	{
		free_array(array_playground);
		write(1, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
}

void	frontend_exit(t_data frontend_state, int code)
{
	int		i;
	char	**playground;

	i = 0;
	playground = frontend_state.playground_state.playground;
	if (frontend_state.mlx)
		mlx_destroy_window(frontend_state.mlx, frontend_state.mlx_win);
	free_array(playground);
	if (code == 0)
		exit(EXIT_SUCCESS);
	else if (code == 1)
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_play	playground_state;
	t_data	frontend_state;
	char	*string_playground;
	char 	**array_playground;

	if (argc != 2)
		return (0);
	string_playground = read_file(argv[1]);
	if (!string_playground || are_empty_lines(string_playground))
		string_playground_exit(string_playground);
	array_playground = ft_split(string_playground, '\n');
	if (!array_playground)
		array_playground_exit(playground_state.playground, 1);
	playground_state = is_playground_shape_valid(array_playground);
	if (playground_state.is_valid == -2)
		array_playground_exit(playground_state.playground, 1);
	playground_state.playground = array_playground;
	frontend_state = start(playground_state);
	frontend_exit(frontend_state, 0);
	return (0);
}
