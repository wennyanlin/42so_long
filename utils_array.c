#include "so_long.h"

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
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

void	fill(char **array, t_play game, int player_row, int player_column)
{
	int	width = game.width;
	int	height = game.height;

	if (player_column < 0 || player_column >= width || player_row < 0 \
	|| player_row >= height || array[player_row][player_column] == '1')
		return ;
	array[player_row][player_column] = '1';
	fill(array, game, player_row - 1, player_column);
	fill(array, game, player_row + 1, player_column);
	fill(array, game, player_row, player_column - 1);
	fill(array, game, player_row, player_column + 1);
}

char	**flood_fill(t_play game, char **array)
{
	char **array_to_fill;
	int	player_column;
	int	player_row;

	player_column = game.player_column;
	player_row = game.player_row;
	array_to_fill = ft_arraydup(array);
	fill(array_to_fill, game, player_row, player_column);
	return (array_to_fill);
}
