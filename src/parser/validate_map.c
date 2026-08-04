/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarttapon.lim@gmail.com <terx13>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:12:04 by smarttapon.       #+#    #+#             */
/*   Updated: 2026/08/04 09:12:04 by smarttapon.      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**alloc_visited(t_map *map)
{
	char	**visited;
	int		y;

	visited = ft_safe_calloc(map->height, sizeof(char *), false);
	if (!visited)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		visited[y] = ft_safe_calloc(map->width, sizeof(char), false);
		if (!visited[y])
			return (NULL);
		y++;
	}
	return (visited);
}

/*
** Spreads out from the player over every reachable cell. Falling off
** the grid, or stepping onto a padded space, means the walls do not
** enclose the player, so the map is open. Walls stop the spread.
*/
static bool	flood_fill(t_map *map, char **visited, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (false);
	if (visited[y][x])
		return (true);
	visited[y][x] = 1;
	if (map->grid[y][x] == WALL)
		return (true);
	if (map->grid[y][x] == SPACE)
		return (false);
	if (!flood_fill(map, visited, x + 1, y))
		return (false);
	if (!flood_fill(map, visited, x - 1, y))
		return (false);
	if (!flood_fill(map, visited, x, y + 1))
		return (false);
	return (flood_fill(map, visited, x, y - 1));
}

static bool	find_player(t_map *map, int *px, int *py)
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
			{
				found++;
				*px = x;
				*py = y;
			}
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
	char	**visited;
	int		px;
	int		py;

	px = 0;
	py = 0;
	if (!find_player(&scene->map, &px, &py))
		return (false);
	visited = alloc_visited(&scene->map);
	if (!visited)
		return (parse_error("Validation allocation failed"));
	if (!flood_fill(&scene->map, visited, px, py))
		return (parse_error("Map is not closed by walls"));
	return (true);
}
