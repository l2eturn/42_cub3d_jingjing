/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarttapon.lim@gmail.com <terx13>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:12:04 by smarttapon.       #+#    #+#             */
/*   Updated: 2026/08/04 09:12:04 by smarttapon.      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	store_texture(t_scene *scene, char *value, int index)
{
	char	*path;
	size_t	length;

	if (scene->texture_path[index])
		return (parse_error("Duplicate texture identifier"));
	while (*value == ' ' || *value == '\t')
		value++;
	length = ft_strlen(value);
	while (length > 0 && (value[length - 1] == '\n'
			|| value[length - 1] == ' ' || value[length - 1] == '\t'))
		length--;
	if (length == 0)
		return (parse_error("Empty texture path"));
	path = ft_safe_calloc(length + 1, sizeof(char), false);
	if (!path)
		return (parse_error("Texture path allocation failed"));
	ft_memcpy(path, value, length);
	scene->texture_path[index] = path;
	return (true);
}

static int	texture_index(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (TEX_NO);
	if (ft_strncmp(line, "SO", 2) == 0)
		return (TEX_SO);
	if (ft_strncmp(line, "WE", 2) == 0)
		return (TEX_WE);
	if (ft_strncmp(line, "EA", 2) == 0)
		return (TEX_EA);
	return (-1);
}

/*
** The blank after the identifier matters: without it "NOPE ./x.png"
** would be read as a north texture called "PE ./x.png".
*/
static bool	parse_element_line(t_scene *scene, char *line)
{
	int	index;

	while (*line == ' ' || *line == '\t')
		line++;
	index = texture_index(line);
	if (index >= 0 && (line[2] == ' ' || line[2] == '\t'))
		return (store_texture(scene, line + 2, index));
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_color(&scene->floor, line + 1));
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_color(&scene->ceiling, line + 1));
	return (parse_error("Unknown identifier in scene file"));
}

bool	elements_complete(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (!scene->texture_path[i])
			return (parse_error("Missing NO, SO, WE or EA texture"));
		i++;
	}
	if (scene->floor.r == -1 || scene->ceiling.r == -1)
		return (parse_error("Missing F or C colour"));
	return (true);
}

/*
** Stops at the first map row and hands it back through first_map_line:
** get_next_line cannot rewind, so dropping that row would lose it.
*/
bool	parse_elements(int fd, t_scene *scene, char **first_map_line)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
		{
			*first_map_line = line;
			return (true);
		}
		if (!is_blank_line(line) && !parse_element_line(scene, line))
			return (free(line), false);
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}
