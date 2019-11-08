/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:59:46 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/09 00:25:24 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		print_ans(char *flags, int a)
{
	int		i;

	i = 0;
	while (i < a * a)
	{
		ft_putchar(flags[i++]);
		if (i % a == 0)
			ft_putchar('\n');
	}
}

static t_pos	*i_pos(t_pos *pos, t_tetr *tetrs, int a, int i)
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
	pos->a[0] = i + (tetrs->a[0] * a) + tetrs->a[1];
	pos->a[1] = i + (tetrs->a[2] * a) + tetrs->a[3];
	pos->a[2] = i + (tetrs->a[4] * a) + tetrs->a[5];
	pos->a[3] = i + (tetrs->a[6] * a) + tetrs->a[7];
	pos->tetrimino = tetrs->tetrimino;
	pos->head = 0;/* test */
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
		tmp->next = cells[pos->a[i]];
		cells[pos->a[i]]->prev = tmp;
	}
	return (1);
}

static int		inits(t_usage **usage, t_cell **cells, int a, t_tetr *tetrs)/* test */
{
	int		n;
	int		i;
	t_pos	*pos;

	n = a * a;
	pos = NULL;
	//*head_pos = NULL;
	while (tetrs)
	{
		i = -1;
		while (++i < n - 3)
			if (tetrs->a[6] * a + i < n &&
				((int)ft_max(ft_max(tetrs->a[3], tetrs->a[5]), tetrs->a[7]) + i) / a == i / a)
			{
				if (!(pos = i_pos(pos, tetrs, a, i)) || !(i_cell(pos, cells)))
					return (0);
				//if (!(*head_pos))
				//	*head_pos = pos;
				if (!(usage[pos->tetrimino - 65]->head_pos))/* test */
					usage[pos->tetrimino - 65]->head_pos = pos;/* test */
			}
		tetrs = tetrs->next;
	}
	if (pos)
	{
		pos->next = NULL;
		//(*head_pos)->prev = NULL;
		usage[0]->head_pos->prev = NULL;/* test */
	}
	return (1);
}

void			fillit(int n, int a, t_tetr *tetrs)
{
	//t_pos	*pos;
	t_cell	*cells[a * a];
	char	flags[a * a];
	t_usage	*usage[n + 1];/* test */
	int		i;/* test */

	i = 0;/* test */
	while (i <= n)/* test */
	{/* test */
		usage[i] = (t_usage*)malloc(sizeof(t_usage));/* test */
		usage[i]->bool = 0;/* test */
		usage[i++]->head_pos = NULL;/* test */
	}/* test */
	usage[0]->bool = n;/* test */
	i = 0;/* test */
	while (i < a * a)/* test */
	{
		flags[i] = '.';/* test */
		cells[i++] = NULL;/* test */
	}
	if (!(inits(usage, cells, a, tetrs)))/* test */
		exit(0);/* is it need to free all allocated memory? */
	if (backtracking(usage, cells, flags, usage[0]->head_pos))/* test */
	{
		print_ans(flags, a);
		exit(0);/* is it need to free all allocated memory? */
	}
}
