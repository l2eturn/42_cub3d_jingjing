/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:09:27 by marvin            #+#    #+#             */
/*   Updated: 2025/06/15 21:09:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*new_s;
	unsigned char		new_c;
	size_t				i;

	if (!s)
		return (NULL);
	i = 0;
	new_c = c;
	new_s = s;
	while (i < n)
	{
		if (new_s[i] == new_c)
			return ((void *) &new_s[i]);
		i++;
	}
	return (NULL);
}
