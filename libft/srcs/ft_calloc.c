/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:28:00 by marvin            #+#    #+#             */
/*   Updated: 2025/06/17 18:28:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*new_ptr;
	size_t			i;

	i = 0;
	new_ptr = NULL;
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if ((nmemb * size) > INT_MAX
		|| nmemb > INT_MAX
		|| size > INT_MAX)
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
