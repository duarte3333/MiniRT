/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 19:09:27 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 19:10:48 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	check_ambient(char **line)
{
	(*line)++;
	if (check_float(line, 0) == 0)
		return (0);
	if (check_color(line) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line && **line != '\n')
		return (0);
	return (1);
}

int	check_float(char **line, int g)
{
	int	f;

	f = 0;
	while (ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit(**line) && **line != '+' && g == 1 && **line != '-')
		return (0);
	(*line)++;
	while (**line && **line != ',' && !ft_isspace(**line))
	{
		if (**line == '.' && f == 0)
			f = 1;
		else if (**line == '.' && f == 1)
			return (0);
		else if (!ft_isdigit(**line) && **line != '.')
			return (0);
		(*line)++;
	}
	return (1);
}

int	check_vector(char **line)
{
	if (check_float(line, 1) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	if (check_float(line, 1) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	if (check_float(line, 1) == 0)
		return (0);
	if (!ft_isspace(**line) && **line)
		return (0);
	return (1);
}

int	check_color(char **line)
{
	if (check_float(line, 0) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	if (check_float(line, 0) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	if (**line != ',')
		return (0);
	(*line)++;
	if (check_float(line, 0) == 0)
		return (0);
	if (!ft_isspace(**line) && **line)
		return (0);
	return (1);
}

int	check_spec_ref(char **line)
{
	if (check_float(line, 0) == 0)
		return (0);
	if (check_float(line, 0) == 0)
		return (0);
	while (ft_isspace(**line))
		(*line)++;
	return (1);
}
