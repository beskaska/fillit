/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:45:48 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/09 00:08:53 by aimelda          ###   ########.fr       */
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

static void remove_nodes(t_pos *pos, t_cell **cells, t_stack **stack, t_usage **tetrs)/* test */
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
			if (cur->pos == tetrs[cur->pos->tetrimino - 65]->head_pos)/* test */
			{/* test */
				//cur->pos->head = 1;/* test */
				if (cur->pos->next && cur->pos->tetrimino == cur->pos->next->tetrimino)/* test */
					tetrs[cur->pos->tetrimino - 65]->head_pos = cur->pos->next;/* test */
				else/* test */
					tetrs[cur->pos->tetrimino - 65]->head_pos = NULL;/* test */
			}/* test */
			if (cur->next == cells[pos->a[i]])
				break;
			cur = cur->next;
		}
	}
}

static int	recursion(t_cell **cells, char *flags, t_usage **tetrs)/* test */
{
	int		i;/* test */

	i = 1;/* test */
	//while (pos && tetrs[pos->tetrimino - 64])
	//	pos = pos->next;
	while (tetrs[i]->bool)/* test */
		i++;/* test */
	if (tetrs[--i]->head_pos)/* test */
		return (backtracking(tetrs, cells, flags, tetrs[i]->head_pos));/* test */
	return (0);
}

static void restore_nodes(t_pos *pos, t_cell **cells, t_stack **stack, t_usage **tetrs)/* test */
{
	t_cell	*cur;
	t_cell	*tmp;
	int		i;
	int		j;

	i = 4;
	while (i-- > 0)
	{
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
			if (!(cur->pos->prev) || cur->pos->tetrimino != cur->pos->prev->tetrimino)/* test */
			{/* test */
				tetrs[cur->pos->tetrimino - 65]->head_pos = cur->pos;/* test */
				//cur->pos->head = 0;/* test */
			}/* test */
			if (cur == cells[pos->a[i]])
				break;
		}
	}
}

int			backtracking(t_usage **tetrs, t_cell **cells, char *flags, t_pos *pos)/* test */
{
	//t_pos	*pos;
	t_stack	*stack;
	int		i;

	stack = NULL;
	//pos = h_pos;
	while (pos)
	{
		if (!(tetrs[pos->tetrimino - 64]->bool))
		{
			tetrs[pos->tetrimino - 64]->bool = 1;/* test */
			i = 4;
			while (i-- > 0)
				flags[pos->a[i]] = pos->tetrimino;
			if (--(tetrs[0]->bool) == 0)/* test */
				return (1);
			remove_nodes(pos, cells, &stack, tetrs);/* test */
			if (recursion(cells, flags, tetrs))/* test */
				return (1);
			restore_nodes(pos, cells, &stack, tetrs);/* test */
			tetrs[pos->tetrimino - 64]->bool = 0;/* test */
			i = 0;
			while (i < 4)
				flags[pos->a[i++]] = '.';
			++(tetrs[0]->bool);/* test */
		}
		pos = pos->next;
	}
	return (0);
}
