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

static bool	push_neighbour(t_map *map, t_flood *state,
		int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (false);
	if (state->visited[y][x])
		return (true);
	if (map->grid[y][x] == SPACE)
		return (false);
	if (map->grid[y][x] == WALL)
		return (true);
	state->visited[y][x] = 1;
	state->stack[state->top].x = x;
	state->stack[state->top].y = y;
	state->top++;
	return (true);
}

static bool	flood_fill(t_map *map, t_flood *state,
		int start_x, int start_y)
{
	t_point	current;

	state->top = 0;
	state->visited[start_y][start_x] = 1;
	state->stack[state->top++] = (t_point){start_x, start_y};
	while (state->top > 0)
	{
		current = state->stack[--state->top];
		if (!push_neighbour(map, state,
				current.x + 1, current.y))
			return (false);
		if (!push_neighbour(map, state,
				current.x - 1, current.y))
			return (false);
		if (!push_neighbour(map, state,
				current.x, current.y + 1))
			return (false);
		if (!push_neighbour(map, state,
				current.x, current.y - 1))
			return (false);
	}
	return (true);
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
	t_point	*stack;
	t_flood	state;
	int		px;
	int		py;

	px = 0;
	py = 0;
	if (!find_player(&scene->map, &px, &py))
		return (false);
	visited = alloc_visited(&scene->map);
	if (!visited)
		return (parse_error("Validation allocation failed"));
	stack = ft_safe_calloc((size_t)scene->map.width
			* scene->map.height, sizeof(t_point), false);
	if (!stack)
		return (parse_error("Validation allocation failed"));
	state.visited = visited;
	state.stack = stack;
	if (!flood_fill(&scene->map, &state, px, py))
		return (parse_error("Map is not closed by walls"));
	return (true);
}
