/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 23:21:37 by aimelda           #+#    #+#             */
/*   Updated: 2019/11/02 22:37:08 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		input_handling(char *txt, t_tetr **tetrs)
{
	int		fd;
	char	*line;
	t_tetr	*tmp;
	int		i;
	int		j;

	j = 0;
	tmp = *tetrs;
	fd = open(txt, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(*tetrs))
		{
			*tetrs = (t_tetr*)malloc(sizeof(t_tetr));
			tmp = *tetrs;
		}
		else
		{
			tmp->next = (t_tetr*)malloc(sizeof(t_tetr));
			tmp = tmp->next;
		}
		i = 0;
		tmp->tetrimino = 'A' + j++;
		while (i < 8)
		{
			tmp->a[i] = *(line + i) - 48;
			i++;
		}
		tmp->next = NULL;
		//printf("%s\n", line);
		//printf("%i %i\n%i %i\n%i %i\n%i %i\n", tmp->a[0], tmp->a[1], tmp->a[2], tmp->a[3], tmp->a[4], tmp->a[5], tmp->a[6], tmp->a[7]);
		//printf("%c\n", tmp->tetrimino);
		free(line);
	}
	return (j);
}
/*
{
	int		fd;
	int		row;
	char	*line;

	row = 0;
	fd = open(txt, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (*line == '\0')
		{
			if (row < 4)
			{
				ft_putstr("error\n"); // is it need to free allocated at *tetrs?
				return (0);
			}
			row = 0;
		}
		free(line);
	}
	close(fd);
}
*/