/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:07:19 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/11 18:36:34 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	new_node(t_stk **head, t_cell *content)
{
	t_stk	*tmp;

	tmp = (t_stk*)malloc(sizeof(t_stk));
	tmp->next = *head;
	tmp->elem = content;
	*head = tmp;
}

static void	remove_column(t_cell **cells, t_cell *cur, t_stk **stack, int j)
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

static int	remove_row(t_pos *pos, t_pos **head)
{
	if (pos->next)
		pos->next->prev = pos->prev;
	if (pos->prev)
		pos->prev->next = pos->next;
	else if (pos->next)
		*head = pos->next;
	else
		return (0);
	return (1);
}

int			removing(t_pos *pos, t_cell **cells, t_stk **stack, t_pos **tetrs)
{
	t_cell	*cur;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		cur = cells[pos->a[i]];
		while (cur && cur->pos->tetrimino <= pos->tetrimino)
			cur = cur->next;
		while (cur)
		{
			j = -1;
			while (++j < 4)
				if (pos->a[i] != cur->pos->a[j])
					remove_column(cells, cur, stack, j);
			if (!(remove_row(cur->pos, tetrs + (cur->pos->tetrimino - 65))))
				return (i);
			cur = cur->next;
		}
	}
	return (i);
}
