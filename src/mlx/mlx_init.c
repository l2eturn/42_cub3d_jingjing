#include "cub3d.h"

/*
 * เปิด MLX42 + สร้าง screen image ขนาด WIDTH x HEIGHT.
 * WHY วาดลง image เดียวแล้ว mlx_image_to_window ทีเดียว:
 * เร็วกว่า put pixel ตรงหน้าต่าง และคุม double-buffer ให้ MLX จัดการ.
 */
int	init_mlx(t_game *game)
{
	(void)game;
	/* TODO:
	 *  game->mlx.mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	 *  ถ้า NULL → return error
	 *  game->mlx.screen.img = mlx_new_image(...);
	 *  mlx_image_to_window(...); */
	return (0);
}
