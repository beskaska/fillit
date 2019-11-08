/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:45:48 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/08 16:48:19 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void new_node(t_stack **head, t_cell *content, char begin)
{
	t_stack	*tmp;

	tmp = (t_stack*)malloc(sizeof(t_stack));
	tmp->next = *head;
	tmp->elem = content;
	tmp->head = begin;
	*head = tmp;
}

static void	del_node(t_stack **head)
{
	t_stack	*tmp;

	tmp = *head;
	*head = (*head)->next;
	free(tmp);
}

static void remove_nodes(t_pos *pos, t_cell **cells, t_stack **stack, t_pos **h_pos)
{
	t_cell	*cur;
	t_cell	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		cur = cells[pos->a[i]];
		while (cur)
		{
			j = -1;
			while (++j < 4)
				if (pos->a[i] != cur->pos->a[j])
				{
					if (cells[cur->pos->a[j]] == cells[cur->pos->a[j]]->next)
					{
						new_node(stack, cells[cur->pos->a[j]], 1);
						cells[cur->pos->a[j]] = NULL;
					}
					else
					{
						tmp = cells[cur->pos->a[j]];
						while (tmp->pos != cur->pos)
							tmp = tmp->next;
						tmp->next->prev = tmp->prev;
						tmp->prev->next = tmp->next;
						new_node(stack, tmp, 0);
						if (tmp == cells[cur->pos->a[j]])
						{
							cells[cur->pos->a[j]] = tmp->next;
							(*stack)->head = 1;
						}
					}
				}
			if (cur->pos->next)
				cur->pos->next->prev = cur->pos->prev;
			if (cur->pos->prev)
				cur->pos->prev->next = cur->pos->next;
			if (cur->pos == *h_pos)/* test */
					{/* test */
						cur->pos->head = 1;/* test */
						*h_pos = (*h_pos)->next;
					}/* test */
			if (cur->next == cells[pos->a[i]])
				break;
			cur = cur->next;
		}
	}
}

static int	recursion(t_pos *pos, t_cell **cells, char *flags, char *tetrs)
{
	while (pos && tetrs[pos->tetrimino - 64])
		pos = pos->next;
	if (pos && backtracking(pos, cells, flags, tetrs))
		return (1);
	return (0);
}

static void restore_nodes(t_pos *pos, t_cell **cells, t_stack **stack, t_pos **h_pos)
{
	t_cell	*cur;
	t_cell	*tmp;
	int		i;
	int		j;

	i = 4;
	while (i-- > 0)
	{
		//printf("In restore_nodes at cell = %i of POS{%i %i %i %i}\n", pos->a[i], pos->a[0], pos->a[1], pos->a[2], pos->a[3]);//DELETE
		cur = cells[pos->a[i]];
		while (cur)
		{
			cur = cur->prev;
			j = 4;
			while (j-- > 0)
				if (pos->a[i] != cur->pos->a[j])
				{
					tmp = cells[cur->pos->a[j]];
					if (!tmp)
						tmp = (*stack)->elem;
					else
					{
						while (tmp->pos != (*stack)->elem->prev->pos)
							tmp = tmp->next;
						tmp->next->prev = (*stack)->elem;
						tmp->next = (*stack)->elem;
					}
					if ((*stack)->head)
						cells[cur->pos->a[j]] = (*stack)->elem;
					del_node(stack);
				}
			if (cur->pos->next)
				cur->pos->next->prev = cur->pos;
			if (cur->pos->prev)
				cur->pos->prev->next = cur->pos;
			if (cur->pos->head)/* test */
			{/* test */
				*h_pos = cur->pos;
				cur->pos->head = 0;/* test */
			}/* test */
			if (cur == cells[pos->a[i]])
				break;
		}
	}
}

int			backtracking(t_pos *h_pos, t_cell **cells, char *flags, char *tetrs)
{
	t_pos	*pos;
	t_stack	*stack;
	int		i;

	stack = NULL;
	pos = h_pos;
	while (pos)
	{
		if (!(tetrs[pos->tetrimino - 64]))
		{
			tetrs[pos->tetrimino - 64] = 1;
			i = 4;
			while (i-- > 0)
				flags[pos->a[i]] = pos->tetrimino;
			if (--tetrs[0] == 0)
				return (1);
			remove_nodes(pos, cells, &stack, &h_pos);
			if (recursion(h_pos, cells, flags, tetrs))
				return (1);
			tetrs[pos->tetrimino - 64] = 0;
			i = 0;
			while (i < 4)
				flags[pos->a[i++]] = '.';
			++tetrs[0];
			restore_nodes(pos, cells, &stack, &h_pos);
		}
		pos = pos->next;
	}
	return (0);
}
