/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:08:00 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/13 15:30:43 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long int	nb;

	nb = 10;
	if (n < 0)
		ft_putchar('-');
	while (n / nb != 0)
		nb *= 10;
	if (n == 0)
		ft_putchar('0');
	else
		while (nb != 1)
		{
			nb /= 10;
			ft_putchar(ft_abs(n / nb) + '0');
			n = n % nb;
		}
}
