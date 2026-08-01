/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:02:02 by marvin            #+#    #+#             */
/*   Updated: 2025/06/18 00:02:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		start;
	int		end;

	if (set == NULL || s1 == NULL)
		return (NULL);
	start = find_start_trim(s1, set);
	end = find_end_trim(s1, set, start);
	new = ft_calloc(end - start + 1, sizeof(char));
	ft_strlcpy(new, &s1[start], end - start + 1);
	return (new);
}

int	in_set_trim(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

int	find_start_trim(char const *s1, char const *set)
{
	int		start;

	start = 0;
	while (s1[start] && in_set_trim(s1[start], set))
		start++;
	return (start);
}

int	find_end_trim(char const *s1, char const *set, int start)
{
	int		end;

	end = ft_strlen(s1) - 1;
	while (end > start && in_set_trim(s1[end], set))
		end--;
	end++;
	return (end);
}
