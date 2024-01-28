#include "so_long.h"

/**
 * playground contains:
 * 	- 1 player
 * 	- 1 exit
 *  - at least one collectible
 * - make sure playground is rectangular (all rows same length) - DONE
 * - make sure playground is surrounded by walls
 * - make sure there is valid route for player to reach the exit
*/
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

void	test_playground_check()
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


	playground = read_file("maps/not_rectangle.ber");
	printf("\nShould return error code when playground is not a rectangle:\n");
	write_playground(STDOUT_FILENO, playground, 7);
	printf("expected: 0, actual result: %d\n", is_playground_shape_valid(playground));
}


