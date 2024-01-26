#include "so_long.h"

char **buildPlayground(int height, int width)
{
	char **playground;
	int i = 0;
	int	j = 0;

	playground = malloc((sizeof(char*)) * (height + 1));
	if (!playground)
		return (NULL);
	while (i < height)
	{
        playground[i] = malloc(sizeof(char) * (width + 1));
		if (!playground[i])
			return (NULL);

		if (i == 0 || i == (height - 1))
		{
			j = 0;
			while (j < width)
				playground[i][j++] = '1';
		}
		else
		{
			playground[i][0] = '1';
			playground[i][width - 1] = '1';
			j = 1;
			while (j != 0 && j != (width - 1))
			{
				playground[i][j++] = '0';
			}
		}
		playground[i][width] = '\0';
		i++;
	}
	return (playground);
}

void write_playground(int fd, char **playground, int width)
{
	int i = 0;

	while(playground[i])
	{
		write(fd, playground[i], width);
		write(fd, "\n", 1);
		i++;
	}
}

int	is_playground_shape_valid(char **arr)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	j = 0;
	width = 0;
	while (arr[i])
	{
		while (arr[i][j])
			j++;
		if (i == 0)
			width = j;
		if (j != width)
			return (0);
		i++;
	}
	if (i < 3 || width < 3)
		return (0);
	return (1);
}


// char	*read_file(char *filepath)
// {
// 	int	fd;

// 	fd = open(filepath, O_CREAT | O_RDWR);
// 	if (fd == -1)
// 		return (NULL);

// }

int	main()
{
	char **playground = buildPlayground(3, 4);
	printf("\nShould return success when playground is valid:\n");
	write_playground(STDOUT_FILENO, playground, 4);
	printf("expected: 1, actual result: %d\n", is_playground_shape_valid(playground));

	printf("\n");
	playground = buildPlayground(4, 2);
	printf("\nShould return error code when playground width is invalid:\n");
	write_playground(STDOUT_FILENO, playground, 2);
	printf("expected: 0, actual result: %d\n", is_playground_shape_valid(playground));

	playground = buildPlayground(2, 4);
	printf("\nShould return error code when playground height is invalid:\n");
	write_playground(STDOUT_FILENO, playground, 4);
	printf("expected: 0, actual result: %d\n", is_playground_shape_valid(playground));
}


