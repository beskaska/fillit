/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:45:48 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/02 23:47:03 by aimelda          ###   ########.fr       */
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

static void remove_nodes(t_pos *pos, t_cell **cells, t_stack **stack)
{
	t_cell	*cur;
	t_cell	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		printf("Program was there at i = %i\n", i);//DELETE
		cur = cells[pos->a[i]];
		while (cur) //пробегаемся по столбцу выбранной ячейки чтобы удалить позиции
		{
			j = -1;
			while (++j < 4)
			{//DELETE
			printf("Program was there at j = %i\n", j);//DELETE
				if (pos->a[i] != cur->pos->a[j])
				{
					if (cells[cur->pos->a[j]] == cells[cur->pos->a[j]]->next)
					{
						cells[cur->pos->a[j]] = NULL;
						new_node(stack, tmp, 1);
					}
					else
					{
						tmp = cells[cur->pos->a[j]]; //пробегаемся по каждому столбцу удаляемой позиции, чтобы удалить в этих стобцах наименование позиции
						while (tmp->pos != cur->pos)
							tmp = tmp->next;
						tmp->next->prev = tmp->prev;
						tmp->prev->next = tmp->next;
						new_node(stack, tmp, 0);
						if (tmp == cells[cur->pos->a[j]])
						{
							cells[cur->pos->a[j]] = tmp->next; //чтобы начало списка ячейки соответствовал валидному положению
							(*stack)->head = 1;
						}
					}
				}
			}//DELETE
			cur->pos->next->prev = cur->pos->prev;
			cur->pos->prev->next = cur->pos->next;
			if (cur->next == cells[pos->a[i]])
				break;
			cur = cur->next;
		}
	}
}

static int	recursion(t_pos *pos, t_cell **cells, char *flags, char *tetrs)
{
	t_pos	*head_pos;

	head_pos = pos->prev;
	while (tetrs[pos->tetrimino - 64])

		if (pos == head_pos)
			return (0);
		else
			pos = pos->next;
	if (backtracking(pos, cells, flags, tetrs))
		return (1);
	return (0);
}

static void restore_nodes(t_pos *pos, t_cell **cells, t_stack **stack)
{
	t_cell	*cur;
	t_cell	*tmp;
	int		i;
	int		j;

	i = 4;
	while (i-- > 0)
	{
		//printf("Program was there at i = %i\n", i);//DELETE
		cur = cells[pos->a[i]]->prev;
		while (cur)
		{
			j = 4;
			while (j-- > 0)
			{//DELETE
			//printf("Program was there at j = %i\n", j);//DELETE
				if (pos->a[i] != cur->pos->a[j])
				{
					if (!cells[cur->pos->a[j]])
						cells[cur->pos->a[j]] = (*stack)->elem;
					else
					{
						tmp = cells[cur->pos->a[j]];
						while (tmp->pos != (*stack)->elem->prev->pos)
							tmp = tmp->next;
						tmp->next->prev = (*stack)->elem;
						tmp->next = (*stack)->elem;
						if ((*stack)->head)
							cells[cur->pos->a[j]] = tmp;
					}
					del_node(stack);
				}
			}//DELETE
			cur->pos->next->prev = cur->pos;
			cur->pos->prev->next = cur->pos;
			if (cur->prev == cells[pos->a[i]]->prev)
				break;
			cur = cur->prev;
		}
	}
}

int			backtracking(t_pos *h_pos, t_cell **cells, char *flags, char *tetrs)
{
	t_pos	*pos;
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
		remove_nodes(pos, cells, &stack);
		if (recursion(pos->next, cells, flags, tetrs))
			return (1);
		tetrs[pos->tetrimino - 64] = 0;
		while (i < 4) // if i == 0;
			flags[pos->a[i++]] = '.';
		++tetrs[0];
		restore_nodes(pos, cells, &stack);
		if (pos->next == h_pos)
			break;
		pos = pos->next;
	}
	return (0);
}
