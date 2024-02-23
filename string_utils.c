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

// char	*ft_strdup(char *str, int len)
// {
// 	int		i;
// 	char	*result;

// 	if (!str)
// 		return (NULL);

// 	i = 0;
// 	result = malloc(sizeof(char) * (len + 1));
// 	if (!result)
// 		return (NULL);
// 	while (str[i] && i < len)
// 	{
// 		result[i] = str[i];
// 		i++;
// 	}
// 	result[i] = '\0';
// 	return (result);
// }

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
