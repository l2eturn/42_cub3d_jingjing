/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:09:54 by waragwon          #+#    #+#             */
/*   Updated: 2026/08/01 14:20:46 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_safe_calloc(size_t nmemb, size_t size, bool is_clear)
{
	static t_list	*mem_lst = NULL;
	t_list			*new;
	void			*ptr;

	if (is_clear)
	{
		ft_lstclear(&mem_lst, free);
		return (NULL);
	}
	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		return (NULL);
	new = ft_lstnew(ptr);
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_front(&mem_lst, new);
	return (ptr);
}
