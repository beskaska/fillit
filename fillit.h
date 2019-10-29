/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:45:16 by aimelda           #+#    #+#             */
/*   Updated: 2019/10/29 21:59:56 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

typedef	struct	s_brick
{
	int	i;
	int	j;
}				t_brick;

typedef	struct	s_tetr
{
	struct s_brick	brick_1;
	struct s_brick	brick_2;
	struct s_brick	brick_3;
	struct s_brick	brick_4;
	struct s_tetr	*next;
}				t_tetr;

#endif
