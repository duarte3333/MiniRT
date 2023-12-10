/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:50:22 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/12 21:26:55 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_values	intersect_plane(t_raytracer *rt, t_plane *this)
{
	t_values	local;

	rt->c = -dot(this->direction, vector_subtract(rt->o, this->vector));
	rt->b = dot(rt->d, this->direction);
	if (rt->b < 0.0001f && rt->b > -0.0001f)
	{
		local.t1 = (float)INT_MAX;
		local.t2 = (float)INT_MAX;
		return (local);
	}
	local.t1 = rt->c / rt->b;
	local.t2 = (float)INT_MAX;
	return (local);
}

void	create_upper_cap(t_cylinder *cylinder)
{
	cylinder->up_cap = new_object(sizeof(t_plane));
	cylinder->up_cap->intersect = intersect_plane;
	cylinder->up_cap->vector = vector_subtract(cylinder->vector, \
	vector_mult_const(vector_div_const(cylinder->axis, \
		module(cylinder->axis)), cylinder->height / 2));
	cylinder->up_cap->direction = vector_mult_const(cylinder->axis, 1);
}

void	create_lower_cap(t_cylinder *cylinder)
{
	cylinder->down_cap = new_object(sizeof(t_plane));
	cylinder->down_cap->intersect = intersect_plane;
	cylinder->down_cap->vector = vector_add(cylinder->vector, \
		vector_mult_const(vector_div_const(cylinder->axis, \
		module(cylinder->axis)), cylinder->height / 2));
	cylinder->down_cap->direction = vector_mult_const(cylinder->axis, -1);
}

t_values	rest_intersect(t_raytracer *rt, t_cylinder *this, t_values local)
{
	t_values	local_up_cap;
	t_values	local_down_cap;

	local.t1 = min(local.t1, local.t2);
	local_up_cap = this->up_cap->intersect(rt, this->up_cap);
	local_down_cap = this->down_cap->intersect(rt, this->down_cap);
	local_up_cap.t1 = check_width(this->up_cap, \
		rt, local_up_cap.t1, this->diameter);
	local_down_cap.t1 = check_width(this->down_cap, \
		rt, local_down_cap.t1, this->diameter);
	local.t1 = min(min(local_up_cap.t1, local_down_cap.t1), local.t1);
	return (local);
}
