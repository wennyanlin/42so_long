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
	playground[i] = NULL;
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
