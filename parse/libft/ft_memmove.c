/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:52:20 by idelfag           #+#    #+#             */
/*   Updated: 2022/11/07 11:57:02 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src < dst)
	{
		while (len > 0)
		{
			*(unsigned char *)(dst + len - 1) = *(unsigned char *)(src + len
					- 1);
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
