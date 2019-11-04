/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:45:48 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/04 23:06:39 by aimelda          ###   ########.fr       */
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
		//printf("In remove_nodes at cell = %i of POS{%i %i %i %i}\n", pos->a[i], pos->a[0], pos->a[1], pos->a[2], pos->a[3]);//DELETE
		cur = cells[pos->a[i]];
		while (cur) //пробегаемся по столбцу выбранной ячейки чтобы удалить позиции
		{
			j = -1;
			while (++j < 4)
			{//DELETE
			//printf("	at cell = %i of CUR_POS{%i %i %i %i}\n", cur->pos->a[j], cur->pos->a[0], cur->pos->a[1], cur->pos->a[2], cur->pos->a[3]);//DELETE
				if (pos->a[i] != cur->pos->a[j])
				{
					if (cells[cur->pos->a[j]] == cells[cur->pos->a[j]]->next)
					{
						new_node(stack, cells[cur->pos->a[j]], 1);
						cells[cur->pos->a[j]] = NULL;
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
							//printf("Program was there...\n");
							cells[cur->pos->a[j]] = tmp->next; //чтобы начало списка ячейки соответствовал валидному положению
							(*stack)->head = 1;
						}
					}
					//printf("		POS{%i %i %i %i} added to stack\n", (*stack)->elem->pos->a[0], (*stack)->elem->pos->a[1], (*stack)->elem->pos->a[2], (*stack)->elem->pos->a[3]);
				}
			}//DELETE
			cur->pos->next->prev = cur->pos->prev;
			cur->pos->prev->next = cur->pos->next;
			if (cur->pos == *h_pos) //test
					{// test
						cur->pos->head = 1;
						if (*h_pos == (*h_pos)->next) //test
							*h_pos = NULL; //test
						else // test
							*h_pos = (*h_pos)->next; //test
					}// test
			if (cur->next == cells[pos->a[i]])
				break;
			cur = cur->next;
		}
	}
}

static int	recursion(t_pos *pos, t_cell **cells, char *flags, char *tetrs)
{
	t_pos	*last_pos;

	if (!pos)//test
		return (0);//test
	last_pos = pos->prev;
	while (tetrs[pos->tetrimino - 64])
		if (pos == last_pos)
			return (0);
		else
			pos = pos->next;
	if (backtracking(pos, cells, flags, tetrs))
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
			{//DELETE
			//printf("	at cell = %i of CUR_POS{%i %i %i %i}\n", cur->pos->a[j], cur->pos->a[0], cur->pos->a[1], cur->pos->a[2], cur->pos->a[3]);//DELETE
				if (pos->a[i] != cur->pos->a[j])
				{
					//printf("		POS{%i %i %i %i} retrieved from stack\n", (*stack)->elem->pos->a[0], (*stack)->elem->pos->a[1], (*stack)->elem->pos->a[2], (*stack)->elem->pos->a[3]);
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
							cells[cur->pos->a[j]] = (*stack)->elem;
					}
					del_node(stack);
				}
			}//DELETE
			cur->pos->next->prev = cur->pos;
			cur->pos->prev->next = cur->pos;
			if (cur->pos->head) //test
			{//test
				*h_pos = (*stack)->elem->pos; //test
				cur->pos->head = 0;
			}//test
			if (cur == cells[pos->a[i]])
				break;
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
		if (!(tetrs[pos->tetrimino - 64])) //test
		{//test
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
		while (i < 4) // if i == 0;
			flags[pos->a[i++]] = '.';
		++tetrs[0];
		restore_nodes(pos, cells, &stack, &h_pos);
		}//test
		if (pos->next == h_pos)
			break;
		pos = pos->next;
	}
	return (0);
}
