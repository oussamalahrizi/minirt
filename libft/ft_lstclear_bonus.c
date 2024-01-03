/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 12:08:53 by idelfag           #+#    #+#             */
/*   Updated: 2022/11/10 10:03:01 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tp;
	}
	*lst = NULL;
}
