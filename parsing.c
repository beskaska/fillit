/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:04:39 by pmelodi           #+#    #+#             */
/*   Updated: 2019/11/04 21:46:22 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		error()
{
	ft_putstr("error\n");
	exit(1);
}

static int		has_neighbour(int i, char *buff)
{
	if (i != 0)
	{
		if (buff[i - 1] == '#')
			return (1);
	}
	if (buff[i + 1] == '#')
		return (1);
	if (i > 4)
	{
		if (buff[i - 5] == '#')
			return (1);
	}
	if (i < 14)
	{
		if (buff[i + 5] == '#')
			return (1);
	}
	return (0);
}

static void		forchest(t_data *data, char *buff, int *piece)
{
	if (!has_neighbour(data->i, buff))
		error();
	if (!(data->count))
	{
		(piece[0]) = 0;
		(piece[1]) = 0;
		data->fst = data->i;
	}
	else
	{
		(piece[(2*(data->count))]) = (data->i) / 5  - (data->fst) / 5 ;
		(piece[2*(data->count) + 1]) = (data->i + 1) % 5 - (data->fst + 1) % 5;
	}
	data->count += 1;
}

static void		tetrimina(char *buff, t_tetr *tetris)
{
	t_data *data;

	data = (t_data *)ft_memalloc(sizeof(t_data));
	while (data->i < 20 && data->count < 5)
	{
		if (((data->i + 1) % 5) == 0)
		{
			if (buff[data->i] != '\n')
				error();
			else
			{
				data->i += 1;
				continue;
			}
		}
		if (buff[data->i] == '#')
			forchest(data, buff, tetris->a);
		else if (buff[data->i] != '.')
			error();
		data->i++;
	}
	if (data->i != 20 || data->count != 4 || buff[20] != '\n')
		error();
	free(data);
	data = NULL;
	return ;
}

static void		another_format(t_tetr *tetris)
{
	int j;
	int neg;

	while (tetris)
	{
		j = 0;
		while (j < 8)
		{
			if (tetris->a[j] < 0)
			{
				neg = tetris->a[j];
				tetris->a[1] -= neg;
				tetris->a[3] -= neg;
				tetris->a[5] -= neg;
				tetris->a[7] -= neg;
				break;
			}
			j++;
		}
		tetris = tetris->next;
	}
}

int		parsing(char *txt, t_tetr **tetris)
{
	t_tetr		*tmp;
	char		buff[BUFF];
	int			len;
	int			fd;
	int			nums;

	nums = 0;
	fd = open(txt, O_RDONLY);
	len = read(fd, buff, BUFF);
	tmp = *tetris;
	if ((len - 20) % 21 != 0)
		error();
	else
	{
		buff[len] = '\n';
		nums = (len - 20) / 21 + 1;
		len = 0;
		while (len < nums)
		{
			if (!(*tetris))
			{
				*tetris = (t_tetr*)malloc(sizeof(t_tetr));
				tmp = *tetris;
			}
			else
			{
				tmp->next = (t_tetr*)malloc(sizeof(t_tetr));
				tmp = tmp->next;
			}
			tmp->tetrimino = 'A' + len;
			tetrimina(buff + len * 21, tmp);
			len++;
		}
		tmp->next = NULL;
	}
	another_format(*tetris);
	close(fd);
	return (nums);
}
