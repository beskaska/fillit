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
			j = -1;
			while (++j < 4)
				if (pos->a[i] != cur->pos->a[j])
					rem_column(cells, cur, stack, j);
			if (cur->pos->next)
				cur->pos->next->prev = cur->pos->prev;
			if (cur->pos->prev)
				cur->pos->prev->next = cur->pos->next;
			if (cur->pos == tetrs[cur->pos->tetrimino - 65])
			{
				if (cur->pos->next && cur->pos->tetrimino == cur->pos->next->tetrimino)
					tetrs[cur->pos->tetrimino - 65] = cur->pos->next;
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

static int	recursion(t_cell **cells, char *flags, t_pos **tetrs)
{
	int		i;

	i = 0;
	while (!tetrs[i])
		i++;
	return (tracking(tetrs, cells, flags, tetrs[i]));
}

static void	restoring(int i, t_cell **cells, t_stack **stack, t_pos **tetrs)
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
		if (tetrs[cur->pos->tetrimino - 65] &&
		(!(cur->pos->prev) || cur->pos->tetrimino != cur->pos->prev->tetrimino))
			tetrs[cur->pos->tetrimino - 65] = cur->pos;
		if (cur == cells[i])
			break ;
		cur = cur->prev;
	}
}

int			tracking(t_pos **tetrs, t_cell **cells, char *flags, t_pos *pos)
{
	t_stack		*stack;
	int			i;
	t_pos		*tmp;

	stack = NULL;
	while (pos)
	{
		tmp = tetrs[pos->tetrimino - 65];
		tetrs[pos->tetrimino - 65] = NULL;
		i = 4;
		while (i-- > 0)
			flags[pos->a[i] + 1] = pos->tetrimino;
		if (--flags[0] == 0)
			return (1);
		i = removing(pos, cells, &stack, tetrs);
		if (i == 4 && recursion(cells, flags, tetrs))
			return (1);
		tetrs[pos->tetrimino - 65] = tmp;
		if (i < 4)
			i++;
		while (i-- > 0)
			if (cells[pos->a[i]])
				restoring(pos->a[i], cells, &stack, tetrs);
		i = 0;
		while (i < 4)
			flags[pos->a[i++] + 1] = '.';
		++flags[0];
		if (pos->next && pos->tetrimino != pos->next->tetrimino)/*test*/
		{/*test*/
			i = pos->tetrimino - 64;
			while (i < flags[0] && !tetrs[i])/*test*/
				i++;/*test*/
			pos = tetrs[i];/*test*/
		}/*test*/
		else/*test*/
			pos = pos->next;
	}
	return (0);
}
