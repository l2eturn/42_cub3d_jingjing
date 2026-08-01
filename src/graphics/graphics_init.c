/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:59:07 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 14:59:10 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	graphics_init(t_game *game)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	game->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	if (!game->mlx)
		return (false);
	if (!texture_load_all(game))
		return (false);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		return (false);
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) < 0)
		return (false);
	return (true);
}
