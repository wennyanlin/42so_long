#ifndef SO_LONG_H
# define SO_LONG_H

//MACROS
#define MIN_MAP_SIZE 3
#define MAX_MAP_HEIGHT 17
#define MAX_MAP_WIDTH 29
#define PLAYER 'P'
#define COLLECTABLE 'C'
#define EXIT 'E'
#define PATH '0'
#define WALL '1'
#define UP 'W'
#define DOWN 'S'
#define LEFT 'A'
#define RIGHT 'D'
#define QUIT 'Q'
#define NEWLINE '\n'
#define exit_success 0
#define exit_failure 1
#define INVALID -2
#define NEGATIVE -1
#define POSITIVE 1

//libraries
# include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "./mlx/mlx.h"
#include "./ft_printf/ft_printf.h"
#include <math.h>
#include <errno.h>
#include <string.h>

//structs
typedef struct s_error
{
	int		error_code;
	char 	*error_message;
}	t_error;

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
	t_error	error;
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

//FUNCTION PROTOTYPES
//string_utils
size_t	ft_strlen(char *s);
int		string_contain(char *str, char target);
char	*duplicate_storage(char *storage, char *buffer);
char	*ft_strjoin(char *str1, char *str2);
char	**ft_split(char *str, char seperator);
void	free_array(char **array);
void	ft_putnbr(int nbr);
void	write_num_moves(int num_move);
char	**ft_strdup_array(char **array);


//read_file
char	*read_map_file(char *filepath);

//playground_check
t_play	playground_validation(char **arr);
void	get_playground_objects(char **arr, t_play *playground, int row, int column);
void	get_playground_wall(char **arr, t_play *playground, int row);
int 	are_empty_lines(char *storage);
int		check_exist_path(t_play playground_state, char **array);
//playground_utils
char	**flood_fill(t_play playground_state, char **array);
void	fill(char **array, t_play playground_state, int player_row, int player_column);
t_play	empty_playground();
// void 	write_playground(int fd, char **playground, int width);
t_play	update_command(t_data frontend_state, int newplayer_x, int newplayer_y);
t_play	get_playground_new_status(t_data frontend_state, char command);
char	validate_direction_command(int keycode);
// t_play	update_command(t_play playground_state, int newplayer_x, int newplayer_y);
t_play	empty_playground();
void	frontend_exit(t_data frontend_state, int code);
void	free_array(char **array);
void	array_playground_exit(char **array_playground, t_error error);

//test functions
void	test_read();
void	test_string_utils();
void	test_split();
void	test_playground_check();
void 	print_playground(t_play playground);

//frontend
t_data	start_game(t_play playground);
void	draw_map_background(t_data *image);
int		handle_command(int keycode, t_data *img);
int		final_exit(t_data *frontend_state);

//
t_play	get_playground(char *filepath);
int		string_playground_exit(char *string_playground, int code);
t_error	error(int code, char *message);
t_play	set_error(int code, char *message, t_play playground_state);

#endif
