/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 19:42:20 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/15 12:14:28 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;

	dest = (unsigned char*)dst;
	source = (unsigned char*)src;
	while (n-- > 0 && (dest || source))
		*(dest++) = *(source++);
	return (dst);
}
