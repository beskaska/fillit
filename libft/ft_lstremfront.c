/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremfront.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 23:43:46 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/12 23:53:31 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstremfront(t_list *head)
{
	t_list	*tmp;

	if (head)
	{
		tmp = head->next;
		free(head);
		return (tmp);
	}
	return (NULL);
}
