/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:03:21 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/12 21:28:00 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	t_discover(float *t, t_cylinder *this)
{
	float	quadratic[3];

	quadratic[0] = dot(this->axis, this->axis);
	quadratic[1] = 0;
	quadratic[2] = -pow(this->height / 2, 2);
	t[0] = (-quadratic[1] - sqrt(pow(quadratic[1], 2) - 4 \
		* quadratic[0] * quadratic[2])) / (2 * quadratic[0]);
	t[1] = (-quadratic[1] + sqrt(pow(quadratic[1], 2) - 4 \
		* quadratic[0] * quadratic[2])) / (2 * quadratic[0]);
}

static void	rotate(t_cylinder *this)
{
	float	t[2];

	rotation_x(&this->axis, this->theta);
	rotation_y(&this->axis, this->phi);
	rotation_z(&this->axis, this->qsi);
	t_discover(t, this);
	this->up_cap->direction = vector_mult_const(this->axis, 1);
	rotation_x(&this->up_cap->direction, this->theta);
	rotation_y(&this->up_cap->direction, this->phi);
	rotation_z(&this->up_cap->direction, this->qsi);
	this->up_cap->vector = vector_add(this->vector, \
		vector_mult_const(this->axis, t[0]));
	t_discover(t, this);
	this->down_cap->direction = vector_mult_const(this->axis, -1);
	rotation_x(&this->down_cap->direction, this->theta);
	rotation_y(&this->down_cap->direction, this->phi);
	rotation_z(&this->down_cap->direction, this->qsi);
	this->down_cap->vector = vector_add(this->vector, \
		vector_mult_const(this->axis, -t[1]));
	this->theta = 0.0f;
	this->phi = 0.0f;
	this->qsi = 0.0f;
}

static t_values	intersect(t_raytracer *rt, t_cylinder *this)
{
	t_values	local;
	t_vector	co;

	co = vector_subtract(rt->o, this->vector);
	rt->a = dot(rt->d, rt->d) * pow(module(this->axis), 2) - \
		pow(dot(rt->d, this->axis), 2);
	rt->b = 2.0f * dot(co, rt->d) * pow(module(this->axis), 2) - \
		2.0f * dot(rt->d, this->axis) * dot(co, this->axis);
	rt->c = (dot(co, co) - pow(this->diameter / 2, 2)) * \
		pow(module(this->axis), 2) - \
		pow(dot(co, this->axis), 2);
	rt->discriminant = rt->b * rt->b - 4.0f * rt->a * rt->c;
	if (rt->discriminant < 0.001f)
	{
		local = (t_values){(float)INT_MAX, (float)INT_MAX};
		local.t1 = min(min(check_width(this->up_cap, rt, \
			(this->up_cap->intersect(rt, this->up_cap)).t1, this->diameter) \
			, check_width(this->down_cap, rt, (this->down_cap->intersect(rt, \
			this->up_cap)).t1, this->diameter)), local.t1);
		return (local);
	}
	local.t1 = ((-rt->b + sqrt(rt->discriminant)) / (2.0f * rt->a));
	local.t2 = ((-rt->b - sqrt(rt->discriminant)) / (2.0f * rt->a));
	local = check_height(rt, this, local);
	return (rest_intersect(rt, this, local));
}

t_object	*new_cylinder(char *line)
{
	t_cylinder	*cylinder;

	cylinder = new_object(sizeof(t_cylinder));
	cylinder->intersect = intersect;
	cylinder->rotate = rotate;
	cylinder->type = CYLINDER;
	cylinder->vector.x = ft_atof(&line);
	cylinder->vector.y = ft_atof(&line);
	cylinder->vector.z = ft_atof(&line);
	cylinder->axis.x = ft_atof(&line);
	cylinder->axis.y = ft_atof(&line);
	cylinder->axis.z = ft_atof(&line);
	cylinder->diameter = ft_atof(&line);
	cylinder->height = ft_atof(&line);
	cylinder->color.r = (int)ft_atof(&line);
	cylinder->color.g = (int)ft_atof(&line);
	cylinder->color.b = (int)ft_atof(&line);
	cylinder->specular = (int)ft_atof(&line);
	cylinder->refletive = ft_atof(&line);
	cylinder->intensity = ft_atof(&line);
	cylinder->checkerboard = (int)ft_atof(&line);
	create_lower_cap(cylinder);
	create_upper_cap(cylinder);
	return ((t_object *)cylinder);
}
