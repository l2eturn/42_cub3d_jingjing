/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:28:54 by marvin            #+#    #+#             */
/*   Updated: 2025/06/15 21:28:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*new_s1;
	unsigned const char	*new_s2;
	size_t				i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	new_s1 = s1;
	new_s2 = s2;
	if (n == 0)
		return (0);
	while (i < (n - 1))
	{
		if (new_s1[i] != new_s2[i])
			return (new_s1[i] - new_s2[i]);
		i++;
	}
	return (new_s1[i] - new_s2[i]);
}
