/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 07:13:08 by idelfag           #+#    #+#             */
/*   Updated: 2022/10/25 08:21:19 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
	}
	else
	{
		if (n < 0)
		{
			ft_putchar_fd(('-'), fd);
			n *= -1;
			ft_putnbr_fd(n, fd);
		}
		else if (n < 10)
			ft_putchar_fd((n + 48), fd);
		else
		{
			ft_putnbr_fd((n / 10), fd);
			ft_putchar_fd((n % 10 + 48), fd);
		}
	}
}
