#include "cub3d.h"

/*
 * key event → ตั้ง/ล้าง flag เท่านั้น (ไม่ขยับตรงนี้).
 * ESC = ปิดเกม. WHY แยก press/release: กดค้างต้องเดินต่อ.
 */
void	key_hook(mlx_key_data_t kd, void *param)
{
	(void)kd;
	(void)param;
	/* TODO:
	 *  t_game *game = param;
	 *  if (kd.key == KEY_ESC && kd.action == MLX_PRESS) close_hook(game);
	 *  W/S → move_fb = (press ? ±1 : 0); A/D → move_lr; ←/→ → rotate */
}

/*
 * ถูกเรียกทุกเฟรมโดย mlx_loop_hook: update state แล้ว render.
 * WHY logic อยู่ใน loop ไม่ใช่ key event: เฟรมเรตคงที่, เคลื่อนไหวลื่น.
 */
void	loop_hook(void *param)
{
	(void)param;
	/* TODO: t_game *game = param; update_player(game); render_frame(game); */
}

/*
 * ปิดหน้าต่าง (ปุ่มกากบาท / ESC) → หยุด loop แล้วไป cleanup.
 */
void	close_hook(void *param)
{
	(void)param;
	/* TODO: mlx_close_window(((t_game *)param)->mlx.mlx); */
}
