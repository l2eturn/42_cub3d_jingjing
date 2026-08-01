/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:56:59 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 14:57:03 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static uint32_t	texture_color(mlx_texture_t *texture,
		int x, int y, int shade)
{
	size_t	index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	index = (y * texture->width + x) * texture->bytes_per_pixel;
	r = texture->pixels[index];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	a = ALPHA;
	if (texture->bytes_per_pixel > 3)
		a = texture->pixels[index + 3];
	if (shade)
		return (get_rgba(r / 2, g / 2, b / 2, a));
	return (get_rgba(r, g, b, a));
}

static void	draw_ceiling(t_game *game, int x, int end)
{
	int			y;
	uint32_t	color;

	y = 0;
	color = get_rgba(game->scene.ceiling.r, game->scene.ceiling.g,
			game->scene.ceiling.b, ALPHA);
	while (y < end)
	{
		mlx_put_pixel(game->image, x, y, color);
		y++;
	}
}

static void	draw_floor(t_game *game, int x, int start)
{
	int			y;
	uint32_t	color;

	y = start;
	color = get_rgba(game->scene.floor.r, game->scene.floor.g,
			game->scene.floor.b, ALPHA);
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->image, x, y, color);
		y++;
	}
}

static void	draw_wall(t_game *game, t_ray *ray, int x)
{
	int			y;
	int			texture_y;
	uint32_t	color;

	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		texture_y = (int)ray->texture_pos;
		ray->texture_pos += ray->texture_step;
		if (texture_y < 0)
			texture_y = 0;
		if (texture_y >= (int)ray->texture->height)
			texture_y = ray->texture->height - 1;
		color = texture_color(ray->texture, ray->texture_x,
				texture_y, ray->side == 1);
		mlx_put_pixel(game->image, x, y, color);
		y++;
	}
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	draw_ceiling(game, x, ray->draw_start);
	draw_wall(game, ray, x);
	draw_floor(game, x, ray->draw_end + 1);
}
