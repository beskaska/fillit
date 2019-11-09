/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:45:48 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/09 18:13:56 by aimelda          ###   ########.fr       */
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

static int	removing(t_pos *pos, t_cell **cells, t_stack **stack, t_usage **tetrs)
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
			j = -1;
			while (++j < 4)
				if (pos->a[i] != cur->pos->a[j])
					rem_column(cells, cur, stack, j);
			if (cur->pos->next)
				cur->pos->next->prev = cur->pos->prev;
			if (cur->pos->prev)
				cur->pos->prev->next = cur->pos->next;
			if (cur->pos == tetrs[cur->pos->tetrimino - 65]->head_pos)
			{
				if (cur->pos->next && cur->pos->tetrimino == cur->pos->next->tetrimino)
					tetrs[cur->pos->tetrimino - 65]->head_pos = cur->pos->next;
				else if (tetrs[cur->pos->tetrimino - 64]->bool)
					tetrs[cur->pos->tetrimino - 65]->head_pos = NULL;
				else
					return (i);
			}
			if (cur->next == cells[pos->a[i]])
				break ;
			cur = cur->next;
		}
	}
	return (i);
}

static int	recursion(t_cell **cells, char *flags, t_usage **tetrs)
{
	int		i;

	i = 1;
	while (tetrs[i]->bool)
		i++;
	return (backtracking(tetrs, cells, flags, tetrs[--i]->head_pos));
}

static void	restoring(int i, t_cell **cells, t_stack **stack, t_usage **tetrs)
{
	t_cell	*cur;
	t_cell	*tmp;
	int		j;

	cur = cells[i]->prev;
	while (cur->pos != (*stack)->elem->pos)
		cur = cur->prev;
	while (cur)
	{
		j = 4;
		while (j-- > 0)
			if (i != cur->pos->a[j])
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
		if (!(cur->pos->prev) || cur->pos->tetrimino != cur->pos->prev->tetrimino)
			tetrs[cur->pos->tetrimino - 65]->head_pos = cur->pos;
		if (cur == cells[i])
			break ;
		cur = cur->prev;
	}
}

int			backtracking(t_usage **tetrs, t_cell **cells, char *flags, t_pos *pos)
{
	t_stack	*stack;
	int		i;

	stack = NULL;
	while (pos)
	{
		if (!(tetrs[pos->tetrimino - 64]->bool))
		{
			tetrs[pos->tetrimino - 64]->bool = 1;
			i = 4;
			while (i-- > 0)
				flags[pos->a[i]] = pos->tetrimino;
			if (--(tetrs[0]->bool) == 0)
				return (1);
			i = removing(pos, cells, &stack, tetrs);
			if (i == 4 && recursion(cells, flags, tetrs))
				return (1);
			if (i < 4)
				i++;
			while (i-- > 0)
				if (cells[pos->a[i]])
					restoring(pos->a[i], cells, &stack, tetrs);
			tetrs[pos->tetrimino - 64]->bool = 0;
			i = 0;
			while (i < 4)
				flags[pos->a[i++]] = '.';
			++(tetrs[0]->bool);
		}
		pos = pos->next;
	}
	return (0);
}
