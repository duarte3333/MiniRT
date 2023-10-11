/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:44:42 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/11 00:50:29 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_object	*closest_intersection(t_raytracer *rt, t_vector limits)
{
	t_object	*obj;
	t_object	*tmp;

	tmp = vars()->scene->object;
	obj = NULL;
	rt->closest_t = INT_MAX;
	while (tmp)
	{
		rt->t = tmp->intersect(rt, tmp);
		if ((rt->t.t1 >= limits.x && rt->t.t1 <= limits.y) \
			&& rt->t.t1 < rt->closest_t)
		{
			rt->closest_t = rt->t.t1;
			obj = tmp;
		}
		if ((rt->t.t2 >= limits.x && rt->t.t2 <= limits.y) \
			&& rt->t.t2 < rt->closest_t)
		{
			rt->closest_t = rt->t.t2;
			obj = tmp;
		}
		tmp = tmp->next;
	}
	return (obj);
}

int	new_trace_ray(t_object *last_obj, t_raytracer rt, \
	int recursion_depth, float limit)
{
	float		r;
	t_object	*obj;

	obj = NULL;
	obj = closest_intersection(&rt, (t_vector){limit, INT_MAX, 0});
	if (!(obj) || (last_obj && obj == last_obj))
		return (BLACK);
	light_prepare(&rt, obj);
	rt.local_color = color_multiply(obj->color, \
		compute_light(&rt), obj->intensity);
	r = obj->refletive;
	if (recursion_depth <= 0 || r <= 0.001f)
		return (rt.local_color);
	rt.rl.r = reflected_ray(vector_mult_const(rt.d, -1), rt.rl.n);
	rt.o = vector_add(rt.rl.p, vector_mult_const(rt.rl.r, 0.01f));
	rt.d = rt.rl.r;
	rt.reflected_color = new_trace_ray(obj, \
		rt, recursion_depth - 1, 0.01f);
	return (color_mult_int(rt.local_color, (1 - r)) + \
			color_mult_int(rt.reflected_color, r));
}

void	canvas_to_viewport(t_raytracer *rt, float x, float y)
{
	t_camera	*cam;
	float		d;
	float		aspect_ratio;
	float		fov_radians;
	t_vector	direction;

	cam = vars()->scene->camera;
	direction = cam->direction;
	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	fov_radians = cam->fov * (M_PI / 180.0f);
	d = (1.0f / tan(fov_radians / 2.0f));
	rt->d = direction;
	rt->d.x += x * (1.0f / WIDTH) * aspect_ratio;
	rt->d.y -= y * (1.0f / HEIGHT);
	rt->d.z = d;
	cam->rotate(&rt->d, cam);
}
// // rt->D = (t_vector){x * (1.0f / WIDTH) * aspect_ratio,
// // 					  - y * (1.0f / HEIGHT),  d};	

void	raytracer_threads(t_ray_thread *threads)
{
	t_chunk	s;

	pthread_mutex_lock(&threads->th_mut);
	threads->rt.o = vars()->scene->camera->vector;
	s.sx = 0;
	s.x = threads->x_i - 1;
	while (++s.x < threads->x_f)
	{
		s.sy = 0;
		s.y = -HEIGHT_2 - 1;
		while (++s.y < HEIGHT_2)
		{
			threads->rt.closest_obj = NULL;
			canvas_to_viewport(&threads->rt, s.x, s.y);
			threads->color[((s.sy++) * threads->delta) + s.sx] = \
				new_trace_ray(NULL, threads->rt, 0, 1.0f);
		}
		s.sx++;
	}
	pthread_mutex_unlock(&threads->th_mut);
}
