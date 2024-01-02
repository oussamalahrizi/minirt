/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:46:24 by idelfag           #+#    #+#             */
/*   Updated: 2024/01/01 22:51:37 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parse.h"

int	check_cone(t_object *obj)
{
	if ((obj->d_normal.x < -1.0f) || (obj->d_normal.x > 1.0f))
		return (0);
	if ((obj->d_normal.y < -1.0f) || (obj->d_normal.y > 1.0f))
		return (0);
	if ((obj->d_normal.z < -1.0f) || (obj->d_normal.z > 1.0f))
		return (0);
	if ((obj->base_color.x < 0.0f) || (obj->base_color.x > 1.0f))
		return (0);
	if ((obj->base_color.y < 0.0f) || (obj->base_color.y > 1.0f))
		return (0);
	if ((obj->base_color.z < 0.0f) || (obj->base_color.z > 1.0f))
		return (0);
	return (1);
}

void	cone_position(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	vars->parse.obj[*index].type = CONE;
	vars->parse.obj[*index].translation.x = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].translation.y = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].translation.z = parse_number(line[*i], &j, vars);
	if (line[*i][j])
		msg_exit_free("parsing cone infos\n", 1, vars);
	(*i)++;
}

void	cone_dnormal(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	vars->parse.obj[*index].d_normal.x = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].d_normal.y = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].d_normal.z = parse_number(line[*i], &j, vars);
	if (line[*i][j])
		msg_exit_free("parsing cone infos\n", 1, vars);
	(*i)++;
}

void	cone_scale_color(char **line, t_vars *vars, int *index, int *i)
{
	int	j;

	j = 0;
	vars->parse.obj[*index].scale.x = (parse_number(line[*i], &j, vars) / 2.f);
	j = 0;
	vars->parse.obj[*index].scale.y = (parse_number(line[*i], &j, vars) / 2.f);
	(*i)++;
	j = 0;
	vars->parse.obj[*index].scale.z = parse_number(line[*i], &j, vars);
	if (line[*i][j])
		msg_exit_free("parsing cone infos\n", 1, vars);
	(*i)++;
	j = 0;
	vars->parse.obj[*index].base_color.x = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].base_color.y = parse_number(line[*i], &j, vars);
	skip_char(line[*i], ',', &j, vars);
	vars->parse.obj[*index].base_color.z = parse_number(line[*i], &j, vars);
	vars->parse.obj[*index].base_color.x /= 255.f;
	vars->parse.obj[*index].base_color.y /= 255.f;
	vars->parse.obj[*index].base_color.z /= 255.f;
	if (line[*i][j])
		msg_exit_free("parsing cone infos\n", 1, vars);
  (*i)++;
}

void	parse_cone(char **line, t_vars *vars, int *index)
{
	int	i;

	i = 1;
	if (!(ft_tablen(line) >= 6 && ft_tablen(line) <= 15))
		msg_exit_free("parsing cone infos\n", 1, vars);
	cone_position(line, vars, index, &i);
	cone_dnormal(line, vars, index, &i);
	cone_scale_color(line, vars, index, &i);
  while(line[i])
	{
		if (line[i][0] == 'r' || line[i][0] == 's')
			parse_reflectivity(line, vars, index, &i);
		else if (line[i][0] == 't')
			parse_texture(line, vars, index, &i);
		else if (line[i][0] == 'b')
			parse_bump(line, vars, index, &i);
		else
    {
      printf("%c\n", line[i][0]);
			msg_exit_free("Unknown key\n", 1, vars);
    }
		i++;
	}
	if (!check_cone(&(vars->parse.obj[*index])))
		msg_exit_free("parsing cone infos\n", 1, vars);
	(*index)++;
}
