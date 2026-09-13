/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarttapon <smarttapon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:12:04 by slimvutt          #+#    #+#             */
/*   Updated: 2026/08/24 17:57:38 by smarttapon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_sealed(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (false);
	return (map->grid[y][x] != SPACE);
}

static bool	cell_is_closed(t_map *map, int x, int y)
{
	char	cell;

	cell = map->grid[y][x];
	if (cell != WALKABLE && !is_direction(cell))
		return (true);
	return (is_sealed(map, x + 1, y) && is_sealed(map, x - 1, y)
		&& is_sealed(map, x, y + 1) && is_sealed(map, x, y - 1));
}

static bool	map_is_closed(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!cell_is_closed(map, x, y))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

static bool	find_player(t_map *map)
{
	int	x;
	int	y;
	int	found;

	found = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_direction(map->grid[y][x]))
				found++;
			x++;
		}
		y++;
	}
	if (found != 1)
		return (parse_error("Map needs exactly one player start"));
	return (true);
}

bool	validate_map(t_scene *scene)
{
	if (!find_player(&scene->map))
		return (false);
	if (!map_is_closed(&scene->map))
		return (parse_error("Map is not closed by walls"));
	return (true);
}
