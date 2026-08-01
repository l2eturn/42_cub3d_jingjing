/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:58:55 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 15:23:54 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	texture_load_all(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		game->texture[i] = mlx_load_png(
				game->scene.texture_path[i]);
		if (!game->texture[i])
			return (false);
		i++;
	}
	return (true);
}
