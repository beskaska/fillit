/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 20:51:14 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/09 21:08:15 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char*)s;
	while (*str != '\0')
		if (*(str++) == (char)c)
			return (str - 1);
	if ((char)c == '\0')
		return (str);
	return (NULL);
}
