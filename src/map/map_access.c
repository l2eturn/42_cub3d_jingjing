/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:54:33 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 14:56:10 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	map_is_wall(t_game *game, int x, int y)
{
	char	cell;

	if (x < 0 || y < 0)
		return (true);
	if (x >= game->scene.map.width || y >= game->scene.map.height)
		return (true);
	if (!game->scene.map.grid || !game->scene.map.grid[y])
		return (true);
	cell = game->scene.map.grid[y][x];
	return (cell == WALL || cell == SPACE);
}

bool	position_is_open(t_game *game, double x, double y)
{
	double	margin;

	margin = WALL_MARGIN;
	if (map_is_wall(game, (int)(x - margin), (int)(y - margin)))
		return (false);
	if (map_is_wall(game, (int)(x + margin), (int)(y - margin)))
		return (false);
	if (map_is_wall(game, (int)(x - margin), (int)(y + margin)))
		return (false);
	if (map_is_wall(game, (int)(x + margin), (int)(y + margin)))
		return (false);
	return (true);
}
