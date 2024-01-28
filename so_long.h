#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_play
{
	char	*playground;
	int 	width;
	int 	num_collectable;
	int		is_exit_open;
	int		player_x;
	int		player_y;
}	t_play;

//string_utils
size_t	ft_strlen(char *str);
int		string_contain(char *str, char target);
char	*ft_strdup(char *str, int len);
char	*ft_strjoin(char *str1, char *str2);
char	**ft_split(char *str, char seperator);

//read_file
char	**read_file(char *filepath);

//playground_check
int		is_playground_shape_valid(char **arr);

//playground_utils
char 	**buildPlayground(int height, int width);
void 	write_playground(int fd, char **playground, int width);

//test functions
void	test_read();
void	test_string_utils();
void	test_split();
void	test_playground_check();


#endif
