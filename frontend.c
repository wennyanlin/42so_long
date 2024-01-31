#include "so_long.h"

void	start()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	// int		offset;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 400, 400, "So long");

	img.img = mlx_new_image(mlx, 400, 400);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// offset = (y * img.line_length + x * (img.bits_per_pixel / 8));
	for (int y = 0; y < 400; ++y)
	{
		for (int x = 0; x < 400; ++x)
		{
			my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		}
	}

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
