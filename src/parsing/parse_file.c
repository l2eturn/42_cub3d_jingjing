#include "cub3d.h"

/*
 * เจ้าภาพของ parsing: เปิดไฟล์ → อ่าน element (NO/SO/WE/EA/F/C)
 * จนครบ → บรรทัดที่เหลือคือ map → ส่งต่อ parse_map.
 * WHY แยก element กับ map: element มาก่อน map เสมอตาม subject,
 * และ map เป็นบล็อกท้ายสุดที่ห้ามมี element คั่น.
 */
int	parse_cub(t_game *game, char *path)
{
	int		fd;
	char	*first_map_line;

	first_map_line = NULL;
	/* TODO: เช็คนามสกุล .cub ก่อนเปิด */
	if ()
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\nCannot open file\n", 23), 1);
	if (parse_elements(game, fd, &first_map_line) != 0)
		return (close(fd), 1);
	if (parse_map(game, fd, first_map_line) != 0)
		return (close(fd), 1);
	close(fd);
	return (0);
}
