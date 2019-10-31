/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:44:12 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/15 12:25:54 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;

	dest = (unsigned char*)dst;
	source = (unsigned char*)src;
	while (n-- > 0)
		if (*source == (unsigned char)c)
		{
			*(dest++) = *source;
			return (dest);
		}
		else
			*(dest++) = *(source++);
	return (NULL);
}
