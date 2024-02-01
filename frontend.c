#include "so_long.h"


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
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	calculate_window_size(playground, &img);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, img.width, img.height, "So long");

	img.img = mlx_new_image(mlx, img.width, img.height);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// offset = (y * img.line_length + x * (img.bits_per_pixel / 8));
	draw_map(playground, &img);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
