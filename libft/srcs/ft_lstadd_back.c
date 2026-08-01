/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:34:18 by marvin            #+#    #+#             */
/*   Updated: 2025/06/19 15:34:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *neww)
{
	t_list	*current;

	if (!neww || !lst)
		return ;
	current = *lst;
	if (current == NULL)
	{
		*lst = neww;
		return ;
	}
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = neww;
}
