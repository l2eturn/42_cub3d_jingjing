#include "cub3d.h"

/*
 * เติมพื้น (ครึ่งล่าง) และเพดาน (ครึ่งบน) ด้วยสีเดียวจาก F/C.
 */
void	draw_background(t_game *game)
{
	(void)game;
	/* TODO:
	 *  for y in [0, HEIGHT/2):      put_pixel แถวนั้นด้วย game->ceil_color
	 *  for y in [HEIGHT/2, HEIGHT): put_pixel แถวนั้นด้วย game->floor_color
	 *  หมายเหตุ: สีต้องเป็น 0xRRGGBBAA (alpha=0xFF) สำหรับ MLX42 */
}
