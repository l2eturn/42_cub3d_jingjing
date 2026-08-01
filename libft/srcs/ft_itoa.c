/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:55:25 by marvin            #+#    #+#             */
/*   Updated: 2025/06/18 16:55:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_itoa(int n)
{
	char	*new;
	long	nbr;
	size_t	len;

	nbr = n;
	len = 1;
	if (nbr == 0)
		return (iszero());
	if (nbr < 0)
	{
		nbr *= -1;
		len++;
	}
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	new = ft_calloc(len, sizeof(char));
	if (!new)
		return (NULL);
	process_itoa(new, n);
	return (new);
}

void	process_itoa(char *str, long n)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_strcat_chr(str, '-');
		nbr *= -1;
	}
	if (nbr > 9)
	{
		process_itoa(str, nbr / 10);
		process_itoa(str, nbr % 10);
	}
	else
	{
		ft_strcat_chr(str, "0123456789"[nbr]);
	}
}

void	ft_strcat_chr(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	str[i] = c;
	i++;
	str[i] = '\0';
}

char	*iszero(void)
{
	char	*new;

	new = malloc(2);
	if (!new)
		return (NULL);
	new[0] = '0';
	new[1] = '\0';
	return (new);
}
