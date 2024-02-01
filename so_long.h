#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "./mlx/mlx.h"

typedef struct s_play
{
	char	**playground;
	int 	width;
	int		player_x;
	int		player_y;
	int		is_exit_open;
	int 	num_collectable;
}	t_play;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		size_x;
	int		size_y;
}	t_data;

//string_utils
size_t	ft_strlen(char *str);
int		string_contain(char *str, char target);
char	*ft_strdup(char *str, int len);
char	*ft_strjoin(char *str1, char *str2);
char	**ft_split(char *str, char seperator);

//read_file
char	**read_file(char *filepath);

//playground_check
t_play	is_playground_shape_valid(char **arr);

//playground_utils
char 	**buildPlayground(int height, int width);
void 	write_playground(int fd, char **playground, int width);
t_play	update_command(t_play playground_state, int newplayer_x, int newplayer_y);

//test functions
void	test_read();
void	test_string_utils();
void	test_split();
void	test_playground_check();
void 	print_playground(t_play playground);

//frontend
void	start();
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_map(t_play playground_state, t_data *image);


#endif
