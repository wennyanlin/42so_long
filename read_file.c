#include "so_long.h"

typedef struct s_line
{
	char	*remaining_storage;
	char	*line;

}	t_line;

// char	*append_lines(char *buffer)
// {

// 	return (updated_lines);
// }



t_line	get_next_line(char *storage)
{
	t_line	line;
	int		i;
	int		newline_i;

    line.line = NULL;
	if (!storage)
		return (line);
	i = 0;
	newline_i = 0;
	while (storage[i])
	{
		if (storage[i] == '\n')
			newline_i = i;
		i++;
	}
	line.line = malloc(sizeof(char) * (newline_i + 1));
	if (!line.line)
		return (line);
	line.line = ft_strdup(storage, (newline_i));
	if (!line.line)
	{
		free(storage);
		return (line);
	}
	return (line);
}

char	*read_file(char *filepath)
{
	int     BUFFER_SIZE = 5;
	int		fd;
	int		bytes_read;
	char	*buffer;
	char	*storage;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (NULL);
	storage = malloc(sizeof(char));
	if (!storage)
		return (NULL);
	storage[0] = '\0';
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0 && string_contain(buffer, '\n') == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(storage);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		storage = ft_strjoin(storage, buffer);
	}
	free(buffer);
	close(fd);
	return (get_next_line(storage).line);

}

void test_read()
{
	printf("result: '%s'\n", read_file("./maps/test.txt"));
}
