/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:12:04 by slimvutt          #+#    #+#             */
/*   Updated: 2026/08/04 09:12:04 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Accepts " 220 " but rejects "22a", "" and "12 34": surrounding blanks
** are skipped, everything between them has to be a digit.
*/
static bool	is_number(char *part)
{
	int	i;
	int	digits;

	i = 0;
	digits = 0;
	while (part[i] == ' ' || part[i] == '\t')
		i++;
	while (ft_isdigit(part[i]))
	{
		digits++;
		i++;
	}
	while (part[i] == ' ' || part[i] == '\t' || part[i] == '\n')
		i++;
	return (digits > 0 && part[i] == '\0');
}

static bool	commas_are_valid(char *value)
{
	int	i;
	int	end;

	i = 0;
	while (value[i] == ' ' || value[i] == '\t')
		i++;
	if (value[i] == ',')
		return (false);
	end = 0;
	while (value[end])
		end++;
	end--;
	while (end >= 0 && (value[end] == ' ' || value[end] == '\t'
			|| value[end] == '\n'))
		end--;
	if (end >= 0 && value[end] == ',')
		return (false);
	while (value[i] && value[i] != '\n')
	{
		if (value[i] == ',' && value[i + 1] == ',')
			return (false);
		i++;
	}
	return (true);
}

static bool	has_three_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
		i++;
	return (i == 3);
}

static bool	fill_rgb(char **parts, t_rgb *color)
{
	int	value[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!is_number(parts[i]))
			return (false);
		value[i] = ft_atoi(parts[i]);
		if (value[i] < 0 || value[i] > 255)
			return (false);
		i++;
	}
	color->r = value[0];
	color->g = value[1];
	color->b = value[2];
	return (true);
}

/*
** r stays at -1 until a colour is stored, so it doubles as the
** "already seen this identifier" marker.
*/
bool	parse_color(t_rgb *color, char *value)
{
	char	**parts;
	bool	status;

	if (color->r != -1)
		return (parse_error("Duplicate F or C identifier"));
	if (!commas_are_valid(value))
		return (parse_error("Invalid colour, expected R,G,B in 0-255"));
	parts = ft_split(value, ',');
	if (!parts)
		return (parse_error("Colour allocation failed"));
	status = has_three_parts(parts) && fill_rgb(parts, color);
	free_arr(parts);
	if (!status)
		return (parse_error("Invalid colour, expected R,G,B in 0-255"));
	return (true);
}
