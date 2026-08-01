/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:46:19 by marvin            #+#    #+#             */
/*   Updated: 2025/06/15 23:46:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	unsigned int	i;
	unsigned int	len_d;
	unsigned int	len_s;

	if (!dst || !src)
		return (0);
	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	if (len_d >= dsize)
		return (len_s + dsize);
	i = 0;
	while ((i + len_d) < dsize - 1 && src[i] != '\0')
	{
		dst[len_d + i] = src[i];
		i++;
	}
	dst[len_d + i] = '\0';
	return (len_d + len_s);
}
