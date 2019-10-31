/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 22:10:17 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/10 21:07:00 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;

	str = (char*)malloc(sizeof(*str) * (ft_strlen(s1) + 1));
	if (str)
		ft_strcpy(str, s1);
	return (str);
}
