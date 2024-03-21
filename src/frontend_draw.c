#include "so_long.h"

void	put_image(t_data *state, int row, int column, char *xpm)
{
	void	*image_to_draw;

	image_to_draw = mlx_xpm_file_to_image(
		state->mlx, xpm,
		&state->width,&state->height
	);
	mlx_put_image_to_window(
		state->mlx, state->mlx_win,
		image_to_draw, column * 50, row * 50
	);
}

void	draw_tile(t_data *state, char **map, int row, int column)
{
	put_image(state, row, column, sand);
	if (map[row][column] == WALL)
		put_image(state, row, column, rock);
	else if (map[row][column] == COLLECTABLE)
		put_image(state, row, column, money);
	else if (map[row][column] == PLAYER)
		put_image(state, row, column, krab);
	else if (map[row][column] == EXIT)
		put_image(state, row, column, boat);
}


void	draw_map_background(t_data *state)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	map = state->game.map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			draw_tile(state, map, i, j++);
		i++;
	}
}
