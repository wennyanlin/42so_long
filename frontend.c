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

void	draw_map_background(t_data *image)
{
	void	*image_to_win;
	int		i;
	int		j;
	char	**playground;

	i = 0;
	j = 0;
	playground = image->playground_state.playground;
	while (playground[i])
	{
		j = 0;
		while (playground[i][j])
		{
			image_to_win = mlx_xpm_file_to_image(image->mlx, "./game_assets/sand.xpm", &image->width, &image->height);
			mlx_put_image_to_window(image->mlx, image->mlx_win, image_to_win, j * 50, i * 50);
			if (playground[i][j] == '1')
			{
				image_to_win = mlx_xpm_file_to_image(image->mlx, "./game_assets/rock.xpm", &image->width, &image->height);
				mlx_put_image_to_window(image->mlx, image->mlx_win, image_to_win, j * 50, i * 50);
			}
			else if (playground[i][j] == 'C')
			{
				image_to_win = mlx_xpm_file_to_image(image->mlx, "./game_assets/money.xpm", &image->width, &image->height);
				mlx_put_image_to_window(image->mlx, image->mlx_win, image_to_win, j * 50, i * 50);
			}
			else if (playground[i][j] == 'P')
			{
				image_to_win = mlx_xpm_file_to_image(image->mlx, "./game_assets/crab.xpm", &image->width, &image->height);
				mlx_put_image_to_window(image->mlx, image->mlx_win, image_to_win, j * 50, i * 50);
			}
			else if (playground[i][j] == 'E')
			{
				image_to_win = mlx_xpm_file_to_image(image->mlx, "./game_assets/boat.xpm", &image->width, &image->height);
				mlx_put_image_to_window(image->mlx, image->mlx_win, image_to_win, j * 50, i * 50);
			}
			j++;
		}
		i++;
	}

	// image_to_win = mlx_xpm_file_to_image(image->mlx, "./game_assets/crab_idle.xpm", &image->width, &image->height);
	// mlx_put_image_to_window(image->mlx, image->mlx_win, image_to_win, 0, 0);

}

int	close_window(int keycode, t_data *img)
{
	// mlx_destroy_window(vars->mlx, vars->win);
	img->keycode = keycode;
	img->playground_state = get_playground_new_status(img->playground_state, validate_direction_command(img->keycode));
	draw_map_background(img);
	// mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	img->keycode = -1;
	printf("keycode: '%d'\n", keycode);
	return (0);
}

void	start(t_play playground)
{
	t_data	img;

	img.playground_state = playground;

	img.mlx = mlx_init();
	calculate_window_size(&img);
	// img.path = mlx_xpm_file_to_image(img.mlx, img.path, &img.width, &img.height);
	img.mlx_win = mlx_new_window(img.mlx, img.width, img.height, "So long");

	img.img = mlx_new_image(img.mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_map_background(&img);
	mlx_hook(img.mlx_win, 2, 1L<<0, close_window, &img);
	// mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_loop(img.mlx);
	// printf("keycode in the loop: %d\n", img.keycode);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
