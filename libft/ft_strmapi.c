/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:27:15 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/13 18:22:36 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	size_t	i;

	if (s && f)
	{
		i = 0;
		res = ft_strnew(ft_strlen(s));
		if (res)
			while (*s != '\0')
			{
				res[i] = f(i, *s++);
				i++;
			}
		return (res);
	}
	return (NULL);
}
