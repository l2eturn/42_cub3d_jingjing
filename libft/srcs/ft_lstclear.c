/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:37:35 by marvin            #+#    #+#             */
/*   Updated: 2025/06/19 16:37:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	current = *lst;
	if (current == NULL)
	{
		*lst = NULL;
		return ;
	}
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		if (tmp->content != NULL)
			del(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}
