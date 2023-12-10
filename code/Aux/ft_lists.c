/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:42:09 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/11 17:50:57 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	lst_add_back(t_scene *scene, t_type type, char *line)
{
	t_object	*new;

	new = parse_next(type, line);
	if (new)
	{
		if (scene->object == NULL)
			scene->object = new;
		else
			scene->end->next = new;
		scene->end = new;
	}
	else
		scene->syntax = true;
}

void	light_add_back(t_scene *scene, t_type type, char *line)
{
	t_object	*new;

	new = parse_next(type, line);
	if (new)
	{
		if (scene->light == NULL)
			scene->light = new;
		else
			scene->end_light->next = new;
		scene->end_light = new;
	}
}

int	check_rgb(char **line)
{
	int	n;

	n = 0;
	while (ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit(**line) && **line != '+')
		return (0);
	while (**line && **line != ',' && !ft_isspace(**line))
	{
		if (!ft_isdigit(**line))
			return (0);
		n *= 10;
		n += (**line - 48);
		(*line)++;
	}
	if (n == 0)
		return (1);
	if (n > 255)
		return (0);
	return (n);
}
