#include "cub3d.h"

/*
 * โหลด PNG 4 ทิศ (NO/SO/WE/EA) จาก path ที่ parser เก็บไว้.
 * WHY โหลดหลัง validate: ถ้า map พังก็ไม่ต้องเสียเวลา decode PNG,
 * และแยก MLX side-effect ออกจาก parsing.
 */
int	load_textures(t_game *game)
{
	(void)game;
	/* TODO: วน 4 ทิศ:
	 *  game->tex[i].tex = mlx_load_png(game->tex_path[i]);
	 *  ถ้า NULL → return error
	 *  เก็บ width/height ไว้ใช้ตอน map texel */
	return (0);
}
