/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 21:06:30 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/11 16:06:41 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	freeing(t_tetr *tetrs)
{
	t_tetr	*tmp;

	while (tetrs)
	{
		tmp = tetrs;
		tetrs = tetrs->next;
		free(tmp);
	}
}

int			main(int argc, char **argv)
{
	int		n;
	int		a;
	t_tetr	*tetrs;

	tetrs = NULL;
	if (argc != 2)
		ft_putstr("usage: ./fillit source_file\n");
	else if	((n = parsing(argv[1], &tetrs)))
	{
		a = ft_sqrt(n * 4, 1);
		if (a * a < n * 4)
			a++;
		while (!(fillit(n, a++, tetrs)));
		freeing(tetrs);
	}
}
