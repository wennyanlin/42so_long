#include "so_long.h"

//Before splitting the input playground string into an array of string, check for the empty lines, spaces and other non-related characters.
int are_empty_lines(char *storage)
{
	int i;

	i = 0;
	while (storage[i])
	{
		if (storage[i + 1] && storage[i] == NEWLINE && storage[i + 1] == NEWLINE)
			return (1);
		else if (storage[i] && (storage[i] != WALL && storage[i] != NEWLINE && storage[i] != PATH
					&& storage[i] != EXIT && storage[i] != COLLECTABLE && storage[i] != PLAYER))
			return (1);
		i++;
	}
	return (0);
}