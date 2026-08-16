/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 13:46:58 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/16 16:42:00 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	print_error(char *message)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (EXIT_FAILURE);
}

static void	how_to_play(t_game *game)
{
	mlx_put_string(game->mlx, "Controls", 10, 10);
	mlx_put_string(game->mlx, "W / S : walk forward / backward", 10, 30);
	mlx_put_string(game->mlx, "A / D : strafe left / right", 10, 50);
	mlx_put_string(game->mlx, "<- / ->, Q / E : turn the camera", 10, 70);
	mlx_put_string(game->mlx, "ESC : quit", 10, 90);
}

static int	run_game(t_game *game)
{
	if (!player_init(game))
		return (print_error("Invalid player configuration"));
	if (!graphics_init(game))
	{
		graphics_destroy(game);
		return (print_error("Graphics initialization failed"));
	}
	how_to_play(game);
	mlx_loop_hook(game->mlx, render_loop, game);
	mlx_loop(game->mlx);
	graphics_destroy(game);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		status;

	if (argc != 2)
		return (print_error("Usage: ./cub3D <map.cub>"));
	if (WIDTH < MIN_WIDTH || HEIGHT < MIN_HEIGHT)
		return (print_error("WIDTH and HEIGHT must be >= MIN_WIDTH and MIN_HEIGHT"));
	ft_bzero(&game, sizeof(game));
	if (!parse_scene(argv[1], &game.scene))
	{
		ft_safe_calloc(0, 0, true);
		return (EXIT_FAILURE);
	}
	status = run_game(&game);
	ft_safe_calloc(0, 0, true);
	return (status);
}
