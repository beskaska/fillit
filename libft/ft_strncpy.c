/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 23:08:23 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/08 23:42:28 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*dest;

	dest = dst;
	while (*src != 0 && len > 0)
	{
		*dest++ = *src++;
		len--;
	}
	while (len-- > 0)
		*dest++ = 0;
	return (dst);
}
