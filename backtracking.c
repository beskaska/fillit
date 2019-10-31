/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:45:48 by aimelda           #+#    #+#             */
/*   Updated: 2019/10/31 23:13:39 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void remove_nodes(t_pos *pos, t_cell **cells, t_stack *stack)
{
	t_cell	*cur;
	t_cell	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		cur = cells[pos->a[i]];
		while (cur) //пробегаемся по столбцу выбранной ячейки чтобы удалить позиции
		{
			j = -1;
			while (++j < 4)
			{
				tmp = cells[cur->pos->a[j]]; //пробегаемся по каждому столбцу удаляемой позиции, чтобы удалить в этих стобцах наименование позиции
				while (tmp != cur)
					tmp = tmp->next;
				if (pos->a[i] != cur->pos->a[j]) //не
				{
					tmp->next->prev = tmp->prev;
					tmp->prev->next = tmp->next;
					if (tmp == cells[cur->pos->a[j]])
						cells[cur->pos->a[j]] = tmp->next; //чтобы начало списка ячейки соответствовал валидному положению
					//tmp->next->prev = tmp;
					//tmp->prev->next = tmp;
				}
			}
			cur->pos->next->prev = cur->pos->prev;
			cur->pos->prev->next = cur->pos->next;
			//tmp->pos->next->prev = tmp->pos;
			//tmp->pos->prev->next = tmp->pos;
			if (cur->next == cells[pos->a[i]])
				break;
			cur = cur->next;
		}
	}
}

static void	recursion(t_pos *pos, t_cell **cells, char *flags, char *tetrs)
{
	while (tetrs[pos->tetrimino - 64])
		pos = pos->next;
	backtracking(pos, cells, flags, tetrs);
}

static void restore_nodes(t_pos *pos, t_cell **cells)
{
	t_cell	*cur;
	t_cell	*tmp;
	int		i;
	int		j;

	i = 4;
	while (i-- > 0)
	{
		cur = cells[pos->a[i]]->prev;
		while (cur)
		{
			j = -1;
			while (++j < 4)
			{
				tmp = cells[cur->pos->a[j]];
				if (pos->a[i] != cur->pos->a[j])

			}
		}
	}
}

void		backtracking(t_pos *h_pos, t_cell **cells, char *flags, char *tetrs)
{
	t_pos	*pos;
	t_cell	*tmp;
	t_stack	*stack; //test
	int		i;

	stack = NULL;
	pos = h_pos;
	while (pos)
	{
		tetrs[pos->tetrimino - 64] = 1;
		i = 4;
		while (i-- > 0)
			flags[pos->a[i]] = pos->tetrimino;
		if (--tetrs[0] == 0)
			return (1);
		while (i < 4) //need to correct
			remove_nodes(pos, cells, stack); //need to correct
		recursion(pos->next, tetrs);
		tetrs[pos->tetrimino - 64] = 0;
		while (i < 4) // if i == 0;
			flags[pos->a[i++]] = ".";
		++tetrs[0];
		//restoring
		if (pos->next == h_pos)
			break;
		pos = pos->next;
	}
	return (0);
}
