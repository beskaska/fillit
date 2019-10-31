/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 21:11:16 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/09 21:13:36 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*res;

	str = (char*)s;
	res = NULL;
	while (*str != '\0')
		if (*(str++) == (char)c)
			res = str - 1;
	if ((char)c == '\0')
		return (str);
	return (res);
}
