/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 23:35:10 by waroonwork@       #+#    #+#             */
/*   Updated: 2026/08/01 13:25:28 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi_base(char *str, char *base)
{
	int	len_base;
	int	negative;
	int	j;

	negative = 1;
	j = 0;
	len_base = ft_strlen(base);
	if (len_base == 0 || len_base == 1 || *base == 0
		|| has_duplicates(base) == 0
		|| ft_strchr(base, '+') != NULL || ft_strchr(base, '-') != NULL
		|| ft_strchr(base, ' ') != NULL || (*base >= 11 && *base <= 15))
		return (0);
	while (str[j] == ' ' || (str[j] >= 9 && str[j] <= 13))
		j++;
	while (str[j] == '-' || str[j] == '+')
	{
		if (str[j] == '-')
		{
			negative *= -1;
		}
		j++;
	}
	return (loop_atoi_base(base, str, j) * negative);
}

int	has_duplicates(char *str)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(str);
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	loop_atoi_base(char *base, char *str, int j)
{
	int	ans;
	int	i;
	int	len_base;

	ans = 0;
	len_base = ft_strlen(base);
	while (ft_strchr(base, str[j]) != NULL && str[j] != '\0')
	{
		i = 0;
		while (base[i] != '\0')
		{
			if (base[i] == str[j])
				break ;
			i++;
		}
		ans = (ans * len_base) + i;
		j++;
	}
	return (ans);
}
