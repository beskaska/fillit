/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 23:25:07 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/13 17:50:11 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	size_t	i;

	if (s && f)
	{
		i = 0;
		res = ft_strnew(ft_strlen(s));
		if (res)
			while (*s != '\0')
				res[i++] = f(*s++);
		return (res);
	}
	return (NULL);
}
