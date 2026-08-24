/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarttapon <smarttapon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:12:04 by slimvutt          #+#    #+#             */
/*   Updated: 2026/08/24 17:57:33 by smarttapon       ###   ########.fr       */
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
