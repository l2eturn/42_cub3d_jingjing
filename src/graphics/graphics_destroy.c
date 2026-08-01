/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:59:19 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 15:22:58 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	graphics_destroy(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < TEX_COUNT)
	{
		if (game->texture[i])
		{
			mlx_delete_texture(game->texture[i]);
			game->texture[i] = NULL;
		}
		i++;
	}
	if (game->mlx && game->image)
	{
		mlx_delete_image(game->mlx, game->image);
		game->image = NULL;
	}
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
}
