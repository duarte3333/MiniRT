/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:17:06 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/11 15:14:23 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	rotate(t_cone *this)
{
	rotation_x(&this->direction, this->theta);
	rotation_y(&this->direction, this->phi);
	rotation_z(&this->direction, this->qsi);
	this->theta = 0.0f;
	this->phi = 0.0f;
	this->qsi = 0.0f;
}

static void	calculate_coefficients(t_raytracer *rt, t_cone *this)
{
	rt->co = vector_subtract(rt->o, this->vector);
	rt->a = dot(rt->d, rt->d) - this->m * \
		pow(dot(rt->d, this->direction), 2) - \
		pow(dot(rt->d, this->direction), 2);
	rt->b = 2 * (dot(rt->d, rt->co) - this->m * \
		dot(rt->d, this->direction) * dot(rt->co, this->direction) \
		- dot(rt->d, this->direction) * dot(rt->co, this->direction));
	rt->c = dot(rt->co, rt->co) - this->m * \
		pow(dot(rt->co, this->direction), 2) - \
		pow(dot(rt->co, this->direction), 2);
}

static t_values	intersect(t_raytracer *rt, t_cone *this)
{
	t_values	local;
	t_vector	p;
	float		value;

	this->tmp = vector_mult_const(this->direction, 2);
	this->m = pow(this->radius / this->height, 2);
	calculate_coefficients(rt, this);
	rt->discriminant = rt->b * rt->b - 4.0f * rt->a * rt->c;
	if (rt->discriminant < 0.0001f)
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return (local);
	}
	local.t1 = ((-rt->b + sqrt(rt->discriminant)) / (2.0f * rt->a));
	local.t2 = ((-rt->b - sqrt(rt->discriminant)) / (2.0f * rt->a));
	p = vector_add(rt->o, vector_mult_const(rt->d, local.t1));
	value = dot(vector_subtract(p, this->vector), this->direction);
	if (value < 0.001f || value > module(this->tmp))
		local.t1 = INT_MAX;
	p = vector_add(rt->o, vector_mult_const(rt->d, local.t2));
	value = dot(vector_subtract(p, this->vector), this->direction);
	if (value < 0.001f || value > module(this->tmp))
		local.t2 = INT_MAX;
	return (local);
}

static void	new_cone_2(t_cone *cone, char *line)
{
	cone->height = ft_atof(&line);
	cone->radius = ft_atof(&line);
	cone->color.r = (int)ft_atof(&line);
	cone->color.g = (int)ft_atof(&line);
	cone->color.b = (int)ft_atof(&line);
	cone->specular = (int)ft_atof(&line);
	cone->refletive = ft_atof(&line);
	cone->intensity = ft_atof(&line);
	cone->checkerboard = (int)ft_atof(&line);
	cone->theta = 0.0f;
	cone->phi = 0.0f;
	cone->qsi = 0.0f;
}

t_object	*new_cone(char *line)
{
	t_cone	*cone;

	cone = new_object(sizeof(t_cone));
	cone->intersect = intersect;
	cone->rotate = rotate;
	cone->type = CONE;
	cone->vector.x = ft_atof(&line);
	cone->vector.y = ft_atof(&line);
	cone->vector.z = ft_atof(&line);
	cone->direction.x = ft_atof(&line);
	cone->direction.y = ft_atof(&line);
	cone->direction.z = ft_atof(&line);
	cone->direction = vector_div_const(cone->direction, \
		module(cone->direction));
	new_cone_2(cone, line);
	return ((t_object *)cone);
}
