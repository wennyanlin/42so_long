#include "so_long.h"

int	main(int argc, char **argv)
{
	t_play	game;
	t_data	state;
	char 	*filepath;

	if (argc != 2)
		return (0);
	filepath = argv[1];
	game = parse_map(filepath);
	state = start_game(game);
	quit_game(state, exit_success);
	return (0);
}
