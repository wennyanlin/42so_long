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
	// printf("command: %c\n", buffer[0]);
	command = buffer[0];
	free(buffer);
	return (command);
}

char	validate_direction_command(char command)
{
	if (command == 'W' || command == 'A' || command == 'S' || command == 'D')
		return (command);
	return (0);
}

t_play	get_playground_new_status(t_play playground_state, char command)
{
	int	x;
	int	y;

	x = playground_state.player_x;
	y = playground_state.player_y;
	if (command == 'W')
		playground_state = update_command(playground_state, (x - 1), y);
	else if (command == 'S')
		playground_state = update_command(playground_state, (x + 1), y);
	else if (command == 'A')
		playground_state = update_command(playground_state, x, (y - 1));
	else if (command == 'D')
		playground_state = update_command(playground_state, x, (y + 1));
	return (playground_state);
}

t_play	update_command(t_play playground_state, int newplayer_x, int newplayer_y)
{
	char	**playground;
	int		num_collectable;
	int		x;
	int		y;

	x = playground_state.player_x;
	y = playground_state.player_y;
	num_collectable = playground_state.num_collectable;
	playground = playground_state.playground;
	if (playground[newplayer_x][newplayer_y] == '0' || playground[newplayer_x][newplayer_y] == 'C'
		|| (playground[newplayer_x][newplayer_y] == 'E' && num_collectable == 0))
	{
		if (playground[newplayer_x][newplayer_y] == 'C')
			playground_state.num_collectable--;
		if (playground[newplayer_x][newplayer_y] == 'E' && num_collectable == 0)
			playground_state.is_exit_open = 1;
		playground[x][y] = '0';
		playground[newplayer_x][newplayer_y] = 'P';
		playground_state.player_x = newplayer_x;
		playground_state.player_y = newplayer_y;
	}
	return (playground_state);
}

int	main()
{
	// test_read();
	// test_string_utils();
	// test_split();
	// test_playground_check();
	// char	command;
	// char 	**arr;
	// t_play	playground_state;


	// arr = read_file("maps/playground_detail.ber");
	// playground_state = is_playground_shape_valid(arr);
	// playground_state.playground = arr;
	// while (playground_state.is_exit_open != 1)
	// {
	// 	write_playground(STDOUT_FILENO, playground_state.playground, 21);
	// 	command = validate_direction_command(read_direction_command(STDIN_FILENO));
	// 	printf("command before: '%c'\n", command);
	// 	playground_state = get_playground_new_status(playground_state, command);
	// 	printf("command after: '%c'\n", command);
	// 	print_playground(playground_state);
	// }
	start();
	/**
	 * read the map
	 * validate the map
	 *	- a valid route to exit
	 * play the game -DONE
	 * 	 - read the direction command -DONE
	 * 	 - validate the direction command -DONE
	 * 	 - if valid make the move -DONE
	 * 		- recieve correct command -DONE
	 * 		- update new playground state -DONE

	 * 	 - otherwise don't move
	 *   - update state
	 * 		- if on collectible, update collectible count
	 * 	 - if exit and no collectibles left, end the game
	 * 	 - if exit and there are collectible, you can't leave!
	*/
	return (0);
}
