/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:46:37 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/31 01:32:37 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_validity(char *name)
{
	int	i;

	i = (ft_strlen(name) - 1);
	if (name[i] == 't' && name[i - 1] == 'r'
		&& name[i - 2] == '.' && name[i - 3] != '.')
		return (1);
	return (0);
}

int	read_file(int fd, t_vars *vars)
{
	char	*buff;
	char	*file;
	int		readed;

	readed = 1;
	buff = malloc(sizeof(char) * 11);
	file = (char *)ft_calloc(1, 1);
	while (readed)
	{
		readed = read(fd, buff, 10);
		if (readed < 0)
		{
			free(buff);
			free(file);
			return (0);
		}
		buff[readed] = 0;
		file = ft_strjoin(file, buff);
	}
	free(buff);
	vars->lines = ft_split(file, '\n');
	free(file);
	return (1);
}

void	parse(int ac, char **av, t_vars *vars)
{
	int		fd;

	if (ac != 2)
		message_exit("Invalid args !\n", 1);
	if (!check_validity(av[1]))
		message_exit("filename format is not valid\n", 1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		message_exit("failed to open the file\n", 1);
	if (!read_file(fd, vars))
		message_exit("Something gone wrong\n", 1);
	get_content(vars);
	vars->cam = vars->parse.cam;
	vars->lights = &vars->parse.light;
	vars->objects = vars->parse.obj;
	close(fd);
}
