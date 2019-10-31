/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:26:11 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/15 17:34:01 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(t_list **head)
{
	t_list	*tmp;

	if (head)
	{
		tmp = *head;
		while (tmp)
		{
			*head = (*head)->next;
			free(tmp);
			tmp = *head;
		}
	}
}
