/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarttapon <smarttapon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:12:04 by slimvutt          #+#    #+#             */
/*   Updated: 2026/09/13 16:48:15 by smarttapon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	has_cub_extension(char *filename)
{
	size_t	length;

	length = ft_strlen(filename);
	if (length < 5)
		return (false);
	return (ft_strncmp(filename + length - 4, ".cub", 4) == 0);
}

static void	scene_init(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
		scene->texture_path[i++] = NULL;
	scene->floor.r = -1;
	scene->ceiling.r = -1;
	scene->map.grid = NULL;
	scene->map.width = 0;
	scene->map.height = 0;
}

static bool	parse_sections(int fd, t_scene *scene)
{
	char	*first_map_line;

	first_map_line = NULL;
	if (!parse_elements(fd, scene, &first_map_line))
		return (free(first_map_line), false);
	if (!elements_complete(scene))
		return (free(first_map_line), false);
	if (!first_map_line)
		return (parse_error("Scene file has no map"));
	if (!parse_map(fd, scene, first_map_line))
		return (false);
	return (validate_map(scene));
}

static void	free_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

bool	parse_scene(char *filename, t_scene *scene)
{
	int		fd;
	bool	status;

	if (!filename || !scene)
		return (false);
	scene_init(scene);
	if (!has_cub_extension(filename))
		return (parse_error("Scene file must end with .cub"));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (parse_error("Cannot open scene file"));
	status = parse_sections(fd, scene);
	if (!status)
		free_gnl(fd);
	close(fd);
	return (status);
}
