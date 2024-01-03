/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:05:45 by idelfag           #+#    #+#             */
/*   Updated: 2024/01/01 14:22:54 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	skip_char(char *line, char c, int *index, t_vars *vars)
{
	if (line[*index] != c || !line[*index])
		msg_exit_free("Error\n check configuration file\n", 1, vars);
	(*index)++;
	if (!line[*index])
		msg_exit_free("Error\n check configuration file\n", 1, vars);
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

float	get_number(char *str, int *index, int sign, t_vars *vars)
{
	float	res;
	int		i;

	i = *index;
	res = 0.0;
	if (!ft_isdigit(str[i]))
		msg_exit_free("Error\nparsing Number", 1, vars);
	while (ft_isdigit(str[i]))
	{
		res = 10 * res + sign * (str[i] - '0');
		i++;
	}
	res += get_fractal_part(str, &i, sign);
	*index = i;
	return (res);
}

float	parse_number(char *str, int *index, t_vars *vars)
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
		skip_char(str, str[i], &i, vars);
	}
	res = get_number(str, &i, sign, vars);
	while (str[i] && ft_isspace(str[i]))
		i++;
	*index = i;
	return (res);
}
