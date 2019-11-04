/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:45:16 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/04 22:58:43 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "libft/libft.h"
#include "fcntl.h"
#include <stdio.h> //DELETE
# define BUFF 600 //*

typedef	struct	s_tetr
{
	int				a[8];
	char			tetrimino;
	struct s_tetr	*next;
}				t_tetr;

typedef	struct s_pos
{
	int				a[4];
	char			tetrimino;
	char			head;//test
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

typedef struct	s_data //*
{
	int count;
	int i;
	int fst;
}				t_data;

void			fillit(int n, int a, t_tetr *tetrs);
int				backtracking(t_pos *h_pos, t_cell **cells, char *flags, char *tetrs);
int				parsing(char *txt, t_tetr **tetris);

#endif
