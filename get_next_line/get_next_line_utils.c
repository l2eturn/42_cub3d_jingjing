/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:44:19 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/06/22 22:44:19 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	unsigned char	*new_ptr;
	size_t			i;

	i = 0;
	new_ptr = NULL;
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if ((nmemb * size) > 2147483647
		|| nmemb > 2147483647
		|| size > 2147483647)
		return (NULL);
	new_ptr = malloc(nmemb * size);
	if (new_ptr == NULL)
		return (NULL);
	while (i < (size * nmemb))
	{
		new_ptr[i] = 0;
		i++;
	}
	return (new_ptr);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
	{
		len++;
	}
	return (len);
}

size_t	ft_strlcat_gnl(char *dst, const char *src, size_t dsize)
{
	unsigned int	i;
	unsigned int	len_d;
	unsigned int	len_s;

	len_d = ft_strlen_gnl(dst);
	len_s = ft_strlen_gnl(src);
	if (len_d >= dsize)
	{
		return (len_s + dsize);
	}
	i = 0;
	while ((i + len_d) < dsize - 1 && src[i] != '\0')
	{
		dst[len_d + i] = src[i];
		i++;
	}
	dst[len_d + i] = '\0';
	return (len_d + len_s);
}

char	*append_n_str(char *old, char *read, size_t index_lf)
{
	char	*new;
	size_t	len_old;

	len_old = ft_strlen_gnl(old);
	new = ft_calloc_gnl((len_old + index_lf + 1), 1);
	if (!new)
	{
		free(old);
		return (NULL);
	}
	ft_strlcat_gnl(new, old, len_old + 1);
	ft_strlcat_gnl(new, read, len_old + index_lf + 1);
	free(old);
	return (new);
}

ssize_t	ft_strchr_gnl(const char *s, int c)
{
	ssize_t	i;
	ssize_t	len;

	i = 0;
	len = ft_strlen_gnl(s);
	while (i <= len)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
