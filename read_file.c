#include "so_long.h"

static int are_empty_lines(char *storage)
{
	int i;

	i = 0;
	while (storage[i])
	{
		if (storage[i + 1] && storage[i] == '\n' && storage[i + 1] == '\n')
			return (1);
		else if (storage[i] && (storage[i] != '1' || storage[i] != '0' || storage[i] != 'E' || storage[i] != 'C' || storage[i] != 'P'))
			return (1);
		i++;
	}
	return (0);
}

char	**read_file(char *filepath)
{
	int     BUFFER_SIZE = 5;
	int		fd;
	int		bytes_read;
	char	*buffer;
	char	*storage;
	char    **result;

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
	while (bytes_read > 0)
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
	if (are_empty_lines(storage))
		return (free(storage), printf("Error\n"), NULL);
	result = ft_split(storage, '\n');
	free(storage);
	if (!result)
		return (printf("Error\n"), NULL);
	close(fd);
	return (result);
}

void test_read()
{
	int i;
	// TODO handle file not exists AND don't have read permissions
	// spaces in the map should be an error, user should fix the map
	char **contents = read_file("./maps/test.ber");

	i = 0;
	while(contents[i])
	{
		printf("result: '%s'\n", contents[i]);
		i++;
	}
}
