#include "cub3d.h"

/*
 * libft helpers ที่ cub3D ใช้บ่อย. ถ้าน้องมี libft ของตัวเองที่ผ่าน Norm แล้ว
 * จะลบไฟล์นี้แล้วลิงก์ libft.a แทนก็ได้ — แค่ให้ prototype ตรงกัน.
 */

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dst;

	dst = malloc(ft_strlen(s) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	dst = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dst)
		return (NULL);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	j = -1;
	while (s2[++j])
		dst[i + j] = s2[j];
	dst[i + j] = '\0';
	return (dst);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
