#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "./mlx/mlx.h"
#include <math.h>

typedef struct s_play
{
	char	**playground;
	int 	width;
	int		height;
	int		player_row;
	int		player_column;
	int		is_exit_open;
	int 	num_collectable;
	int		num_move;
	int		is_valid;
}	t_play;

typedef struct s_data
{
	void	*img;
	char	*path;
	void	*mlx;
	void	*mlx_win;
	int		keycode;
	int		width;
	int		height;
	t_play	playground_state;
}	t_data;

//string_utils
size_t	ft_strlen(char *s);
int		string_contain(char *str, char target);
char	*duplicate_storage(char *storage, char *buffer);
char	*ft_strjoin(char *str1, char *str2);
char	**ft_split(char *str, char seperator);
void	free_array(char **array);
void	ft_putnbr(int nbr);
void	write_num_moves(int num_move);


//read_file
char	*read_file(char *filepath);

//playground_check
t_play	is_playground_shape_valid(char **arr);
void	validate_playground_objects(char **arr, t_play *playground, int row, int column);
void	validate_playground_wall(char **arr, t_play *playground, int row);
int 	are_empty_lines(char *storage);

//playground_utils
// void 	write_playground(int fd, char **playground, int width);
t_play	update_command(t_data frontend_state, int newplayer_x, int newplayer_y);
t_play	get_playground_new_status(t_data frontend_state, char command);
char	validate_direction_command(int keycode);
// t_play	update_command(t_play playground_state, int newplayer_x, int newplayer_y);
t_play	empty_playground();
void	frontend_exit(t_data frontend_state, int code);
void	free_array(char **array);
void	array_playground_exit(char **array_playground, int code);

//test functions
void	test_read();
void	test_string_utils();
void	test_split();
void	test_playground_check();
void 	print_playground(t_play playground);

//frontend
t_data	start(t_play playground);
void	draw_map_background(t_data *image);
int		handle_command(int keycode, t_data *img);
int		final_exit(t_data *frontend_state);

//ft_itoa
char	*ft_itoa(int n);
int		ft_is_negative(int *n);
char	*ft_caso_zero(char n);
int		calculate_digits(int n);
char	*ft_strdup(const char *s1);

#endif
