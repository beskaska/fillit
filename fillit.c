/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:59:46 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/11 18:38:18 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		freeing(t_pos **head, t_cell **cells, int n, int m)
{
	t_pos	*tmp_pos;
	t_cell	*tmp_cell;

	while (n--)
		while (head[n])
		{
			tmp_pos = head[n];
			head[n] = head[n]->next;
			free(tmp_pos);
		}
	while (m--)
		while (cells[m])
		{
			tmp_cell = cells[m];
			cells[m] = cells[m]->next;
			free(tmp_cell);
		}
	return (1);
}

static t_pos	*i_pos(t_pos *pos, t_tetr *tetrs, int a, int i)
{
	if (pos)
	{
		if (!(pos->next = (t_pos*)malloc(sizeof(t_pos))))
			return (NULL);
		pos->next->prev = pos;
		pos = pos->next;
	}
	else if (!(pos = (t_pos*)malloc(sizeof(t_pos))))
		return (NULL);
	pos->a[0] = i + (tetrs->a[0] * a) + tetrs->a[1];
	pos->a[1] = i + (tetrs->a[2] * a) + tetrs->a[3];
	pos->a[2] = i + (tetrs->a[4] * a) + tetrs->a[5];
	pos->a[3] = i + (tetrs->a[6] * a) + tetrs->a[7];
	pos->tetrimino = tetrs->tetrimino;
	return (pos);
}

static int		i_cell(t_pos *pos, t_cell **cells)
{
	int		i;
	t_cell	*tmp;

	i = -1;
	while (++i < 4)
	{
		if ((tmp = cells[pos->a[i]]))
		{
			tmp = tmp->prev;
			if (!(tmp->next = (t_cell*)malloc(sizeof(t_cell))))
				return (0);
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		else if (!(cells[pos->a[i]] = (t_cell*)malloc(sizeof(t_cell))))
			return (0);
		else
			tmp = cells[pos->a[i]];
		tmp->pos = pos;
		tmp->next = NULL;
		cells[pos->a[i]]->prev = tmp;
	}
	return (1);
}

static int		inits(t_pos **head, t_cell **cells, int a, t_tetr *tetrs)
{
	int		i;
	t_pos	*pos;

	while (tetrs)
	{
		pos = NULL;
		i = -1;
		while (++i < a * a - 3)
			if (tetrs->a[6] * a + i < a * a && ((int)ft_max(ft_max(tetrs->a[3],
			tetrs->a[5]), tetrs->a[7]) + i) / a == i / a)
			{
				if (!(pos = i_pos(pos, tetrs, a, i)) || !(i_cell(pos, cells)))
					return (0);
				if (!(head[pos->tetrimino - 65]))
					head[pos->tetrimino - 65] = pos;
			}
		if (head[tetrs->tetrimino - 65])
		{
			pos->next = NULL;
			head[tetrs->tetrimino - 65]->prev = NULL;
		}
		tetrs = tetrs->next;
	}
	return (1);
}

int				fillit(int n, int a, t_tetr *tetrs)
{
	t_cell	*cells[a * a];
	char	flags[a * a + 1];
	t_pos	*head[n];
	int		i;

	i = 0;
	while (i <= n)
		head[i++] = NULL;
	i = 0;
	flags[0] = n;
	while (i < a * a)
	{
		cells[i++] = NULL;
		flags[i] = '.';
	}
	if (!(inits(head, cells, a, tetrs)))
		return (freeing(head, cells, n, a * a));
	if (tracking(head, cells, flags, head[0]))
	{
		print_square(flags, a);
		return (freeing(head, cells, n, a * a));
	}
	else
		freeing(head, cells, n, a * a);
	return (0);
}
