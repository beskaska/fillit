/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:44:50 by aimelda           #+#    #+#             */
/*   Updated: 2019/10/26 22:00:45 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		del(void *st, size_t s)
{
	s = 0;
	free(((t_fd*)st)->txt);
	free(st);
}

static int		fd_new(char *str, int fd, t_list **fd_lst)
{
	t_list	*tmp;

	if (*fd_lst)
		if (((t_fd*)((*fd_lst)->content))->fd == fd)
		{
			((t_fd*)((*fd_lst)->content))->cur = str;
			return (1);
		}
	if (!(tmp = ft_lstnew(NULL, 0)))
		return (0);
	ft_lstadd(fd_lst, tmp);
	if (!(tmp->content = (t_fd*)malloc(sizeof(t_fd))))
		return (0);
	if (!(((t_fd*)tmp->content)->txt = ft_strdup(str)))
		return (0);
	((t_fd*)tmp->content)->cur = ((t_fd*)tmp->content)->txt;
	((t_fd*)tmp->content)->fd = fd;
	return (1);
}

static int		is_eol(char **line, char *buf, t_list **fd_lst, int fd)
{
	char	*str;
	int		ret;

	ret = 0;
	str = buf;
	if ((str = ft_strchr(str, '\n')))
	{
		ret = 1;
		*(str++) = '\0';
		if (!(buf = ft_strjoin(*line, buf)))
			return (-1);
		if (*str == '\0' && *fd_lst)
			if (((t_fd*)((*fd_lst)->content))->fd == fd)
				((t_fd*)((*fd_lst)->content))->fd = -1;
		if (*str != '\0')
			if (!fd_new(str, fd, fd_lst))
				return (-1);
	}
	else if (!(buf = ft_strjoin(*line, buf)))
		return (-1);
	free(*line);
	*line = buf;
	return (ret);
}

static int		check_fd(int fd, t_list **head_lst, char **line)
{
	t_list	*fd_lst;
	t_list	*tmp;
	int		ret;

	fd_lst = *head_lst;
	tmp = NULL;
	while (fd_lst)
	{
		if (((t_fd*)((fd_lst)->content))->fd == fd)
		{
			ret = is_eol(line, ((t_fd*)((fd_lst)->content))->cur, &fd_lst, fd);
			if (!ret || (((t_fd*)((fd_lst)->content))->fd) == -1)
			{
				if (tmp)
					tmp->next = fd_lst->next;
				else
					*head_lst = fd_lst->next;
				ft_lstdelone(&fd_lst, del);
			}
			return (ret);
		}
		tmp = fd_lst;
		fd_lst = fd_lst->next;
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	char			*buf;
	static t_list	*fd_list;
	int				ret;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (!(buf = (char*)malloc(BUFF_SIZE + 1)))
		return (-1);
	*line = ft_strnew(0);
	if (!(ret = check_fd(fd, &fd_list, line)))
		while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			*(buf + ret) = '\0';
			if ((ret = is_eol(line, buf, &fd_list, fd)))
				break ;
		}
	free(buf);
	if ((!ret && **line != '\0') || ret == 1)
		return (1);
	free(*line);
	if (!ret)
		return (0);
	ft_lstdel(&fd_list, del);
	return (-1);
}
