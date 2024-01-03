/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:55:43 by idelfag           #+#    #+#             */
/*   Updated: 2022/11/07 11:57:33 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		l;

	str = (char *)s;
	l = ft_strlen(str);
	while (l >= 0)
	{
		if (str[l] == (char)c)
			return (&str[l]);
		l--;
	}
	return (NULL);
}
