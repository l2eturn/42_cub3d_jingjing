/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:57:49 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 16:02:12 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_direction(t_game *game, char direction)
{
	if (direction == N)
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (direction == S)
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (direction == E)
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	else if (direction == W)
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
}

static bool	is_player_direction(char cell)
{
	return (cell == N || cell == S || cell == E || cell == W);
}

static void	set_player(t_game *game, int x, int y, char direction)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	set_direction(game, direction);
	game->player.plane_x = -game->player.dir_y * CAMERA_PLANE;
	game->player.plane_y = game->player.dir_x * CAMERA_PLANE;
	game->scene.map.grid[y][x] = WALKABLE;
}

bool	player_init(t_game *game)
{
	int		x;
	int		y;
	char	cell;

	y = 0;
	while (y < game->scene.map.height)
	{
		x = 0;
		while (x < game->scene.map.width)
		{
			cell = game->scene.map.grid[y][x];
			if (is_player_direction(cell))
				return (set_player(game, x, y, cell), true);
			x++;
		}
		y++;
	}
	return (false);
}
