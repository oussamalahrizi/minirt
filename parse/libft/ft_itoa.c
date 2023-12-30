/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 21:30:44 by idelfag           #+#    #+#             */
/*   Updated: 2022/11/07 11:56:41 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	cal_len(long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	size_t	i;
	size_t	len;

	nbr = n;
	str = malloc(sizeof(char) * (cal_len(nbr) + 1));
	if (!str)
		return (NULL);
	i = cal_len(nbr) - 1;
	len = cal_len(nbr);
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		str[i--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[len] = '\0';
	return (str);
}
