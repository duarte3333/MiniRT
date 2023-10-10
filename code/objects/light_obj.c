/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:24:34 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 18:59:04 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	rotate(t_cylinder *this)
{
	if (this->type != AMBIENT)
	{
		rotation_x(&this->vector, this->theta);
		rotation_y(&this->vector, this->phi);
		rotation_z(&this->vector, this->qsi);
	}
}

t_object	*new_light(char *line, t_type type)
{
	t_light	*new_light;

	new_light = new_object(sizeof(t_light));
	new_light->type = type;
	new_light->rotate = rotate;
	if (new_light->type != AMBIENT)
	{
		new_light->vector.x = ft_atof(&line);
		new_light->vector.y = ft_atof(&line);
		new_light->vector.z = ft_atof(&line);
	}
	new_light->intensity = ft_atof(&line);
	new_light->color.r = (int)ft_atof(&line);
	new_light->color.g = (int)ft_atof(&line);
	new_light->color.b = (int)ft_atof(&line);
	new_light->theta = 0.0f;
	new_light->phi = 0.0f;
	new_light->qsi = 0.0f;
	return ((t_object *)new_light);
}
