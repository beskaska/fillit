/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:35:13 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/15 17:47:33 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int			len;
	long long	nb;
	char		*res;

	len = 1;
	nb = 10;
	while (n / nb != 0)
	{
		len++;
		nb *= 10;
	}
	nb = 0;
	if (n < 0)
		nb = 1;
	res = ft_strnew(len + nb);
	if (!res)
		return (NULL);
	if (n < 0)
		res[0] = '-';
	while (len-- > 0)
	{
		res[len + nb] = ft_abs(n) % 10 + '0';
		n /= 10;
	}
	return (res);
}
