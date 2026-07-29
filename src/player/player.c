#include "cub3d.h"

/*
 * ตั้ง pos กลาง cell + dir/plane ตามตัวอักษรที่ spawn (N/S/E/W).
 * WHY plane ตั้งฉากกับ dir และยาว ~0.66: กำหนด FOV ~66°.
 * |plane| / |dir| = tan(FOV/2).
 */
void	init_player(t_game *game, int x, int y, char dir)
{
	(void)game;
	(void)x;
	(void)y;
	(void)dir;
	/* TODO: pos = (x+0.5, y+0.5);
	 *  N → dir(0,-1) plane(0.66,0); S → dir(0,1) plane(-0.66,0);
	 *  E → dir(1,0) plane(0,0.66); W → dir(-1,0) plane(0,-0.66) */
}

/*
 * อัปเดตตำแหน่ง/มุมต่อเฟรมจาก flag ที่ event ตั้งไว้.
 * WHY แยก flag ออกจาก key event: กดค้าง = เคลื่อนต่อเนื่องลื่น,
 * ไม่ผูกกับ key-repeat ของ OS.
 */
void	update_player(t_game *game)
{
	(void)game;
	/* TODO:
	 *  rotate: หมุน dir & plane ด้วย rotation matrix (มุม = rotate*ROT_SPEED)
	 *  move_fb/move_lr: บวก dir/plane * MOVE_SPEED
	 *  ก่อนย้ายจริง เช็ค is_blocked แยกแกน x และ y (slide ตามกำแพง) */
}

/*
 * เช็คว่าพิกัด world (x,y) ชนกำแพงไหม (เผื่อ margin กันติดมุม).
 */
int	is_blocked(t_game *game, double x, double y)
{
	(void)game;
	(void)x;
	(void)y;
	/* TODO: return (game->map.grid[(int)y][(int)x] == '1'); (+ กัน out of range) */
	return (0);
}
