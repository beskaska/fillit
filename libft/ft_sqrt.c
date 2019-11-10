/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:07:15 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/10 15:15:29 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** According to the Newton's method **
*/

#include "libft.h"

double	ft_sqrt(double n, double precision)
{
	double	x;
	double	tmp;

	x = 1;
	while (1)
	{
		tmp = (x + n / x) / 2;
		if (ft_abs(x - tmp) < precision)
			return (x);
		x = tmp;
	}
}
