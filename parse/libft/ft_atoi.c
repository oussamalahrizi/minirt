/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:11:08 by idelfag           #+#    #+#             */
/*   Updated: 2022/11/11 09:46:22 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long	n;
	int				sign;

	sign = 1;
	n = 0;
	while (str[0] == 32 || (str[0] >= 9 && str[0] <= 13))
		str++;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(str[0]))
	{
		n *= 10;
		n += (str[0] - '0');
		str++;
		if (n > LLONG_MAX && sign == -1)
			return (0);
		if (n > LLONG_MAX && sign == 1)
			return (-1);
	}
	return ((int)n * sign);
}
