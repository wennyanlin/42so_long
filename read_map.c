#include "so_long.h"

int	check_file_extension(char *str)
{
	int	len;
	int	i;
	char *tmp;
	char *ref;

	ref = ".ber";
	i = -1;
	tmp = str;
	len = ft_strlen(str);
	while (++i < (len - 4))
		tmp++;
	i = -1;
	while (tmp[++i])
	{
		if (tmp[i] != ref[i])
			return (INVALID);
	}
	return (POSITIVE);
}

//read and append all btytes from the input file
char *read_all_bytes(int fd, int BUFFER_SIZE, char *buffer, char *storage)
{
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == UNSET)
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

	if (check_file_extension(filepath) == INVALID)
	{
		ft_printf("Error\nNot a valid file type\n");
		exit(EXIT_FAILURE);
	}

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
