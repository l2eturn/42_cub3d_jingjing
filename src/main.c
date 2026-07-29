#include "cub3d.h"

/*
 * ลำดับสำคัญ: parse → validate → init → render → loop → cleanup
 * ห้าม init MLX / render ก่อนที่ map จะ valid (design rule)
 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (write(2, "Error\nUsage: ./cub3D <map.cub>\n", 30), 1);
	memset(&game, 0, sizeof(t_game));
	if (parse_cub(&game, argv[1]) != 0)
		return (cleanup_exit(&game, NULL, 1));
	if (validate_map(&game) != 0)
		return (cleanup_exit(&game, NULL, 1));
	if (init_mlx(&game) != 0)
		return (cleanup_exit(&game, NULL, 1));
	if (load_textures(&game) != 0)
		return (cleanup_exit(&game, NULL, 1));
	/* TODO: mlx_key_hook(game.mlx.mlx, key_hook, &game); */
	/* TODO: mlx_loop_hook(game.mlx.mlx, loop_hook, &game); */
	/* TODO: mlx_loop(game.mlx.mlx); */
	return (cleanup_exit(&game, NULL, 0));
}
