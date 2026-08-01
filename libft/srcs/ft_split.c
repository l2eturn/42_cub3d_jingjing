/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:19:39 by marvin            #+#    #+#             */
/*   Updated: 2025/06/18 00:19:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	wc;

	if (!s)
		return (NULL);
	if (s[0] == '\0')
	{
		new = ft_calloc(1, sizeof(char *));
		if (!new)
			return (NULL);
		new[0] = NULL;
		return (new);
	}
	wc = count_word_split(s, c);
	new = ft_calloc((wc + 1), sizeof(char *));
	if (!new)
		return (NULL);
	if (process_split(s, c, new, -1) == NULL)
		return (NULL);
	new[wc] = NULL;
	return (new);
}

size_t	count_word_split(char const *s, char c)
{
	size_t	i;
	size_t	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c && i == 0)
			word++;
		else if (s[i] != c && s[i - 1] == c)
			word++;
		i++;
	}
	return (word);
}

void	*free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**process_split(char const *s, char c, char **neww, size_t i)
{
	size_t	index_sep;
	size_t	last_index_sep;
	size_t	new_count;

	new_count = 0;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && i == 0)
			last_index_sep = i;
		else if (s[i] != c && s[i - 1] == c)
			last_index_sep = i;
		if (i > 0)
		{
			if ((s[i] == c || i == ft_strlen(s)) && s[i - 1] != c)
			{
				index_sep = i;
				neww[new_count] = ft_calloc(index_sep - last_index_sep + 1, 1);
				if (!neww[new_count])
					return (free_arr(neww));
				inner_loop_split(s, last_index_sep, index_sep,
					neww[new_count++]);
			}
		}
	}
	return (neww);
}

void	inner_loop_split(char const *s, size_t last_index_sep
			, size_t index_sep, char *neww)
{
	size_t	j;

	j = 0;
	while (last_index_sep < index_sep)
	{
		neww[j] = s[last_index_sep];
		last_index_sep++;
		j++;
	}
	neww[j] = '\0';
}
