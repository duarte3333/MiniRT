/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:50:46 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 23:55:59 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	rotate(t_plane *this)
{
	rotation_x(&this->direction, this->theta);
	rotation_y(&this->direction, this->phi);
	rotation_z(&this->direction, this->qsi);
	this->theta = 0.0f;
	this->phi = 0.0f;
	this->qsi = 0.0f;
}

static t_values	intersect(t_raytracer *rt, t_plane *this)
{
	t_values	local;

	rt->c = -dot(this->direction, vector_subtract(rt->o, this->vector));
	rt->b = dot(rt->d, this->direction);
	if (rt->b < 0.0001f && rt->b > -0.0001f)
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return (local);
	}
	local.t1 = rt->c / rt->b;
	local.t2 = INT_MAX;
	return (local);
}

t_object	*new_plane(char *line)
{
	t_plane	*plane;

	plane = new_object(sizeof(t_plane));
	plane->intersect = intersect;
	plane->rotate = rotate;
	plane->type = PLANE;
	plane->vector.x = ft_atof(&line);
	plane->vector.y = ft_atof(&line);
	plane->vector.z = ft_atof(&line);
	plane->direction.x = ft_atof(&line);
	plane->direction.y = ft_atof(&line);
	plane->direction.z = ft_atof(&line);
	plane->color.r = (int)ft_atof(&line);
	plane->color.g = (int)ft_atof(&line);
	plane->color.b = (int)ft_atof(&line);
	plane->specular = (int)ft_atof(&line);
	plane->refletive = ft_atof(&line);
	plane->intensity = ft_atof(&line);
	plane->checkerboard = (int)ft_atof(&line);
	plane->theta = 0.0f;
	plane->phi = 0.0f;
	plane->qsi = 0.0f;
	return ((t_object *)plane);
}
