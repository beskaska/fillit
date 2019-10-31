/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:14:37 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/15 17:43:23 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	det_sign(const char *s)
{
	if (*s == '-')
		return (-1);
	return (1);
}

int			ft_atoi(const char *str)
{
	size_t	res;
	int		sign;

	while (ft_isspace(*str))
		str++;
	res = 0;
	sign = det_sign(str);
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		if (res * 10 + *str - '0' > MAX_LL)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}
