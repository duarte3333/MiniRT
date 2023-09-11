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

t_object *closest_intersection(t_raytracer *rt)
{
	t_object *obj;
	t_object *tmp;

	tmp = vars()->scene->object;
	obj = NULL;
	rt->closest_t = INT_MAX;
	while (tmp)
	{	
        rt->t = tmp->intersect(rt, tmp); //get t1 and t2
		if (inside(rt->t.t1, 0.001f, INT_MAX) && rt->t.t1 < rt->closest_t ) 
		{
            rt->closest_t = rt->t.t1;
            obj = tmp;
        }
        if (inside(rt->t.t2, 0.001f, INT_MAX) && rt->t.t2 < rt->closest_t) 
		{
            rt->closest_t = rt->t.t2;
            obj = tmp;
        }
		tmp = tmp->next;
    }
	return obj;
}

int new_trace_ray(t_object *last_obj, t_vector O, t_vector D, t_scene *scene ,t_raytracer *rt, int recursion_depth)
{
	float	 r;
	t_object *obj;
	t_vector R;
	t_raytracer newRT = *(rt);

	obj = NULL;
	newRT.O = O;
	newRT.D = D;
	obj = closest_intersection(&newRT);
    if (!(obj) || (last_obj && obj == last_obj))
       return BLACK;
	light_prepare(&newRT, obj);
	//newRT.local_color = get_rgb(obj->color.r, obj->color.g, obj->color.b);
	newRT.local_color = color_multiply(obj->color, compute_light(&newRT));
	r = obj->refletive;
	if (recursion_depth <= 0 || r <= 0.001f)
		return newRT.local_color;
	newRT.rl.R = reflected_ray(vector_mult_const(newRT.D, -1), newRT.rl.N);
	newRT.reflected_color = new_trace_ray(obj, vector_add(newRT.rl.P, \
		vector_mult_const(newRT.rl.R, 0.01f)), newRT.rl.R, scene, rt, recursion_depth - 1);
	return (color_mult_int(newRT.local_color, (1 - r)) + color_mult_int(newRT.reflected_color, r));
}

void canvas_to_viewport(t_raytracer *rt, float x, float y)
{
	t_camera *cam;
	float d = 1;

	cam = vars()->scene->camera;
	rt->D = vector(x*(1.0f/WIDTH) , -y*(1.0f/HEIGHT), d);
	rotation_x(&rt->D, cam->theta);
	rotation_y(&rt->D, cam->phi);
	rotation_z(&rt->D, cam->qsi);
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
                new_trace_ray(NULL, threads->rt.O, threads->rt.D, vars()->scene, &threads->rt, 1);
		}
        //usleep(50);
        s.sx++;
	}
    pthread_mutex_unlock(&threads->th_mut);
}
