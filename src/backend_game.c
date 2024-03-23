/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:06:15 by wlin              #+#    #+#             */
/*   Updated: 2024/03/23 16:06:41 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	validate_direction_command(int keycode)
{
	if (keycode == 13)
		return (UP);
	else if (keycode == 1)
		return (DOWN);
	else if (keycode == 0)
		return (LEFT);
	else if (keycode == 2)
		return (RIGHT);
	else if (keycode == 53)
		return (QUIT);
	return (0);
}

t_play	get_new_game_state(t_play game, char command)
{
	int	row;
	int	column;

	row = game.player_row;
	column = game.player_column;
	if (command == UP)
		game = move(game, (row - 1), column);
	else if (command == DOWN)
		game = move(game, (row + 1), column);
	else if (command == LEFT)
		game = move(game, row, (column - 1));
	else if (command == RIGHT)
		game = move(game, row, (column + 1));
	return (game);
}

int	can_move(t_play game, int newplayer_row, int newplayer_column)
{
	char	new_position;

	new_position = game.map[newplayer_row][newplayer_column];
	if (new_position == PATH || new_position == COLLECTABLE
		|| (new_position == EXIT && game.num_collectable == 0))
		return (POSITIVE);
	else
		return (INVALID);
}

void	update_player(t_play *game, int newplayer_row, int newplayer_column)
{
	game->map[game->player_row][game->player_column] = PATH;
	game->map[newplayer_row][newplayer_column] = PLAYER;
	game->player_row = newplayer_row;
	game->player_column = newplayer_column;
}

t_play	move(t_play game, int newplayer_row, int newplayer_column)
{
	char	**map;
	char	new_position;

	map = game.map;
	new_position = map[newplayer_row][newplayer_column];
	if (can_move(game, newplayer_row, newplayer_column) == POSITIVE)
	{
		if (new_position == EXIT && game.num_collectable == 0)
			game.game_state = PLAYER_WIN;
		else if (new_position == COLLECTABLE)
			game.num_collectable--;
		update_player(&game, newplayer_row, newplayer_column);
		ft_printf("You made: %i step/s\n", ++game.num_move);
	}
	return (game);
}
