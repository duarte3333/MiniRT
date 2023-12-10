/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:10:55 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 19:19:33 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_object	*parse_next(t_type type, char *line)
{
	if (vars()->new_objects[type] == NULL)
		return (NULL);
	return (vars()->new_objects[type](line, type));
}

t_type	ft_get_type(char *line)
{
	if (line)
	{
		if (line[0] == '\n')
			return (EMPTY_LINE);
		if (line[0] == 'A')
			return (AMBIENT);
		if (line[0] == 'P')
			return (POINT);
		if (line[0] == 'D')
			return (DIRECTIONAL);
		if (line[0] == 'C')
			return (CAMERA);
		if ((line)[0] == 's' && (line)[1] == 'p')
			return (SPHERE);
		if ((line)[0] == 'p' && (line)[1] == 'l')
			return (PLANE);
		if ((line)[0] == 'c' && (line)[1] == 'y')
			return (CYLINDER);
		if ((line)[0] == 'c' && (line)[1] == 'n')
			return (CONE);
		if (line[0] == '#')
			return (COMMENT);
	}
	return (ERROR);
}

void	ft_check_line(t_scene *scene, char *line)
{
	int		i;
	t_type	type;

	i = 0;
	type = ft_get_type(line);
	if (type >= 0 && type <= 2)
		i++;
	while (line && line[++i])
	{
		if (!line[i] && !ft_isdigit(line[i]) \
		&& line[i] != '.' && line[i] != ',')
			return ;
	}
	i = 0;
	while (line[i] && !ft_isdigit(line[i]) && line[i] != '+' && line[i] != '-')
		i++;
	if (type == CAMERA)
		scene->camera = new_camera(line + i);
	else if (type == EMPTY_LINE || type == COMMENT)
		return ;
	else if ((type != AMBIENT) && (type != POINT) && (type != DIRECTIONAL))
		lst_add_back(scene, type, (line + i));
	else
		light_add_back(scene, type, (line + i));
}

int	map_loading(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		return (0);
	ft_check_line(scene, line);
	free(line);
	return (1);
}
