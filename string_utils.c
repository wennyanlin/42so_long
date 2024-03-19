#include "so_long.h"

int	string_contain(char *str, char target)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == target)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while(str[i])
		i++;
	return (i);
}

char *ft_strdup(char *src, int len)
{
	int		i;
	char 	*dest;

	i = -1;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	**ft_arraydup(char **array)
{
	int		i;
	char	**result;
	int		len_i;
	int		len_j;

	i = 0;
	if (!array || !array[i])
		return (NULL);
	while (array[i])
		i++;
	len_i = i;
	len_j = ft_strlen(array[0]);
	result = malloc(sizeof(char *) * (len_i + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (array[++i])
		result[i] = ft_strdup(array[i], len_j);
	result[i] = NULL;
	return (result);
}

void	fill(char **array, t_play playground_state, int player_row, int player_column)
{
	int	width = playground_state.width;
	int	height = playground_state.height;

	if (player_column < 0 || player_column >= width || player_row < 0 \
	|| player_row >= height || array[player_row][player_column] == '1')
		return ;
	array[player_row][player_column] = '1';
	fill(array, playground_state, player_row - 1, player_column);
	fill(array, playground_state, player_row + 1, player_column);
	fill(array, playground_state, player_row, player_column - 1);
	fill(array, playground_state, player_row, player_column + 1);
}

char	**flood_fill(t_play playground_state, char **array)
{
	char **array_to_fill;
	int	player_column;
	int	player_row;

	player_column = playground_state.player_column;
	player_row = playground_state.player_row;
	array_to_fill = ft_arraydup(array);
	fill(array_to_fill, playground_state, player_row, player_column);
	return (array_to_fill);
}

void	*free_space(char **reserved_space)
{
	if (*reserved_space)
	{
		free(*reserved_space);
		*reserved_space = NULL;
	}
	return (NULL);
}

char	*duplicate_storage(char *storage, char *buffer)
{
	char	*result;
	int		i;

	i = -1;
	if (!storage || !buffer)
		return (NULL);
	result = malloc(ft_strlen(storage) + ft_strlen(buffer) + 1);
	if (!result)
		return (free_space(&storage));
	while (storage[++i] != '\0')
		result[i] = storage[i];
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin(char *storage, char *buffer)
{
	char	*result;
	int		i;
	int		j;

	if (!storage)
	{
		storage = malloc(sizeof(char));
		if (!storage)
			return (NULL);
		storage[0] = '\0';
	}
	i = ft_strlen(storage);
	result = duplicate_storage(storage, buffer);
	if (!result)
		return (NULL);
	j = -1;
	while (buffer[++j] != '\0')
		result[i + j] = buffer[j];
	result[i + j] = '\0';
	free(storage);
	return (result);
}

// -g -fsanitize='address,undefined'
