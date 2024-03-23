/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:44:26 by wlin              #+#    #+#             */
/*   Updated: 2024/03/23 20:28:16 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	validate_path(GAME_ASSETS_FOLDER);
	validate_path(BOAT);
	validate_path(SAND);
	validate_path(ROCK);
	validate_path(MONEY);
	validate_path(KRAB);
}

int	main(int argc, char **argv)
{
	t_play	game;
	t_data	state;
	char	*filepath;

	if (argc == 1)
		write(2, RED "Error\nGame needed a map.\n" DEF, 40);
	else if (argc > 2)
		write(2, RED "Error\nToo many arguments\n" DEF, 40);
	else
	{
		validate_game_assets();
		filepath = argv[1];
		game = parse_map(filepath);
		state = start_game(game);
		quit_game(state, SUCCESS);
	}
	return (EXIT_FAILURE);
}
