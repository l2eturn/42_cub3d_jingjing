#include "cub3d.h"

/*
 * get_next_line + ft_split.
 * แนะนำ: ใช้ get_next_line / ft_split ของน้องเองจากโปรเจกต์ก่อน (ผ่าน Norm แล้ว).
 * ไฟล์นี้เป็น placeholder ให้ compile ผ่าน — TODO: แทนด้วยของจริง.
 */

char	*get_next_line(int fd)
{
	(void)fd;
	/* TODO: วาง get_next_line ของน้องที่นี่ (อ่านทีละบรรทัด, คืน string จบด้วย '\n') */
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	(void)s;
	(void)c;
	/* TODO: วาง ft_split ของน้อง (คืน NULL-terminated array) */
	return (NULL);
}

void	ft_free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
