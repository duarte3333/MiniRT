/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:06:12 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 19:22:04 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	check_camera(char **line)
{
	(*line)++;
	if (check_vector(line) == 0 || check_vector(line) == 0 \
		|| check_float(line, 0) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int	check_sphere(char **line)
{
	(*line) += 2;
	if (check_vector(line) == 0 || (check_float(line, 1) == 0) || \
		(check_color(line) == 0) || (check_spec_ref(line) == 0))
		return (0);
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int	check_cone(char **line)
{
	(*line) += 2;
	if (check_vector(line) == 0 || check_vector(line) == 0 || \
		check_float(line, 1) == 0 || check_float(line, 1) == 0 || \
		check_color(line) == 0 || check_spec_ref(line) == 0)
		return (0);
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int	check_cylinder(char **line)
{
	(*line) += 2;
	if (check_vector(line) == 0 || check_vector(line) == 0 || \
		check_float(line, 1) == 0 || check_float(line, 1) == 0 || \
		check_color(line) == 0 || check_spec_ref(line) == 0)
		return (0);
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int	check_light(char **line)
{
	(*line)++;
	if (check_vector(line) == 0 || check_float(line, 0) == 0 \
		|| check_color(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	return (1);
}	
