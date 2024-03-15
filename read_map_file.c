#include "so_long.h"

//read and append all btytes from the input file
char *read_all_bytes(int fd, int BUFFER_SIZE, char *buffer, char *storage)
{
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == NEGATIVE)
		{
			free(storage);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		storage = ft_strjoin(storage, buffer);
	}
	close(fd);
	free(buffer);
	return (storage);
}

char	*read_map_file(char *filepath)
{
	int     BUFFER_SIZE = 5;
	int		fd;
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
	storage = read_all_bytes(fd, BUFFER_SIZE, buffer, storage);
	return (storage);
}

// void test_read()
// {
// 	int i;
// 	// TODO handle file not exists AND don't have read permissions
// 	// spaces in the map should be an error, user should fix the map
// 	char *contents = read_file("./maps/test.ber");
// 	i = 0;
// 	while(contents[i])
// 	{
// 		printf("result: '%s'\n", contents[i]);
// 		i++;
// 	}
// }
