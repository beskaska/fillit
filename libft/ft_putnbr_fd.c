/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:18:17 by aimelda           #+#    #+#             */
/*   Updated: 2019/09/13 15:30:54 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = 10;
	if (n < 0)
		ft_putchar_fd('-', fd);
	while (n / nb != 0)
		nb *= 10;
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
		while (nb != 1)
		{
			nb /= 10;
			ft_putchar_fd(ft_abs(n / nb) + '0', fd);
			n = n % nb;
		}
}
