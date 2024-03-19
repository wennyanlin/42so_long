#ifndef SO_LONG_H
# define SO_LONG_H

//MACROS
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
#define UNSET -1
#define POSITIVE 1
#define CLOSED 0
#define PLAYER_WIN 1
#define boat "./game_assets/boat.xpm"
#define sand "./game_assets/sand.xpm"
#define rock "./game_assets/rock.xpm"
#define money "./game_assets/money.xpm"
#define krab "./game_assets/crab.xpm"


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
typedef struct s_play
{
	char	**map;
	int 	width;
	int		height;
	int		player_row;
	int		player_column;
	int		is_exit_open;
	int 	num_collectable;
	int		num_move;
	int		game_state;
	char	*error;
}	t_play;

typedef struct s_data
{
	void	*img;
	void	*mlx;
	void	*mlx_win;
	int		width;
	int		height;
	t_play	game;
}	t_data;

//FUNCTION PROTOTYPES
//string_utils
size_t	ft_strlen(char *s);
char	*duplicate_storage(char *storage, char *buffer);
char	*ft_strjoin(char *str1, char *str2);
char	**ft_split(char *str, char seperator);
char 	*ft_strdup(char *src, int len);
void	free_array(char **array);
char	**ft_arraydup(char **array);

//read_file
char	*read_map_file(char *filepath);

//game_check
t_play	validate_game(char **arr);
void	validate_map_objects(char **arr, t_play *game, int row, int column);
void	validate_map_border(char **arr, t_play *game, int row);
int 	are_empty_lines(char *storage);
int		check_exist_path(t_play game, char **array);

//game_utils
char	**flood_fill(t_play game, char **array);
void	fill(char **array, t_play game, int player_row, int player_column);
t_play	empty_game();
t_play	move(t_play game, int newplayer_x, int newplayer_y);
t_play	get_new_game_state(t_play game, char command);
char	validate_direction_command(int keycode);
t_play	empty_game();
void	quit_game(t_data state, int code);

//frontend
t_data	start_game(t_play game);
void	draw_map_background(t_data *image);
void	draw_tile(t_data *state, char **map, int row, int column);
int		handle_command(int keycode, t_data *img);

//
t_play	parse_map(char *filepath);
void	raw_map_exit(char *raw_map, char *error_message);
void	map_exit(char **map, char *error_message);
t_play	set_error(char *message, t_play game);
int		check_file_extension(char *str);
int		press_x_exit(t_data *state);
#endif
