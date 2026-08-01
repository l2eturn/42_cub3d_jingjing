/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 15:00:52 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 15:08:28 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static const char	g_test_map[10][11] = {
	"1111111111",
	"1000010001",
	"1001000001",
	"1000000001",
	"1000000001",
	"10100N1001",
	"1000000001",
	"1010001001",
	"1000000001",
	"1111111111"
};

static char	*safe_strdup(const char *source)
{
	char	*copy;
	size_t	length;

	length = ft_strlen(source);
	copy = ft_safe_calloc(length + 1, sizeof(char), false);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, source, length);
	return (copy);
}

static bool	allocate_test_map(t_scene *scene)
{
	int	y;

	scene->map.width = 10;
	scene->map.height = 10;
	scene->map.grid = ft_safe_calloc(11, sizeof(char *), false);
	if (!scene->map.grid)
		return (false);
	y = 0;
	while (y < scene->map.height)
	{
		scene->map.grid[y] = ft_safe_calloc(11, sizeof(char), false);
		if (!scene->map.grid[y])
			return (false);
		ft_memcpy(scene->map.grid[y], g_test_map[y], 10);
		y++;
	}
	return (true);
}

static bool	allocate_texture_paths(t_scene *scene)
{
	scene->texture_path[TEX_NO] = safe_strdup("textures/wall_1.png");
	scene->texture_path[TEX_SO] = safe_strdup("textures/wall_2.png");
	scene->texture_path[TEX_WE] = safe_strdup("textures/wall_3.png");
	scene->texture_path[TEX_EA] = safe_strdup("textures/wall_4.png");
	if (!scene->texture_path[TEX_NO] || !scene->texture_path[TEX_SO])
		return (false);
	if (!scene->texture_path[TEX_WE] || !scene->texture_path[TEX_EA])
		return (false);
	return (true);
}

static void	set_test_colors(t_scene *scene)
{
	scene->floor.r = 50;
	scene->floor.g = 50;
	scene->floor.b = 50;
	scene->ceiling.r = 100;
	scene->ceiling.g = 150;
	scene->ceiling.b = 200;
}

bool	parse_scene(char *filename, t_scene *scene)
{
	(void)filename;
	if (!scene)
		return (false);
	if (!allocate_test_map(scene))
		return (false);
	if (!allocate_texture_paths(scene))
		return (false);
	set_test_colors(scene);
	return (true);
}
