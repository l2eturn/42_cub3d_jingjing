/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:12:04 by slimvutt          #+#    #+#             */
/*   Updated: 2026/08/04 09:12:04 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	parse_error(char *message)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (false);
}

bool	is_direction(char c)
{
	return (c == N || c == S || c == E || c == W);
}

bool	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

/*
** A map row holds only map characters and at least one cell (0 or 1).
** The cell requirement is what keeps an identifier line such as
** "NO ./wall.png" from being mistaken for the start of the map.
*/
bool	is_map_line(char *line)
{
	int		i;
	bool	has_cell;

	i = 0;
	has_cell = false;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == WALL || line[i] == WALKABLE)
			has_cell = true;
		else if (!is_direction(line[i]) && line[i] != SPACE)
			return (false);
		i++;
	}
	return (has_cell);
}
