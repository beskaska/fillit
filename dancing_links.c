/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dancing_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:48:35 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/11 14:37:31 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	new_node(t_stack **head, t_cell *content)
{
	t_stack	*tmp;

	tmp = (t_stack*)malloc(sizeof(t_stack));
	tmp->next = *head;
	tmp->elem = content;
	*head = tmp;
}

void	rem_column(t_cell **cells, t_cell *cur, t_stack **stack, int j)
{
	t_cell	*tmp;

	tmp = cells[cur->pos->a[j]];
	while (tmp->pos != cur->pos)
		tmp = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	else
		cells[cur->pos->a[j]]->prev = tmp->prev;
	if (tmp->prev->next)
		tmp->prev->next = tmp->next;
	new_node(stack, tmp);
	if (tmp == cells[cur->pos->a[j]])
		cells[cur->pos->a[j]] = tmp->next;
}
