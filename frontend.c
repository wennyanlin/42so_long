#include "so_long.h"

void	calculate_window_size(t_data *window)
{
	int		img_width;
	int		img_height;
	void	*img;
	img = mlx_xpm_file_to_image(window->mlx, "./game_assets/sand.xpm", &img_width, &img_height);
	window->width = img_width * window->playground_state.width;
	window->height = img_height * window->playground_state.height;
	mlx_destroy_image(window->mlx, img);
}

void	draw_tile(t_data *frontend_state, char **playground, int row, int column)
{
	void	*image_to_draw;

	image_to_draw = mlx_xpm_file_to_image(frontend_state->mlx, "./game_assets/sand.xpm", &frontend_state->width, &frontend_state->height);
	mlx_put_image_to_window(frontend_state->mlx, frontend_state->mlx_win, image_to_draw, column * 50, row * 50);
	if (playground[row][column] == '1')
	{
		image_to_draw = mlx_xpm_file_to_image(frontend_state->mlx, "./game_assets/rock.xpm", &frontend_state->width, &frontend_state->height);
		mlx_put_image_to_window(frontend_state->mlx, frontend_state->mlx_win, image_to_draw, column * 50, row * 50);
	}
	else if (playground[row][column] == 'C')
	{
		image_to_draw = mlx_xpm_file_to_image(frontend_state->mlx, "./game_assets/money.xpm", &frontend_state->width, &frontend_state->height);
		mlx_put_image_to_window(frontend_state->mlx, frontend_state->mlx_win, image_to_draw, column * 50, row * 50);
	}
	else if (playground[row][column] == 'P')
	{
		image_to_draw = mlx_xpm_file_to_image(frontend_state->mlx, "./game_assets/crab.xpm", &frontend_state->width, &frontend_state->height);
		mlx_put_image_to_window(frontend_state->mlx, frontend_state->mlx_win, image_to_draw, column * 50, row * 50);
	}
	else if (playground[row][column] == 'E')
	{
		image_to_draw = mlx_xpm_file_to_image(frontend_state->mlx, "./game_assets/boat.xpm", &frontend_state->width, &frontend_state->height);
		mlx_put_image_to_window(frontend_state->mlx, frontend_state->mlx_win, image_to_draw, column * 50, row * 50);
	}
}

void	draw_map_background(t_data *frontend_state)
{
	int		i;
	int		j;
	char	**playground;

	i = 0;
	j = 0;
	playground = frontend_state->playground_state.playground;
	while (playground[i])
	{
		j = 0;
		while (playground[i][j])
			draw_tile(frontend_state, playground, i, j++);
		i++;
	}
}

void	move_player(t_play old_playground_state, t_play new_playground_state, t_data *frontend_state)
{
	draw_tile(frontend_state, new_playground_state.playground, old_playground_state.player_row, old_playground_state.player_column);
	draw_tile(frontend_state, new_playground_state.playground, new_playground_state.player_row, new_playground_state.player_column);
}

int	handle_command(int keycode, t_data *frontend_state)
{
	t_play	old_playground_state;
	t_play	new_playground_state;

	frontend_state->keycode = keycode;
	old_playground_state = frontend_state->playground_state;
	frontend_state->playground_state = get_playground_new_status(*frontend_state, validate_direction_command(frontend_state->keycode));
	new_playground_state = frontend_state->playground_state; 
	move_player(old_playground_state, new_playground_state, frontend_state);
	frontend_state->keycode = NEGATIVE;
	return (0);
}

t_data	start(t_play playground)
{
	t_data	frontend_state;

	frontend_state.playground_state = playground;
	frontend_state.mlx = mlx_init(); //to establish a connection to the correct graphical system and will return a void * which holds the location of our current MLX instance.
	frontend_state.img = mlx_new_image(frontend_state.mlx, frontend_state.width, frontend_state.height);
	calculate_window_size(&frontend_state);
	frontend_state.mlx_win = mlx_new_window(frontend_state.mlx, frontend_state.width, frontend_state.height, "So long");
	draw_map_background(&frontend_state);
	mlx_hook(frontend_state.mlx_win, 2, 1L<<0, handle_command, &frontend_state);
	mlx_hook(frontend_state.mlx_win, 17, 1L<<2, final_exit, &frontend_state);
	mlx_loop(frontend_state.mlx);
	return (frontend_state);
}

int	final_exit(t_data *frontend_state)
{
	mlx_destroy_window(frontend_state->mlx, frontend_state->mlx_win);
	mlx_destroy_image(frontend_state->mlx, frontend_state->img);
	free_array(frontend_state->playground_state.playground);
	exit(0);
}
