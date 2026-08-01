/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:58:01 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 14:58:05 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	player_try_move(t_game *game, double dx, double dy)
{
	double	next_x;
	double	next_y;

	next_x = game->player.x + dx;
	next_y = game->player.y + dy;
	if (position_is_open(game, next_x, game->player.y))
		game->player.x = next_x;
	if (position_is_open(game, game->player.x, next_y))
		game->player.y = next_y;
}
