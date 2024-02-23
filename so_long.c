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
	{

		mlx_destroy_window(frontend_state.mlx, frontend_state.mlx_win);
		exit(0);
	}
	return (frontend_state.playground_state);
}

t_play	update_command(t_play playground_state, int newplayer_x, int newplayer_y)
{
	char	**playground;
	int		num_collectable;
	int		row;
	int		column;

	row = playground_state.player_row;
	column = playground_state.player_column;
	// printf("player[i][j]: [%i][%i]\n", newplayer_y, newplayer_x);
	num_collectable = playground_state.num_collectable;
	playground = playground_state.playground;
	if (playground[newplayer_x][newplayer_y] == '0' || playground[newplayer_x][newplayer_y] == 'C'
		|| (playground[newplayer_x][newplayer_y] == 'E' && num_collectable == 0))
	{
		if (playground[newplayer_x][newplayer_y] == 'C')
			playground_state.num_collectable--;
		if (playground[newplayer_x][newplayer_y] == 'E' && num_collectable == 0)
			playground_state.is_exit_open = 1;
		playground[row][column] = '0';
		playground[newplayer_x][newplayer_y] = 'P';
		playground_state.player_row = newplayer_x;
		playground_state.player_column = newplayer_y;
	}
	return (playground_state);
}

int	write_error_and_return()
{
	write(1, "Error\n", 6);
	exit(0);
}

void	ft_exit(t_data frontend_state)
{
	int		i;
	char	**playground;

	i = 0;
	playground = frontend_state.playground_state.playground;
	if (frontend_state.mlx)
		mlx_destroy_window(frontend_state.mlx, frontend_state.mlx_win);
	if (playground[i])
	{
		while (playground[i])
			free(playground[i++]);
		free(playground);
	}
	exit(0);
}

int	main(int argc, char **argv)
{
	t_play	playground_state;
	char	*string_playground;
	char 	**array_playground;

	if (argc != 2)
		return (0);
	string_playground = read_file(argv[1]);
	if (!string_playground)
		return (1);
	if (are_empty_lines(string_playground))
	{
		free(string_playground);
		write_error_and_return();
	}
	array_playground = ft_split(string_playground, '\n');
	playground_state = is_playground_shape_valid(array_playground);
	if (playground_state.is_valid == -2)
		write_error_and_return();
	playground_state.playground = array_playground;
	start(playground_state);
	return (0);
}
