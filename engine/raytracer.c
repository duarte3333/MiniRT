#include "../includes/minirt.h"

void light_prepare(t_raytracer* rt, t_object *obj)
{
	float module_N;
	float_t closest_t;

	closest_t = rt->closest_t;
	rt->rl.P = vector_add(rt->O, vector_mult_const(rt->D, closest_t));
	choose_normal(rt, obj);
	module_N = module(rt->rl.N);
	rt->rl.N = vector_div_const(rt->rl.N, module_N);
	rt->rl.s = obj->specular;
	rt->rl.V = vector_mult_const((rt->D), -1);
}

void checkerboard(t_raytracer *rt, t_object *obj)
{
	t_vector intersection_point = vector_add(rt->O, vector_mult_const(rt->D, rt->closest_t));

	int checkered_value = ((int)floor(intersection_point.x) +
						   (int)floor(intersection_point.y) +
						   (int)floor(intersection_point.z)) %
						  2;
	if (checkered_value == 0)
		obj->color = (t_color){0, 0, 0}; // Black
	else
		obj->color = (t_color){255, 255, 255}; // White
	//return obj;
}

t_object *closest_intersection(t_raytracer *rt, t_vector limits)
{
	t_object *obj;
	t_object *tmp;

	tmp = vars()->scene->object;
	obj = NULL;
	rt->closest_t = INT_MAX;
	while (tmp)
	{	
        rt->t = tmp->intersect(rt, tmp); //get t1 and t2
		if ((rt->t.t1 >= limits.x && rt->t.t1 <= limits.y) && rt->t.t1 < rt->closest_t) 
		{
            rt->closest_t = rt->t.t1;
            obj = tmp;
        }
        if ((rt->t.t2 >= limits.x && rt->t.t2 <= limits.y) && rt->t.t2 < rt->closest_t) 
		{
            rt->closest_t = rt->t.t2;
            obj = tmp;
        }
		tmp = tmp->next;
    }
	if (obj && obj->checkerboard == 6)
		checkerboard(rt, obj);
	return obj;
}

int new_trace_ray(t_object *last_obj, t_scene *scene ,t_raytracer rt, int recursion_depth, float limit)
{
	float	 r;
	t_object *obj;
	t_vector R;

	obj = NULL;
	obj = closest_intersection(&rt, (t_vector){limit, INT_MAX, 0});
    if (!(obj) || (last_obj && obj == last_obj))
       return BLACK;
	light_prepare(&rt, obj);
	//newRT.local_color = get_rgb(obj->color.r, obj->color.g, obj->color.b);
	rt.local_color = color_multiply(obj->color, compute_light(&rt), obj->intensity);
	r = obj->refletive;
	if (recursion_depth <= 0 || r <= 0.001f)
		return rt.local_color;
	rt.rl.R = reflected_ray(vector_mult_const(rt.D, -1), rt.rl.N);
	rt.O = vector_add(rt.rl.P, vector_mult_const(rt.rl.R, 0.01f));
	rt.D = rt.rl.R;
	rt.reflected_color = new_trace_ray(obj, scene, rt, recursion_depth - 1, 0.01f);
	return(color_sum_int(color_mult_int(rt.local_color, (1 - r)), color_mult_int(rt.reflected_color, r)));
}

void canvas_to_viewport(t_raytracer *rt, float x, float y)
{
	t_camera *cam;
	float d;
	float aspect_ratio;
	float fov_radians;
	t_vector direction;

	cam = vars()->scene->camera;
	direction = cam->direction;
    aspect_ratio = (float)WIDTH / (float)HEIGHT;
    fov_radians = cam->fov * (M_PI / 180.0f);
	d = (1.0f / tan(fov_radians / 2.0f));
	rt->D = direction;
	rt->D.x += x * (1.0f / WIDTH) * aspect_ratio;
    rt->D.y -= y * (1.0f / HEIGHT);
    rt->D.z = d; 
    // rt->D = (t_vector){x * (1.0f / WIDTH) * aspect_ratio, \
	// 					  - y * (1.0f / HEIGHT),  d};
	cam->rotate(&rt->D, cam);

}

void    raytracer_threads(t_ray_thread *threads)
{
	t_chunk     s;

    pthread_mutex_lock(&threads->th_mut);
    threads->rt.O = vars()->scene->camera->vector;
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
			threads->color[s.sy++ * threads->delta + s.sx] = \
                new_trace_ray(NULL, vars()->scene, threads->rt, 0, 1.0f);
		}
        //usleep(50);
        s.sx++;
	}
    pthread_mutex_unlock(&threads->th_mut);
}
