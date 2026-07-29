#include "cub3d.h"

/*
 * จุด free ที่เดียวของทั้งโปรเจกต์ (design rule: centralize cleanup).
 * เรียกได้ทุกจังหวะ — ต้องทน field ที่ยังเป็น NULL (เพราะ memset 0 ตอน main).
 * WHY คืน code เพื่อให้ main ทำ `return cleanup_exit(...)` บรรทัดเดียวจบ.
 */
int	cleanup_exit(t_game *game, char *msg, int code)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	/* TODO:
	 *  ft_free_split(game->map.grid);
	 *  free(game->tex_path[i]) ทั้ง 4;
	 *  mlx_delete_image / mlx_terminate ถ้า init แล้ว;
	 *  ระวัง double free — เช็ค NULL ก่อน free เสมอ */
	(void)game;
	return (code);
}
