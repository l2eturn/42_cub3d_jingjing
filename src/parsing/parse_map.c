#include "cub3d.h"

/*
 * อ่านบรรทัด map ที่เหลือทั้งหมดมาต่อกันเป็น grid (char **).
 * เริ่มจาก first_line ที่ parse_elements ส่งมา แล้วอ่านต่อจน EOF.
 * WHY เก็บ grid แบบ ragged (ยาวไม่เท่ากัน): map จริงบรรทัดสั้นยาวไม่เท่ากัน,
 * ค่อย normalize ความกว้าง/หา player ตอน validate.
 */
int	parse_map(t_game *game, int fd, char *first_line)
{
	(void)game;
	(void)fd;
	(void)first_line;
	/* TODO: append first_line เข้า grid;
	 *       loop get_next_line ต่อ → append ทุกบรรทัด (ตัด '\n');
	 *       เก็บ map.height, คำนวณ map.width = บรรทัดยาวสุด. */
	return (0);
}
