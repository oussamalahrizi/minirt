/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:45:51 by idelfag           #+#    #+#             */
/*   Updated: 2022/11/07 11:56:24 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	l;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	l = (int)ft_strlen(s1) - 1;
	if (!ft_strlen(s1))
		l = 0;
	while (s1[l] && ft_strchr(set, s1[l]))
		l--;
	return (ft_substr(s1, 0, l + 1));
}
