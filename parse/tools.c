/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:05:45 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/29 14:30:53 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	skip_char(char *line, char c, int *index, char *str)
{
	if (line[*index] != c || !line[*index])
	{
		write(2, "error while parcing ", 21);
		ft_putendl_fd(str, 2);
		exit(1);
	}
	(*index)++;
	if (!line[*index])
	{
		write(2, "error while parcing ", 21);
		ft_putendl_fd(str, 2);
		exit(1);
	}
}

int	ft_isspace(int c)
{
	if (ft_strchr("\t\n\v\f\r ", c))
		return (1);
	return (0);
}

float	get_fractal_part(char *str, int *index, int sign)
{
	float	res;
	int		i;
	float	j;

	i = *index;
	res = 0.0;
	if (str[i] == '.')
	{
		i++;
		j = 0.1;
		while (ft_isdigit(str[i]))
		{
			res = res + sign * j * (str[i] - '0');
			j /= 10;
			i++;
		}
	}
	*index = i;
	return (res);
}

float	get_number(char *str, int *index, int sign)
{
	float	res;
	int		i;

	i = *index;
	res = 0.0;
	if (!ft_isdigit(str[i]))
		message_exit("parsing Number", 1);
	while (ft_isdigit(str[i]))
	{
		res = 10 * res + sign * (str[i] - '0');
		i++;
	}
	res += get_fractal_part(str, &i, sign);
	*index = i;
	return (res);
}

float	parse_number(char *str, int *index)
{
	int		i;
	float	res;
	int		sign;

	i = *index;
	res = 0.0;
	sign = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (ft_strchr("+-", str[i]))
	{
		if (str[i] == '-')
			sign = -1;
		skip_char(str, str[i], &i, "number");
	}
	res = get_number(str, &i, sign);
	while (str[i] && ft_isspace(str[i]))
		i++;
	*index = i;
	return (res);
}
