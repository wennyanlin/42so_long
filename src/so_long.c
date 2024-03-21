#include "so_long.h"

void	validate_path(char *xpm)
{
	if (open(xpm, O_RDONLY) == -1)
	{
		ft_printf("Error\nResource path incorrect\n");
		exit(EXIT_FAILURE);
	}
}

void	validate_game_assets(void)
{
	validate_path(game_assets_folder);
	validate_path(boat);
	validate_path(sand);
	validate_path(rock);
	validate_path(money);
	validate_path(krab);
}

int	main(int argc, char **argv)
{
	t_play	game;
	t_data	state;
	char 	*filepath;

	if (argc != 2)
	{
		ft_printf("Error\nGame needed a map.\n");
		return (0);
	}
	validate_game_assets();
	filepath = argv[1];
	game = parse_map(filepath);
	state = start_game(game);
	quit_game(state, exit_success);
	return (0);
}
