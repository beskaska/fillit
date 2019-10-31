/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 21:14:56 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/10 14:17:26 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*stack;
	char	*delta;
	size_t	i;

	if (*needle == '\0')
		return ((char*)haystack);
	delta = (char*)haystack + (ft_strlen(haystack) - ft_strlen(needle));
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
