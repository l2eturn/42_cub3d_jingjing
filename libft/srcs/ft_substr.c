/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:25:58 by marvin            #+#    #+#             */
/*   Updated: 2025/06/17 21:25:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		new = ft_calloc(1, sizeof(char));
		new[0] = '\0';
		return (new);
	}
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	new = ft_calloc((len + 1), sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		new[i] = s[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
