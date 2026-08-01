/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:56:37 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 14:56:42 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	ray_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (TEX_WE);
		return (TEX_EA);
	}
	if (ray->step_y > 0)
		return (TEX_NO);
	return (TEX_SO);
}

void	ray_set_texture(t_game *game, t_ray *ray)
{
	double	wall_x;
	int		index;

	index = ray_texture_index(ray);
	ray->texture = game->texture[index];
	if (ray->side == 0)
		wall_x = game->player.y + ray->wall_dist * ray->dir_y;
	else
		wall_x = game->player.x + ray->wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	ray->texture_x = (int)(wall_x * ray->texture->width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->texture_x = ray->texture->width - ray->texture_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->texture_x = ray->texture->width - ray->texture_x - 1;
	ray->texture_step = (double)ray->texture->height
		/ ray->line_height;
	ray->texture_pos = (ray->draw_start - HEIGHT / 2.0
			+ ray->line_height / 2.0) * ray->texture_step;
}
