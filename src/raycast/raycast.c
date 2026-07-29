#include "cub3d.h"

/*
 * DDA raycasting — หัวใจ 3D. ยิง 1 ray ต่อ 1 คอลัมน์จอ.
 * อ้างอิงสูตร lodev.org/cgtutor/raycasting.html
 */

/*
 * แปลง x (คอลัมน์จอ) → ทิศ ray ผ่านสูตร camera plane.
 * camera_x ∈ [-1,1]: -1 = ซ้ายสุดจอ, 0 = กลาง, 1 = ขวาสุด.
 */
void	init_ray(t_ray *ray, t_player *p, int x)
{
	(void)ray;
	(void)p;
	(void)x;
	/* TODO:
	 *  camera_x = 2*x/(double)WIDTH - 1;
	 *  ray_dir = dir + plane * camera_x;
	 *  map_x/map_y = (int)pos; */
}

/*
 * delta_dist = ระยะที่ ray เดินเมื่อข้าม 1 เส้น grid.
 * step = ทิศเดิน (+1/-1). side_dist = ระยะถึงเส้น grid แรก.
 */
void	init_step(t_ray *ray, t_player *p)
{
	(void)ray;
	(void)p;
	/* TODO:
	 *  delta_dist_x = fabs(1/ray_dir_x); (ระวังหาร 0 → 1e30)
	 *  ถ้า ray_dir_x < 0: step_x=-1, side_dist_x=(pos_x-map_x)*delta
	 *  else: step_x=1, side_dist_x=(map_x+1-pos_x)*delta; (เหมือนกันแกน y) */
}

/*
 * เดินทีละช่อง grid ไปตามแกนที่ side_dist สั้นกว่า จนชนกำแพง '1'.
 * WHY DDA: กระโดดทีละเส้น grid — ไม่มี ray ทะลุมุมกำแพง, เร็ว, แม่น.
 */
void	perform_dda(t_ray *ray, t_game *game)
{
	(void)ray;
	(void)game;
	/* TODO: while (!hit):
	 *   ถ้า side_dist_x < side_dist_y: side_dist_x+=delta; map_x+=step_x; side=0
	 *   else: side_dist_y+=delta; map_y+=step_y; side=1
	 *   ถ้า grid[map_y][map_x]=='1' → hit=1 */
}

/*
 * แปลงระยะ → ความสูงแท่งกำแพง + ช่วง draw + wall_x (ตำแหน่งชนบนกำแพง).
 * WHY ใช้ perp_wall_dist (ไม่ใช่ euclidean): กันภาพโค้ง fisheye.
 */
void	calc_wall_data(t_ray *ray)
{
	(void)ray;
	/* TODO:
	 *  perp = (side==0) ? side_dist_x-delta_dist_x : side_dist_y-delta_dist_y;
	 *  line_height = HEIGHT/perp;
	 *  draw_start = -line_height/2 + HEIGHT/2 (clamp 0);
	 *  draw_end   =  line_height/2 + HEIGHT/2 (clamp HEIGHT-1);
	 *  wall_x = จุดที่ ray ชน (เศษของ pos ตามแกนตรงข้าม side) → tex_x */
}
