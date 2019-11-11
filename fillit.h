/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:45:16 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/11 14:34:48 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define BUFF 600/* * */

# include "libft/libft.h"
# include "fcntl.h"
# include <stdio.h>/* DELETE */

typedef struct	s_tetr
{
	int				a[8];
	char			tetrimino;
	struct s_tetr	*next;
}				t_tetr;

typedef struct	s_pos
{
	int				a[4];
	char			tetrimino;
	struct s_pos	*next;
	struct s_pos	*prev;
}				t_pos;

typedef struct	s_cell
{
	t_pos			*pos;
	struct s_cell	*next;
	struct s_cell	*prev;
}				t_cell;

typedef struct	s_stack
{
	t_cell			*elem;
	struct s_stack	*next;
}				t_stack;

typedef struct	s_data/* * */
{
	int count;
	int i;
	int fst;
	int near;
}				t_data;

void			fillit(int n, int a, t_tetr *tetrs);
int				tracking(t_pos **head, t_cell **cells, char *flags, t_pos *pos);
void			rem_column(t_cell **cells, t_cell *cur, t_stack **stack, int j);/*test*/
int				parsing(char *txt, t_tetr **tetris);

#endif
