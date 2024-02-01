#include "so_long.h"

/**
 * 400 x 400
 *
 * 1111
 * 1001
 * 1001
 * 1111
 *
 * img_heigh = image.size_x / i;
	img_width = image.size_y / j;
*/
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
	// img = image.img;
	i = 0;
	j = 0;
	while (playground[i])
	{
		while (playground[i][j])
			j++;
		i++;
	}
	img_height = image->size_x / i;
	img_width = image->size_y / j;
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
					my_mlx_pixel_put(image, ((i * img_height) + n), ((j * img_width) + m), 0x00FF0000);
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

	img.size_x = 400;
	img.size_y = 400;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, img.size_x, img.size_y, "So long");

	img.img = mlx_new_image(mlx, 400, 400);
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
