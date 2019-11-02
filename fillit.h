/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:45:16 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/02 23:39:02 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "libft/libft.h"
#include "fcntl.h"
#include <stdio.h> //DELETE

typedef	struct	s_tetr
{
	/* Описание тетриминки */
	/* В массиве перечислены блоки тетриминки, слева направо, начиная с верхнего */
	/* Каждая строка массива соответствует одному блоку тетриминки */
	/* Каждый столбец строки описывает насколько смещен данный блок ... */
	/* Первый столбец - относительно самого верхнего блока текущей тетриминки */
	/* Первый столбец - относительно самого верхнего блока текущей тетриминки */
	int				a[8];
	char			tetrimino; /* Буквенное обозначение тетр-ки (от A до Z) */
	struct s_tetr	*next; /* Указатель на следующую тетриминку */
}				t_tetr;

typedef	struct s_pos
{
	int				a[4];
	char			tetrimino;
	struct s_pos	*next;
	struct s_pos	*prev;
}				t_pos;

typedef struct s_cell
{
	t_pos			*pos;
	struct s_cell	*next;
	struct s_cell	*prev;
}				t_cell;

typedef struct s_stack
{
	t_cell			*elem;
	char			head;
	struct s_stack	*next;
}				t_stack;


void			fillit(int n, int a, t_tetr *tetrs);
int				backtracking(t_pos *h_pos, t_cell **cells, char *flags, char *tetrs);
int				input_handling(char *txt, t_tetr **tetrs);

#endif
