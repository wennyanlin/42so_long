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
	return (0);
}

t_play	get_playground_new_status(t_play playground_state, char command)
{
	int	row;
	int	column;

	row = playground_state.player_row;
	column = playground_state.player_column;
	if (command == 'W')
		playground_state = update_command(playground_state, (row - 1), column);
	else if (command == 'S')
		playground_state = update_command(playground_state, (row + 1), column);
	else if (command == 'A')
		playground_state = update_command(playground_state, row, (column - 1));
	else if (command == 'D')
		playground_state = update_command(playground_state, row, (column + 1));
	return (playground_state);
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

int	main(int argc, char **argv)
{
	t_play	playground_state;
	char 	**arr;
	char	*str;

	if (argc != 2)
		return (0);
	str = read_file(argv[1]);
	if (!str)
		return (1);
	if (are_empty_lines(str))
	{
		free(str);
		write_error_and_return();
	}
	arr = ft_split(str, '\n');
	playground_state = is_playground_shape_valid(arr);
	if (playground_state.is_valid == -2)
		write_error_and_return();
	playground_state.playground = arr;
	start(playground_state);
	return (0);
}
