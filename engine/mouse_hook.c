/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:39:30 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/07 21:58:52 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_object *mouse_trace_ray(t_vars *vars ,t_raytracer *rt)
{
	float 	 dotN_R;
	float	 r;
	t_raytracer newRT;

	newRT = *(rt);
	newRT.O = rt->O;
	newRT.D = rt->D;
	newRT.closest_obj = closest_intersection(&newRT, (t_vector){0.01f, INT_MAX, 0});
    if (!(newRT.closest_obj))
       return NULL;
	light_prepare(&newRT, newRT.closest_obj);
	newRT.local_color = color_multiply(newRT.closest_obj->color, compute_light(&newRT), newRT.closest_obj->intensity);
	return (newRT.closest_obj);
}

static int ft_mouse_scroll(int button, int x, int y, t_scene *scene)
{
	if (scene->select)
		scene->select->vector.z +=  ((button == 5) - (button == 4)) * 0.05;
	else 
		scene->camera->vector.z +=  ((button == 4) - (button == 5)) * 0.05;
	//threads_update();
	return 0;
}

int ft_mouse_down(int button, int x, int y)
{
	t_raytracer rt;
	x -= WIDTH_2;
	y -= HEIGHT_2;
	int i = -1;

	//threads_update();
	if ((button == 5) || (button == 4))
		return (ft_mouse_scroll(button, x, y, vars()->scene));	
	if (vars()->scene->select && button == 3)
	{
		vars()->scene->select->vector.x = ((float)(x))*(1.5f/WIDTH_2);
		vars()->scene->select->vector.y = -((float)(y))*(1.5f/HEIGHT_2);
		//threads_update();
		return (0);
	}
	rt.O = vars()->scene->camera->vector;	
	canvas_to_viewport(&rt, x, y); //get D
	vars()->scene->select = mouse_trace_ray(vars, &rt); //get color
	//threads_update();
	return 0;
}