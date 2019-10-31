/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:16:24 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/15 15:27:58 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	n = ft_min(ft_strlen(s2), n);
	*(ft_strncpy(s1 + ft_strlen(s1), s2, n) + n) = '\0';
	return (s1);
}
