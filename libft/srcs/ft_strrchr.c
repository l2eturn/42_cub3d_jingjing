/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:08:31 by marvin            #+#    #+#             */
/*   Updated: 2025/06/16 00:08:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	new_c;

	if (!s)
		return (NULL);
	new_c = c;
	len = ft_strlen(s);
	while (len > 0)
	{
		if (s[len] == new_c)
		{
			return ((char *) &s[len]);
		}
		len--;
	}
	if (s[0] == new_c)
	{
		return ((char *) &s[0]);
	}
	return (NULL);
}
