#include "so_long.h"

void	calculate_window_size(t_data *window)
{
	int		img_width;
	int		img_height;
	void	*img;
	img = mlx_xpm_file_to_image(window->mlx, sand, &img_width, &img_height);
	window->width = img_width * window->game.width;
	window->height = img_height * window->game.height;
	mlx_destroy_image(window->mlx, img);
}

void	move_player(t_play old_game, t_play new_game, t_data *state)
{
	draw_tile(state, new_game.map, old_game.player_row, old_game.player_column);
	draw_tile(state, new_game.map, new_game.player_row, new_game.player_column);
}

int	press_x_exit(t_data *state)
{
	mlx_destroy_image(state->mlx, state->img);
	quit_game(*state, exit_failure);
	return(1);
}

int	handle_command(int keycode, t_data *state)
{
	t_play	old_game;
	t_play	new_game;
	char	command;

	command = validate_direction_command(keycode);
	if (command == QUIT)
		quit_game(*state, exit_failure);
	old_game = state->game;
	state->game = get_new_game_state(old_game, command);
	new_game = state->game;
	if (state->game.game_state == PLAYER_WIN)
		quit_game(*state, exit_success);
	move_player(old_game, new_game, state);
	return (0);
}

t_data	start_game(t_play map)
{
	t_data	state;

	state.game = map;
	state.mlx = mlx_init(); //to establish a connection to the correct graphical system and will return a void * which holds the location of our current MLX instance.
	calculate_window_size(&state);
	state.img = mlx_new_image(state.mlx, state.width, state.height);
	state.mlx_win =
		mlx_new_window(state.mlx, state.width, state.height, "So long");
	draw_map_background(&state);
	mlx_hook(state.mlx_win, 2, 1L<<0, handle_command, &state);
	mlx_hook(state.mlx_win, 17, 1L<<2, press_x_exit, &state);
	mlx_loop(state.mlx);
	return (state);
}
