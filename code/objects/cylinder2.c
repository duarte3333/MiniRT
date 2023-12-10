/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:08:29 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/12 20:26:05 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	min(float a, float b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

float	distance(t_vector v1, t_vector v2)
{
	return (sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2)
			+ pow(v1.z - v2.z, 2)));
}

t_values	check_height(t_raytracer *rt, t_cylinder *this, t_values t)
{
	t_vector	p;
	t_vector	b;
	float		k;

	p = vector_add(rt->o, vector_mult_const(rt->d, t.t1));
	k = dot(p, this->axis) - dot(this->vector, this->axis) \
		/ dot(this->axis, this->axis);
	b = vector_add(this->vector, vector_mult_const(this->axis, k));
	if (fabs(distance(b, this->vector) * 1.0f) > this->height / 2)
		t.t1 = (float)INT_MAX;
	p = vector_add(rt->o, vector_mult_const(rt->d, t.t2));
	k = dot(p, this->axis) - dot(this->vector, this->axis) / \
		dot(this->axis, this->axis);
	b = vector_add(this->vector, vector_mult_const(this->axis, k));
	if (fabs(distance(b, this->vector) * 1.0f) > this->height / 2)
		t.t2 = (float)INT_MAX;
	return (t);
}

float	check_width(t_plane *this, t_raytracer *rt, float t, float diameter)
{
	t_vector	p_cap;
	t_vector	v;

	p_cap = vector_add(rt->o, vector_mult_const(rt->d, t));
	v = vector_subtract(p_cap, this->vector);
	if (t * (module(v) <= (diameter / 2)))
		return (t * (module(v) <= (diameter / 2)));
	else
		return ((float)INT_MAX);
}

void	t_discover(float *t, t_cylinder *this)
{
	float	quadratic[3];

	quadratic[0] = dot(this->axis, this->axis);
	quadratic[1] = 0;
	quadratic[2] = -pow(this->height, 2) / 4;
	t[0] = (-quadratic[1] - sqrt(pow(quadratic[1], 2) - 4 \
		* quadratic[0] * quadratic[2])) / (2 * quadratic[0]);
	t[1] = (-quadratic[1] + sqrt(pow(quadratic[1], 2) - 4 \
		* quadratic[0] * quadratic[2])) / (2 * quadratic[0]);
}
