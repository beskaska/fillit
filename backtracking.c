/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:45:48 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/11 18:36:05 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	freeing(t_stk **stack)
{
	t_stk	*tmp;
	int		i;

	while (*stack)
	{
		free((*stack)->elem->pos);
		i = 0;
		while (i++ < 3)
		{
			free((*stack)->elem);
			tmp = *stack;
			*stack = (*stack)->next;
			free(tmp);
		}
	}
	return (1);
}

int			tracking(t_pos **tetrs, t_cell **cells, char *flags, t_pos *pos)
{
	t_stk		*stack;
	int			i;

	stack = NULL;
	while (pos)
	{
		i = 4;
		while (i-- > 0)
			flags[pos->a[i] + 1] = pos->tetrimino;
		if (pos->tetrimino - 64 == flags[0])
			return (1);
		if ((i = removing(pos, cells, &stack, tetrs)) < 4)
			i++;
		else if (tracking(tetrs, cells, flags, tetrs[pos->tetrimino - 64]))
			return (freeing(&stack));
		while (stack)
			if (cells[pos->a[--i]])
				restoring(pos->a[i], cells, &stack, tetrs);
		i = 0;
		while (i < 4)
			flags[pos->a[i++] + 1] = '.';
		pos = pos->next;
	}
	return (0);
}
