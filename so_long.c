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
		frontend_exit(frontend_state, exit_success);
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
		write_num_moves(playground_state.num_move);
	}
	return (playground_state);
}

// int	string_playground_exit(char *string_playground)
// {
// 	free(string_playground);
// 	write(1, "Error\n", 6);
// 	exit(1);
// }

// void	array_playground_exit(char **array_playground, int code)
// {
// 	if (code == exit_success)
// 	{
// 		free_array(array_playground);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else if (code == exit_failure)
// 	{
// 		free_array(array_playground);
// 		write(1, "Error\n", 6);
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	frontend_exit(t_data frontend_state, int code)
// {
// 	char	**playground;

// 	playground = frontend_state.playground_state.playground;
// 	if (frontend_state.mlx)
// 		mlx_destroy_window(frontend_state.mlx, frontend_state.mlx_win);
// 	free_array(playground);
// 	if (code == exit_success)
// 		exit(EXIT_SUCCESS);
// 	else if (code == exit_failure)
// 		exit(EXIT_FAILURE);
// }

t_play	get_playground(char *filepath)
{
	char	*string_playground;
	char 	**array_playground;
	t_play	playground_state;
	
	string_playground = read_map_file(filepath);
	if (!string_playground)
		string_playground_exit(string_playground, 0);
	if (are_empty_lines(string_playground))
		string_playground_exit(string_playground, 0);
	array_playground = ft_split(string_playground, '\n');
	playground_state = playground_validation(array_playground);
	if (playground_state.is_valid == INVALID)
		array_playground_exit(array_playground, exit_failure);
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
	return (0);
}

//functions to group and classify different check cases
// -get_map();
// -get_playground();