/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:45:48 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/09 21:36:22 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	del_node(t_stack **head)
{
	t_stack	*tmp;

	tmp = *head;
	*head = (*head)->next;
	free(tmp);
}

static int	freeing(t_stack **stack)
{
	while (*stack)
	{
		free((*stack)->elem->pos);
		free((*stack)->elem);
		del_node(stack);
		free((*stack)->elem);
		del_node(stack);
		free((*stack)->elem);
		del_node(stack);
	}
	return (1);
}

static int	removing(t_pos *pos, t_cell **cells, t_stack **stack, t_pos **tetrs)
{
	t_cell	*cur;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		cur = cells[pos->a[i]];
		while (cur)
		{
			if (cur->pos->tetrimino > pos->tetrimino)
			{
				j = -1;
				while (++j < 4)
					if (pos->a[i] != cur->pos->a[j])
						rem_column(cells, cur, stack, j);
				if (cur->pos->next)
					cur->pos->next->prev = cur->pos->prev;
				if (cur->pos->prev)
					cur->pos->prev->next = cur->pos->next;
				else if (cur->pos->next)
					tetrs[cur->pos->tetrimino - 65] = cur->pos->next;
				else
					return (i);
			}
			cur = cur->next;
		}
	}
	return (i);
}

static void	restoring(int i, t_cell **cells, t_stack **stack, t_pos **tetrs)
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
			if (cur->pos->next)
				cur->pos->next->prev = cur->pos;
			if (cur->pos->prev)
				cur->pos->prev->next = cur->pos;
			else
				tetrs[cur->pos->tetrimino - 65] = cur->pos;
		}
		if (cur == cells[i])
			break ;
		cur = cur->prev;
	}
}

int			tracking(t_pos **tetrs, t_cell **cells, char *flags, t_pos *pos)
{
	t_stack		*stack;
	int			i;

	stack = NULL;
	while (pos)
	{
		i = 4;
		while (i-- > 0)
			flags[pos->a[i] + 1] = pos->tetrimino;
		if (pos->tetrimino - 64 == flags[0])
			return (1);
		if ((i = removing(pos, cells, &stack, tetrs)) < 4)
			i++;
		else if (tracking(tetrs, cells, flags, tetrs[pos->tetrimino - 64]))
			return (freeing(&stack));
		while (stack)
			if (cells[pos->a[--i]])
				restoring(pos->a[i], cells, &stack, tetrs);
		i = 0;
		while (i < 4)
			flags[pos->a[i++] + 1] = '.';
		pos = pos->next;
	}
	return (0);
}
