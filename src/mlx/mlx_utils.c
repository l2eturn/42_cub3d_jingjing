#include "cub3d.h"

/*
 * เขียน 1 pixel ลง image buffer แบบ RGBA (MLX42 ใช้ 32-bit RGBA).
 * WHY เช็คขอบเอง: เขียนนอก buffer = เขียนทับ heap = segv/undefined.
 */
void	put_pixel(t_img *img, int x, int y, int color)
{
	(void)img;
	(void)x;
	(void)y;
	(void)color;
	/* TODO:
	 *  if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT) return;
	 *  mlx_put_pixel(img->img, x, y, color);  // color = 0xRRGGBBAA */
}
