/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 23:21:37 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/15 13:18:54 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count(char const *s, char c)
{
	int		bool;
	int		res;

	bool = 0;
	res = 0;
	while (*s != '\0')
		if (*s++ != c)
		{
			if (!bool)
			{
				res++;
				bool = 1;
			}
		}
		else
			bool = 0;
	return (res);
}

static void		delete_all(char const **s, char **arr, size_t n)
{
	while (n-- > 0)
		free(arr[n]);
	free((void*)*s);
}

static size_t	find_word(char const **s, char c, char **arr, size_t n)
{
	size_t	res;

	res = 0;
	while (*(*s + res) != c && *(*s + res) != '\0')
		res++;
	arr[n] = ft_strnew(res);
	if (!(arr[n]))
	{
		delete_all(s, arr, n + 1);
		return (0);
	}
	return (res);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	size_t	n;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	n = count(s, c);
	res = (char**)malloc(sizeof(res) * n + 1);
	if (res)
	{
		i = 0;
		while (*s != '\0' && i < n)
		{
			while (*s == c)
				s++;
			len = find_word(&s, c, res, i);
			if (!len)
				return (NULL);
			ft_strncpy(res[i++], s, len);
			s = s + len;
		}
		res[n] = NULL;
	}
	return (res);
}
