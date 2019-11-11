/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restoring.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:12:31 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/11 18:36:23 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	del_node(t_stk **head)
{
	t_stk	*tmp;

	tmp = *head;
	*head = (*head)->next;
	free(tmp);
}

static void	restore_column(t_cell **cells, t_cell *cur, t_stk **stack, int j)
{
	if (!cells[cur->pos->a[j]])
		cells[cur->pos->a[j]] = (*stack)->elem;
	else if (!((*stack)->elem->next))
	{
		(*stack)->elem->prev->next = (*stack)->elem;
		cells[cur->pos->a[j]]->prev = (*stack)->elem;
	}
	else
	{
		(*stack)->elem->next->prev = (*stack)->elem;
		if ((*stack)->elem->prev->next)
			(*stack)->elem->prev->next = (*stack)->elem;
		else
			cells[cur->pos->a[j]] = (*stack)->elem;
	}
	del_node(stack);
}

static void	restore_row(t_pos *pos, t_pos **head)
{
	if (pos->next)
		pos->next->prev = pos;
	if (pos->prev)
		pos->prev->next = pos;
	else
		*head = pos;
}

void		restoring(int i, t_cell **cells, t_stk **stack, t_pos **tetrs)
{
	t_cell	*cur;
	int		j;

	cur = cells[i]->prev;
	while (*stack)
	{
		if (cur->pos == (*stack)->elem->pos)
		{
			j = 4;
			while (j-- > 0)
				if (i != cur->pos->a[j])
					restore_column(cells, cur, stack, j);
			restore_row(cur->pos, tetrs + (cur->pos->tetrimino - 65));
		}
		if (cur == cells[i])
			break ;
		cur = cur->prev;
	}
}
