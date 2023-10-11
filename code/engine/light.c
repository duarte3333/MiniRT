/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:24:34 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 21:29:47 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	shadow_light(t_scene *scene, t_raytracer *rt, t_vector light_vec)
{
	t_object	*obj;
	t_raytracer	new_rt;

	new_rt = *(rt);
	new_rt.o = rt->rl.p;
	new_rt.d = rt->rl.l;
	obj = closest_intersection(&new_rt, (t_vector){0.01f, 1, 0});
	return (obj != NULL);
}

static void	specular_light(t_object *tmp, t_scene *scene, t_raytracer *rt)
{
	if (rt->rl.s)
	{
		rt->rl.aux = (t_vector){2 * dot(rt->rl.n, rt->rl.l), \
			2.0f * dot(rt->rl.n, rt->rl.l), 2.0f * dot(rt->rl.n, rt->rl.l)};
		rt->rl.r = vector_subtract(vector_multiply(rt->rl.n, \
			rt->rl.aux), rt->rl.l);
		rt->rl.r_dot_v = dot(rt->rl.r, rt->rl.v);
		if (rt->rl.r_dot_v > 0.001f)
		{
			rt->rl.i[0] += tmp->intensity * \
				pow(rt->rl.r_dot_v / (module(rt->rl.r) \
				* module(rt->rl.v)), rt->rl.s) * ((float)tmp->color.r / 255.0f);
			rt->rl.i[1] += tmp->intensity * \
				pow(rt->rl.r_dot_v / (module(rt->rl.r) \
				* module(rt->rl.v)), rt->rl.s) * ((float)tmp->color.g / 255.0f);
			rt->rl.i[2] += tmp->intensity * \
			pow(rt->rl.r_dot_v / (module(rt->rl.r) \
				* module(rt->rl.v)), rt->rl.s) * ((float)tmp->color.b / 255.0f);
		}
	}
}

static void	diffuse_light(t_object *tmp, t_scene *scene, t_raytracer *rt)
{
	rt->rl.n_dot_l = dot(rt->rl.n, rt->rl.l);
	if (rt->rl.n_dot_l > 0.001f)
	{
		rt->rl.i[0] += (tmp->intensity * rt->rl.n_dot_l) / \
			(module(rt->rl.n) * module(rt->rl.l)) * \
			((float)tmp->color.r / 255.0f);
		rt->rl.i[1] += (tmp->intensity * rt->rl.n_dot_l) / \
			(module(rt->rl.n) * module(rt->rl.l)) * \
			((float)tmp->color.g / 255.0f);
		rt->rl.i[2] += (tmp->intensity * rt->rl.n_dot_l) / \
			(module(rt->rl.n) * module(rt->rl.l)) * \
			((float)tmp->color.b / 255.0f);
	}
}

int	point_and_directional_light(t_raytracer *rt, t_object **tmp)
{
	if ((*tmp)->type == POINT)
		rt->rl.l = vector_subtract((*tmp)->vector, rt->rl.p);
	else if ((*tmp)->type == DIRECTIONAL)
		rt->rl.l = (*tmp)->vector;
	if (shadow_light(vars()->scene, rt, (*tmp)->vector))
	{
		(*tmp) = (*tmp)->next;
		return (1);
	}
	diffuse_light((*tmp), vars()->scene, rt);
	specular_light((*tmp), vars()->scene, rt);
	return (0);
}

void	ambient_light(t_raytracer *rt, t_object *tmp)
{
	rt->rl.i[0] += tmp->intensity * ((float)tmp->color.r / 255.0f);
	rt->rl.i[1] += tmp->intensity * ((float)tmp->color.g / 255.0f);
	rt->rl.i[2] += tmp->intensity * ((float)tmp->color.b / 255.0f);
}
