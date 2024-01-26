#include "so_long.h"

typedef struct s_line
{
	char	*storage;
	char	*line;

}	t_line;

// char	*append_lines(char *buffer)
// {

// 	return (updated_lines);
// }



// t_line	get_next_line(char *storage)
// {

// 	return ();
// }

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	int		str1_len;
	int		str2_len;
	char	*result;

	i = 0;
	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	result = malloc(sizeof(char) * (str1_len + str2_len + 1));
	if (!result)
		return (NULL);
	str1_len = 0;
	str2_len = 0;
	while (str1[str1_len])
		result[i++] = str1[str1_len++];
	while (str2[str2_len])
		result[i++] = str2[str2_len++];
	result[i] = '\0';
	return (result);
}

int	string_contain(char *str, char target)
{
	int	i;

	i = 0;
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

char	*read_file(char *filepath)
{
	int		fd;
	int		bytes_read;
	char	buffer[4];
	char	*storage;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && string_contain(buffer, '\n') == 0)
	{
		bytes_read = read(fd, buffer, 3);
		printf("\n----\n\nread '%d' bytes, content read: '%s'\n\n-----\n", bytes_read, buffer);
		if (bytes_read == -1)
		{
			// free(buffer);
			free(storage);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		storage = ft_strjoin(storage, buffer);
	}
	close(fd);
	// free(buffer);
	return (storage);
}

int	main()
{
	printf("result: '%s'\n", read_file("./Makefile"));
}
