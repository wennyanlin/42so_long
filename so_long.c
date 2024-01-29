#include "so_long.h"
//handle input is more than 1 characters
char	read_direction_command(int input_fd)
{
	char	*buffer;
	char	command;

	buffer = malloc(sizeof(char) * 2);
	if (!buffer)
		return (0);
	read(input_fd, buffer, 1);
	printf("command: %c\n", buffer[0]);
	command = buffer[0];
	free(buffer);
	return (command);
}

int	main()
{
	// test_read();
	// test_string_utils();
	// test_split();
	// test_playground_check();
	read_direction_command(STDIN_FILENO);

	/**
	 * read the map
	 * validate the map
	 *	- a valid route to exit
	 * play the game
	 * 	 - read the direction command
	 * 	 - validate the direction command
	 * 	 - if valid make the move
	 * 	 - otherwise don't move
	 *   - update state
	 * 		- if on collectible, update collectible count
	 * 	 - if exit and no collectibles left, end the game
	 * 	 - if exit and there are collectible, you can't leave!
	*/
	return (0);
}
