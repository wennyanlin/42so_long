/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:36:55 by wlin              #+#    #+#             */
/*   Updated: 2024/03/23 17:11:10 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_play	set_error(char *message, t_play game)
{
	game.error = message;
	return (game);
}

void	raw_map_exit(char *raw_map, char *error_message)
{
	if (raw_map)
		free(raw_map);
	ft_printf("Error\n%s\n", error_message);
	exit(EXIT_FAILURE);
}

void	map_exit(char **map, char *error_message)
{
	if (map && *map)
		free_array(map);
	ft_printf("Error\n%s\n", error_message);
	exit(EXIT_FAILURE);
}

void	quit_game(t_data state, int code)
{
	if (state.mlx)
		mlx_destroy_window(state.mlx, state.mlx_win);
	free_array(state.game.map);
	if (code == SUCCESS)
	{
		ft_printf(
			"\nIt’s money that makes the world go round!\n"
			"- Mr. Mini Krabs\n"
			"\nCongratulations!\n");
		exit(EXIT_SUCCESS);
	}
	else if (code == FAILURE)
	{
		ft_printf(
			"\nI’ll fill your life with misery and woe. Even if you quit."
			"\n- Mr. Mini Krabs\n\nYou lost!\n");
		exit(EXIT_FAILURE);
	}
}
