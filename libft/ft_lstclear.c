/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpasty <cpasty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 21:23:38 by cpasty            #+#    #+#             */
/*   Updated: 2020/11/07 21:24:09 by cpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;

	if (!del || !lst)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		list = *lst;
		*lst = list->next;
		free(list);
	}
	*lst = NULL;
}
