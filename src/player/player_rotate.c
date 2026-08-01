/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:58:14 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 14:58:18 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	player_rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cosine;
	double	sine;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	cosine = cos(angle);
	sine = sin(angle);
	game->player.dir_x = old_dir_x * cosine
		- game->player.dir_y * sine;
	game->player.dir_y = old_dir_x * sine
		+ game->player.dir_y * cosine;
	game->player.plane_x = old_plane_x * cosine
		- game->player.plane_y * sine;
	game->player.plane_y = old_plane_x * sine
		+ game->player.plane_y * cosine;
}
