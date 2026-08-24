/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarttapon <smarttapon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:57:20 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/20 19:16:55 by smarttapon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		ray_init(game, &ray, x);
		ray_dda(game, &ray);
		ray_project(&ray);
		ray_set_texture(game, &ray);
		draw_column(game, &ray, x);
		x++;
	}
}

void	render_loop(void *parameter)
{
	t_game	*game;

	game = parameter;
	player_input(game);
	render_frame(game);
}
