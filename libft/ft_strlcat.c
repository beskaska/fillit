/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:40:21 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/09 20:19:33 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	n;

	len_dst = ft_strlen(dst);
	if (size <= len_dst)
		return (size + ft_strlen(src));
	n = size - len_dst - 1;
	*(ft_strncpy(dst + len_dst, src, n) + n) = '\0';
	return (len_dst + ft_strlen(src));
}
