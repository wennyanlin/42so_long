#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_play
{
	char	*storage;
	int		cursor;

}	t_play;

size_t	ft_strlen(char *str);
int		string_contain(char *str, char target);
char	*ft_strjoin(char *str1, char *str2);

#endif
