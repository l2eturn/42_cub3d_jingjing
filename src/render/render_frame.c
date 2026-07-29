#include "cub3d.h"

/*
 * วาด 1 เฟรม: พื้น/เพดานก่อน แล้ววน raycast ทุกคอลัมน์วาดกำแพงทับ.
 * WHY วาดพื้น/เพดานก่อน: กำแพงทับตรงกลางพอดี ไม่ต้องเคลียร์ buffer ซ้ำ.
 */
void	render_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	(void)game;
	(void)ray;
	x = 0;
	draw_background(game);
	while (x < WIDTH)
	{
		/* TODO:
		 *  init_ray(&ray, &game->player, x);
		 *  init_step(&ray, &game->player);
		 *  perform_dda(&ray, game);
		 *  calc_wall_data(&ray);
		 *  draw_column(game, &ray, x); */
		x++;
	}
	/* MLX42 auto-refresh image ที่ผูกกับ window แล้ว */
}
