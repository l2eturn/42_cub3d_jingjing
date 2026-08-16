/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 14:58:29 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/16 16:28:59 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	move_forward(t_game *game, double speed)
{
	player_try_move(game, game->player.dir_x * speed,
		game->player.dir_y * speed);
}

static void	move_sideways(t_game *game, double speed)
{
	player_try_move(game, -game->player.dir_y * speed,
		game->player.dir_x * speed);
}

void	player_input(t_game *game)
{
	double	move;
	double	rotation;

	move = game->mlx->delta_time * MOVE_SPEED;
	rotation = game->mlx->delta_time * ROT_SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game, move);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_forward(game, -move);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_sideways(game, move);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_sideways(game, -move);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player_rotate(game, rotation);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		player_rotate(game, -rotation);
	if (mlx_is_key_down(game->mlx, MLX_KEY_E))
		player_rotate(game, rotation);
	if (mlx_is_key_down(game->mlx, MLX_KEY_Q))
		player_rotate(game, -rotation);
}
