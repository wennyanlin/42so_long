#include "so_long.h"

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


