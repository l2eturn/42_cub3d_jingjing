/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:12:04 by slimvutt          #+#    #+#             */
/*   Updated: 2026/08/04 09:12:04 by slimvutt         ###   ########.fr       */
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

/*
** -1 in the red channel marks a colour that has not been read yet,
** which both elements_complete() and parse_color() rely on.
*/
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

/*
** The file is read straight through once: identifiers first, then the
** map, which is why the map has to be the last block in the file.
*/
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
	close(fd);
	return (status);
}
