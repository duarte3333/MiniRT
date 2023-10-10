/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:44:42 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 15:46:59 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	light_prepare(t_raytracer	*rt, t_object *obj)
{
	float	module_n;
	float_t	closest_t;

	closest_t = rt->closest_t;
	rt->rl.P = vector_add(rt->O, vector_mult_const(rt->D, closest_t));
	choose_normal(rt, obj);
	module_n = module(rt->rl.N);
	rt->rl.N = vector_div_const(rt->rl.N, module_n);
	rt->rl.s = obj->specular;
	rt->rl.V = vector_mult_const((rt->D), -1);
}

t_object	*checkerboard(t_raytracer *rt, t_object *obj)
{
	t_vector	intersection_point;
	int			checkered_value;

	intersection_point = vector_add(rt->O, \
		vector_mult_const(rt->D, rt->closest_t));
	checkered_value = ((int)floor(intersection_point.x) + \
						(int)floor(intersection_point.y) + \
						(int)floor(intersection_point.z)) % 2;
	if (checkered_value == 0)
		obj->color = (t_color){0, 0, 0};
	else
		obj->color = (t_color){255, 255, 255};
	return (obj);
}
