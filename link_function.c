/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:46:30 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/11 19:13:27 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		another_format(t_tetr *tetris)
{
	int j;
	int neg;

	while (tetris)
	{
		j = 0;
		while (j < 8)
		{
			if (tetris->a[j] < 0)
			{
				neg = tetris->a[j];
				tetris->a[1] -= neg;
				tetris->a[3] -= neg;
				tetris->a[5] -= neg;
				tetris->a[7] -= neg;
				break ;
			}
			j++;
		}
		tetris = tetris->next;
	}
}

t_tetr		*new_tetr(t_tetr **tetris)
{
	static int		tetrimino;
	static t_tetr	*tmp;

	if (!tmp)
	{
		*tetris = (t_tetr*)malloc(sizeof(t_tetr));
		tmp = *tetris;
	}
	else
	{
		tmp->next = (t_tetr*)malloc(sizeof(t_tetr));
		tmp = tmp->next;
	}
	tmp->tetrimino = 'A' + tetrimino++;
	tmp->next = NULL;
	return (tmp);
}
