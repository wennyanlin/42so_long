#include "so_long.h"



int	close_window(int keycode, t_data *img)
{
	// mlx_destroy_window(vars->mlx, vars->win);
	img->keycode = keycode;
	printf("keycode: '%d'\n", keycode);

	return (0);
}

// void	event_handler(void)
// {
// 	t_vars	vars;

// 	vars.mlx = mlx_init();
// 	vars.win = mlx_new_window(vars.mlx, 200, 400, "Hello world!");
// 	mlx_hook(vars.win, 2, 1L<<0, close_window, &vars);
// 	mlx_loop(vars.mlx);
// }


void	calculate_window_size(t_play playground, t_data *image)
{
	int WINDOW_SIZE = 800;

	if (playground.width < playground.height)
	{
		image->width = round(((float)playground.width / (float)playground.height) * WINDOW_SIZE);
		image->height = WINDOW_SIZE;
	}
	else if (playground.height < playground.width)
	{
		image->height = round(((float)playground.height / (float)playground.width) * WINDOW_SIZE);
		image->width = WINDOW_SIZE;
	}
	else
	{
		image->height = WINDOW_SIZE;
		image->width = WINDOW_SIZE;
	}
}

void	draw_map(t_play playground_state, t_data *image)
{
	char	**playground;
	// void	*img;
	int		i;
	int		j;
	int		m;
	int		n;
	int		img_height;
	int		img_width;

	playground = playground_state.playground;
	img_height = image->height / playground_state.height;
	img_width = image->width / playground_state.width;
	i = 0;
	j = 0;
	while (playground[i])
	{
		j = 0;
		while(playground[i][j])
		{
			n = 0;
			while (n < img_height)
			{
				m = 0;
				while (m < img_width)
				{
					if (playground[i][j] == '1')
						my_mlx_pixel_put(image, ((j * img_width) + m), ((i * img_height) + n), 0x00808080);
					else if (playground[i][j] == 'C')
						my_mlx_pixel_put(image, ((j * img_width) + m), ((i * img_height) + n), 0xFFDA03);
					else if (playground[i][j] == 'E')
					my_mlx_pixel_put(image, ((j * img_width) + m), ((i * img_height) + n), 0xCC7722);
					else if (playground[i][j] == 'P')
						my_mlx_pixel_put(image, ((j * img_width) + m), ((i * img_height) + n), 0x000080);
					else
						my_mlx_pixel_put(image, ((j * img_width) + m), ((i * img_height) + n), 0x98BF64);
					m++;
				}
				n++;
			}
			j++;
		}
		i++;
	}
}

void	start(t_play playground)
{
	t_data	img;

	calculate_window_size(playground, &img);
	img.playground_state = playground;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, img.width, img.height, "So long");
	img.img = mlx_new_image(img.mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_hook(img.mlx_win, 2, 1L<<0, close_window, &img);
	mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_loop(img.mlx);
	// printf("keycode in the loop: %d\n", img.keycode);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	render_next_frame(t_data *img)
{
	draw_map(img->playground_state, img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	img->playground_state = get_playground_new_status(img->playground_state, validate_direction_command(img->keycode));
	return (0);
}
