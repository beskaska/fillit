/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:04:39 by pmelodi           #+#    #+#             */
/*   Updated: 2019/11/11 19:11:03 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		error(void)
{
	ft_putstr("error\n");
	exit(1);
}

static int		has_neighbour(int i, char *buff, t_data *data)
{
	int tmp;

	tmp = 0;
	if (i != 0)
	{
		if (buff[i - 1] == '#')
			tmp += 1;
	}
	if (buff[i + 1] == '#')
		tmp += 1;
	if (i > 4)
	{
		if (buff[i - 5] == '#')
			tmp += 1;
	}
	if (i < 14)
	{
		if (buff[i + 5] == '#')
			tmp += 1;
	}
	if (!tmp)
		return (0);
	if (tmp > data->near)
		data->near = tmp;
	return (1);
}

static void		forchest(t_data *data, char *buff, int *piece)
{
	if (!has_neighbour(data->i, buff, data))
		error();
	if (!(data->count))
	{
		(piece[0]) = 0;
		(piece[1]) = 0;
		data->fst = data->i;
	}
	else
	{
		piece[2 * (data->count)] = (data->i) / 5 - (data->fst) / 5;
		piece[2 * (data->count) + 1] = (data->i + 1) % 5 - (data->fst + 1) % 5;
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
	if (data->i != 20 || data->count != 4 || buff[20] != '\n' || data->near < 2)
		error();
	free(data);
	return ;
}

int				parsing(char *txt, t_tetr **tetris)
{
	char		buff[BUFF];
	int			len;
	int			fd;
	int			nums;

	nums = 0;
	if ((fd = open(txt, O_RDONLY)) < 0)
		error();
	len = read(fd, buff, BUFF);
	if ((len - 20) % 21 != 0)
		error();
	else
	{
		buff[len] = '\n';
		if ((nums = (len - 20) / 21 + 1) > 26)
			error();
		len = -1;
		while (++len < nums)
			tetrimina(buff + len * 21, new_tetr(tetris));
	}
	another_format(*tetris);
	close(fd);
	return (nums);
}
