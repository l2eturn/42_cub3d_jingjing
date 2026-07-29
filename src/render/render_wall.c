#include "cub3d.h"

/*
 * วาดกำแพง 1 คอลัมน์แนวตั้ง โดย map แต่ละ pixel → texel ของ texture.
 * WHY tex_y คำนวณจากสัดส่วน (y-draw_start)/line_height:
 * ยืด/ย่อ texture ให้พอดีความสูงกำแพง ณ ระยะนั้น.
 */
void	draw_column(t_game *game, t_ray *ray, int x)
{
	(void)game;
	(void)ray;
	(void)x;
	/* TODO:
	 *  เลือก texture ตามทิศ (side + step): NO/SO/WE/EA
	 *  step = (double)tex_h / line_height;
	 *  tex_pos = (draw_start - HEIGHT/2 + line_height/2) * step;
	 *  for y in [draw_start, draw_end]:
	 *      tex_y = (int)tex_pos & (tex_h-1); tex_pos += step;
	 *      color = อ่าน texel(tex_x, tex_y); put_pixel(screen, x, y, color); */
}
