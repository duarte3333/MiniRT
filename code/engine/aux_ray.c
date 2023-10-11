/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:41:14 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/11 00:49:27 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

bool	inside(float t, float t_min, float t_max)
{
	if (t >= t_min && t < t_max)
		return (true);
	return (false);
}

void	choose_normal(t_raytracer *rt, t_object *obj)
{
	t_vector	obj_to_p;
	float		projection;

	if (obj->type == SPHERE)
		rt->rl.n = vector_subtract(rt->rl.p, obj->vector);
	else if (obj->type == PLANE)
		rt->rl.n = ((t_plane *)obj)->direction;
	else if (obj->type == CONE)
	{
		obj_to_p = vector_subtract(rt->rl.p, obj->vector);
		projection = dot(obj_to_p, ((t_cone *)obj)->direction);
		rt->rl.n = vector_subtract(obj_to_p, \
			vector_mult_const(((t_cone *)obj)->direction, projection));
	}
	else if (obj->type == CYLINDER)
	{
		obj_to_p = vector_subtract(rt->rl.p, obj->vector);
		projection = dot(obj_to_p, ((t_cylinder *)obj)->axis);
		rt->rl.n = vector_subtract(obj_to_p, \
			vector_mult_const(((t_cylinder *)obj)->axis, projection));
	}
	if (dot(rt->d, rt->rl.n) > 0)
		rt->rl.n = vector_mult_const(rt->rl.n, -1);
}

t_vector	reflected_ray(t_vector R, t_vector N)
{
	double		dot_n_r;
	t_vector	r_final;

	dot_n_r = 2.0 * dot(N, R);
	r_final = vector_subtract(vector_mult_const(N, dot_n_r), R);
	return (r_final);
}
