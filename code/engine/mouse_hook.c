/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:58:14 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/12 17:58:29 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	translate_light(int keycode)
{
	vars()->scene->select_light->vector.y += \
		((keycode == XK_Up) - (keycode == XK_Down)) * 0.1;
	vars()->scene->select_light->vector.x += \
		((keycode == XK_Right) - (keycode == XK_Left)) * 0.1;
	vars()->scene->select_light->vector.z += \
		((keycode == XK_z) - (keycode == XK_x)) * 0.1;
}

void	light_keys(int keycode)
{
	if (keycode == XK_r)
		vars()->scene->select_light = vars()->scene->light;
	if (keycode == XK_t)
	{
		if (!vars()->scene->select_light || !vars()->scene->select_light->next)
			vars()->scene->select_light = vars()->scene->light;
		else if (vars()->scene->select_light->next)
			vars()->scene->select_light = vars()->scene->select_light->next;
	}
	if (!vars()->scene->select && vars()->scene->select_light)
		translate_light(keycode);
}

static t_object	*mouse_trace_ray(t_raytracer *rt)
{
	t_raytracer	new_rt;

	new_rt = *(rt);
	new_rt.o = rt->o;
	new_rt.d = rt->d;
	new_rt.closest_obj = closest_intersection(&new_rt, \
		(t_vector){0.01f, (float)INT_MAX, 0});
	if (!(new_rt.closest_obj))
		return (NULL);
	light_prepare(&new_rt, new_rt.closest_obj);
	new_rt.local_color = color_multiply(new_rt.closest_obj->color, \
		compute_light(&new_rt), new_rt.closest_obj->intensity);
	return (new_rt.closest_obj);
}

static int	ft_mouse_scroll(int button, t_scene *scene)
{
	if (scene->select)
	{
		scene->select->vector.z += ((button == 5) - (button == 4)) * 0.1;
		if (vars()->scene->select->type == CYLINDER)
		{
			((t_cylinder *)vars()->scene->select)->up_cap->vector.z \
					+= ((button == 5) - (button == 4)) * 0.1;
			((t_cylinder *)vars()->scene->select)->down_cap->vector.z \
					+= ((button == 5) - (button == 4)) * 0.1;
		}
	}
	else
		scene->camera->vector.z += ((button == 4) - (button == 5)) * 0.1;
	threads_update();
	return (0);
}

int	ft_mouse_down(int button, int x, int y)
{
	t_raytracer	rt;
	int			i;

	x -= WIDTH_2;
	y -= HEIGHT_2;
	i = -1;
	if ((button == 5) || (button == 4))
		return (ft_mouse_scroll(button, vars()->scene));
	if (button == 3)
	{
		vars()->scene->select = NULL;
		return (0);
	}
	if (vars()->scene->select && button == 1)
	{
		vars()->scene->select->vector.x = ((float)(x)) * (1.5f / WIDTH_2);
		vars()->scene->select->vector.y = -((float)(y)) * (1.5f / HEIGHT_2);
		threads_update();
		return (0);
	}
	rt.o = vars()->scene->camera->vector;
	canvas_to_viewport(&rt, x, y);
	vars()->scene->select = mouse_trace_ray(&rt);
	threads_update();
	return (0);
}
