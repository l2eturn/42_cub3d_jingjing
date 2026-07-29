#include "cub3d.h"

/*
 * อ่านทีละบรรทัดจนเจอบรรทัดที่ "เป็น map" (ขึ้นต้นด้วย 0/1/space)
 * แล้วเก็บบรรทัดนั้นไว้ใน *first_map_line เพื่อไม่ให้หลุด.
 * WHY: gnl อ่านแล้วบรรทัดนั้นหายจาก stream — ต้อง hand-off ให้ parse_map.
 */
int	parse_elements(t_game *game, int fd, char **first_map_line)
{
	(void)game;
	(void)fd;
	(void)first_map_line;
	/* TODO: loop get_next_line; ข้ามบรรทัดว่าง;
	 *       ถ้าเป็น NO/SO/WE/EA/F/C → parse_element_line;
	 *       ถ้าเป็นบรรทัด map → เก็บใส่ *first_map_line แล้ว break;
	 *       เช็คว่าครบ 6 element ก่อนเริ่ม map. */
	return (0);
}

/*
 * แยก 1 บรรทัด element: หา identifier แล้วเก็บ path/สี.
 * WHY เก็บ path เป็น string ก่อน แล้วค่อย load ทีหลัง:
 * แยก parsing (validate) ออกจาก MLX (side effect) ตาม design rule.
 */
int	parse_element_line(t_game *game, char *line)
{
	(void)game;
	(void)line;
	/* TODO: trim → split by space → match NO/SO/WE/EA → strdup path;
	 *       F/C → parse "R,G,B" → เก็บเป็น int; กัน duplicate. */
	return (0);
}
