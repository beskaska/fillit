/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 22:25:32 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/15 12:28:18 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;

	dest = (unsigned char*)dst;
	source = (unsigned char*)src;
	if (source > dest)
		while (len-- > 0)
			*(dest++) = *(source++);
	else if (source < dest)
		while (len-- > 0)
			*(dest + len) = *(source + len);
	return (dst);
}
