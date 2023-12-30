/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:00:48 by idelfag           #+#    #+#             */
/*   Updated: 2022/11/07 11:57:32 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*str;
	char	*c;
	size_t	j;

	i = 0;
	str = (char *)haystack;
	c = (char *)needle;
	if (*c && len == 0)
		return (0);
	if (*c == 0)
		return (str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] && str[i + j] == c[j] && i + j < len)
			j++;
		if (c[j] == '\0')
			return (&str[i]);
		i++;
	}
	return (0);
}
