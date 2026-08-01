/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 13:46:58 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 15:23:19 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	print_error(char *message)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (EXIT_FAILURE);
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
	ft_bzero(&game, sizeof(game));
	if (!parse_scene(argv[1], &game.scene))
	{
		ft_safe_calloc(0, 0, true);
		return (print_error("Failed to parse scene"));
	}
	status = run_game(&game);
	ft_safe_calloc(0, 0, true);
	return (status);
}
