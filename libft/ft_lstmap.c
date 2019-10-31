/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:07:49 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/15 17:39:35 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_tmp(t_list *t, t_list **head)
{
	if (t)
		return (0);
	ft_lstfree(head);
	return (1);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;
	t_list	*tmp;

	tmp = NULL;
	res = NULL;
	if (f)
		while (lst)
		{
			if (tmp)
			{
				tmp->next = f(lst);
				tmp = tmp->next;
				if (check_tmp(tmp, &res))
					return (NULL);
			}
			else
			{
				res = f(lst);
				tmp = res;
			}
			lst = lst->next;
		}
	return (res);
}
