#include "cub3d.h"

/*
 * ตรวจ map ว่าเล่นได้จริง:
 *  - มี player ('N'/'S'/'E'/'W') พอดี 1 ตัว → set player แล้วแทนด้วย '0'
 *  - อักขระที่อนุญาต: 0 1 space + player char
 *  - map "ปิด" ทุกด้าน: ทุกช่องเดินได้ต้องไม่ติดขอบ/ไม่ติด space
 * WHY ใช้ flood fill: พิสูจน์ว่าไม่มีรูรั่วออกนอก map ได้ครบทุกกรณี
 * ดีกว่าเช็คแค่ขอบ (เจอรูตรงกลางที่ติด space ด้วย).
 */
int	validate_map(t_game *game)
{
	(void)game;
	/* TODO:
	 *  1) หา player + นับ (ต้อง == 1) → init_player(game, x, y, dir)
	 *  2) เช็ค charset
	 *  3) flood fill จากตำแหน่ง player: ถ้าไปแตะขอบ/space → return error
	 *     (ทำบน copy ของ grid เพื่อไม่ทำลาย map จริง) */
	return (0);
}
