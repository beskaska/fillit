/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 21:06:30 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/03 21:34:06 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static double	ft_sqrt(double n, double precision)
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

int		main(int argc, char **argv)
{
	int		n;
	int		a;
	t_tetr	*tetrs;

	tetrs = NULL;
	if (argc != 2)
		ft_putstr("usage: ./fillit source_file\n");
	else if	((n = input_handling(argv[1], &tetrs)))
	{
		a = ft_sqrt(n * 4, 1);
		if (a * a < n * 4)
			a++;
		while (1)
		{
			printf("Size of square's side = %i\n", a); //DELETE
			fillit(n, a++, tetrs);
		}
	}
}
