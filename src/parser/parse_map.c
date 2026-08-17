/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:12:04 by slimvutt          #+#    #+#             */
/*   Updated: 2026/08/04 09:12:04 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Rows are collected in a list first because the map height is only
** known once the file ends. These copies use plain malloc and are
** released by ft_lstclear; the final grid gets its own memory.
*/
static bool	collect_line(t_list **lines, char *line, int *width)
{
	t_list	*node;
	char	*row;
	int		length;

	length = 0;
	while (line[length] && line[length] != '\n')
		length++;
	row = ft_calloc(length + 1, sizeof(char));
	if (!row)
		return (false);
	ft_memcpy(row, line, length);
	node = ft_lstnew(row);
	if (!node)
		return (free(row), false);
	ft_lstadd_back(lines, node);
	if (length > *width)
		*width = length;
	return (true);
}

static bool	only_trailing_blanks(int fd, char *line)
{
	while (line && is_blank_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		return (true);
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (false);
}

static bool	read_map_lines(int fd, t_list **lines, char *line, int *width)
{
	while (line)
	{
		if (is_blank_line(line))
		{
			if (only_trailing_blanks(fd, line))
				return (true);
			return (parse_error("Empty line inside map"));
		}
		if (!is_map_line(line))
			return (free(line), parse_error("Invalid character in map"));
		if (!collect_line(lines, line, width))
			return (free(line), parse_error("Map allocation failed"));
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}

/*
** Short rows are padded with spaces up to the widest row, so that
** map_is_wall() can index any x < width without reading past the
** end of a string. Spaces already count as walls for the renderer.
*/
static bool	build_grid(t_scene *scene, t_list *lines, int width)
{
	char	*row;
	int		y;

	scene->map.height = ft_lstsize(lines);
	scene->map.width = width;
	scene->map.grid = ft_safe_calloc(scene->map.height + 1,
			sizeof(char *), false);
	if (!scene->map.grid)
		return (false);
	y = 0;
	while (lines)
	{
		row = ft_safe_calloc(width + 1, sizeof(char), false);
		if (!row)
			return (false);
		ft_memset(row, SPACE, width);
		ft_memcpy(row, lines->content, ft_strlen(lines->content));
		scene->map.grid[y++] = row;
		lines = lines->next;
	}
	return (true);
}

bool	parse_map(int fd, t_scene *scene, char *first_line)
{
	t_list	*lines;
	int		width;
	bool	status;

	lines = NULL;
	width = 0;
	status = read_map_lines(fd, &lines, first_line, &width);
	if (status && !build_grid(scene, lines, width))
		status = parse_error("Map allocation failed");
	ft_lstclear(&lines, free);
	if (status && scene->map.height == 0)
		status = parse_error("Scene file has no map");
	return (status);
}
