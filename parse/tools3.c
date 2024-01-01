/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:22:03 by idelfag           #+#    #+#             */
/*   Updated: 2024/01/01 15:01:31 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	message_exit(char *msg, int n)
{
	write(2, "Error\n", 7);
	write(2, msg, ft_strlen(msg));
	exit(n);
}

void	msg_exit_free(char *msg, int n, t_vars *vars)
{
	if (vars->parse.obj)
		free(vars->parse.obj);
	free_tab(vars->lines);
	free_tab(vars->line);
	write(2, "Error\n", 7);
	write(2, msg, ft_strlen(msg));
	exit(n);
}
