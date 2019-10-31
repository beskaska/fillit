/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:59:46 by aimelda           #+#    #+#             */
/*   Updated: 2019/10/31 21:27:15 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_pos	init_pos(t_pos *pos, t_tetr *tetrs, int a, int i)
{
	if (pos)
	{
		if (!(pos->next = (t_pos*)malloc(sizeof(t_pos))))
			return (NULL);
		pos->next->prev = pos;
		pos	= pos->next;
	}
	else if (!(pos = (t_pos*)malloc(sizeof(t_pos))))
		return (NULL);
	pos->a[0] = i + (tetrs->a[0][0] * a) + tetrs->a[0][1];
	pos->a[1] = i + (tetrs->a[1][0] * a) + tetrs->a[1][1];
	pos->a[2] = i + (tetrs->a[2][0] * a) + tetrs->a[2][1];
	pos->a[3] = i + (tetrs->a[3][0] * a) + tetrs->a[3][1];
	pos->tetrimino = tetrs->tetrimino;
	return (pos);
}

static int		init_cell(t_pos *pos, t_cell **cells)
{
	int		i;
	t_cell	*tmp;

	i = -1;
	while (++i < 4)
	{
		if ((tmp = cells[pos->a[i]]))
		{
			while (tmp->next)
				tmp = tmp->next;
			if (!(tmp->next = (t_cell)malloc(sizeof(t_cell))))
				return (0);
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		else if (!(cells[pos->a[i]] = (t_cell)malloc(sizeof(t_cell))))
			return (0);
		else
			tmp = cells[pos->a[i]];
		tmp->pos = pos;
		tmp->next = cells[pos->a[i]];
		cells[pos->a[i]]->prev = tmp;
	}
	return (1);
}

static int		inits(t_pos **head_pos, t_cell **cells, int a, t_tetr *tetrs)
{
	int		n;
	int		i;
	t_pos	*pos;

	n = a * a;
	pos = NULL;
	*head_pos = NULL;
	while (*tetrs)
	{
		i = 0;
		while (i < n - 3)
			if (tetrs->a[3][0] * a + i < n &&
				(ft_max(tetrs->a[2][1], tetrs->a[3][1]) + i) / a == i / a)
			{
				if (!(pos = init_pos(pos, tetrs, a, i++)))
					return (0);
				if (!(*head_pos))
					*head_pos = pos;
				if (!(init_cell(pos, cells)))
					return (0);
			}
		tetrs++;
	}
	pos->next = *head_pos;
	(*head_pos)->prev = pos;
	return (1);
}

void			fillit(int n, int a, t_tetr *tetrs)
{
	t_pos	*pos;
	t_cell	cells[a * a];
	char	flags[a * a];
	char	tetriminos[n + 1];

	ft_bzero(cells, sizeof(cells)); // need to check;
	ft_bzero(flags, sizeof(flags)); // need to fill by "." characters;
	ft_bzero(tetriminos, sizeof(tetriminos)); // need to check;
	tetriminos[0] = n;
	if (inits(&pos, cells, a, tetrs)) //correct
		backtracking(pos, cells, flags, tetriminos); //correct
	else
		//free all allocated memory and exit;
}
