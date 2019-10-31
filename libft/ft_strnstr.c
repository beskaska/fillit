/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:24:05 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/13 15:05:41 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*stack;
	char	*delta;
	size_t	i;

	if (*needle == '\0')
		return ((char*)haystack);
	delta = (char*)haystack +
			(ft_min(ft_strlen(haystack), len) - ft_strlen(needle));
	stack = (char*)haystack;
	while (stack <= delta)
	{
		i = 0;
		if ((stack = ft_strchr(stack, (int)needle[i++])) && stack <= delta)
			while (needle[i] != '\0' && stack[i] == needle[i])
				i++;
		else
			return (NULL);
		if (needle[i] == '\0')
			return (stack);
		stack++;
	}
	return (NULL);
}
