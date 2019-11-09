/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:45:16 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/09 14:10:32 by aimelda          ###   ########.fr       */
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
	char			head;
	struct s_stack	*next;
}				t_stack;

typedef struct	s_usage
{
	t_pos			*head_pos;
	char			bool;
}				t_usage;

typedef struct	s_data/* * */
{
	int count;
	int i;
	int fst;
	int near;
}				t_data;

void			fillit(int n, int a, t_tetr *tetrs);
int				backtracking(t_usage **tetrs, t_cell **cells, char *flags, t_pos *pos);
int				parsing(char *txt, t_tetr **tetris);

#endif
