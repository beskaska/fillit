/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 22:33:36 by aimelda           #+#    #+#             */
/*   Updated: 2019/10/15 16:58:59 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	l1;
	size_t	l2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = (char*)malloc(l1 + l2 + 1);
	if (res)
	{
		ft_strcpy(ft_strcpy(res, s1) + l1, s2);
		res[l1 + l2] = '\0';
	}
	return (res);
}
