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

void print_vector(t_vector P)
{
	printf(" x: %f , y: %f, z: %f\n", P.x, P.y, P.z);
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
		// if (limits.y != INT_MAX && tmp->color.g == 0)
		// {
		// 	printf("direction ");
		// 	print_vector(rt->D);
		// 	printf("origin ");
		// 	print_vector(rt->O);
		// 	printf("pila ");
		// 	print_vector(tmp->vector);
		// 	printf("green %i, t1: %f, t2: %f,\n", tmp->color.g, rt->t.t1, rt->t.t2);
		// }
		if ((rt->t.t1 >= limits.x && rt->t.t1 <= limits.y) && rt->t.t1 < rt->closest_t) 
		{
/* 			if (limits.y != INT_MAX)
			{
				printf("oi %f\n", rt->t.t1);
				printf("limit %f\n", limits.y);
			} */
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
	return obj;
}

int new_trace_ray(t_object *last_obj, t_scene *scene ,t_raytracer rt, int recursion_depth, float limit)
{
	float	 r;
	t_object *obj;
	t_vector R;

	obj = NULL;
	obj = closest_intersection(&rt, vector(limit, INT_MAX, 0));
    if (!(obj) || (last_obj && obj == last_obj))
       return BLACK;
	light_prepare(&rt, obj);
	//newRT.local_color = get_rgb(obj->color.r, obj->color.g, obj->color.b);
	rt.local_color = color_multiply(obj->color, compute_light(&rt));
	r = obj->refletive;
	if (recursion_depth <= 0 || r <= 0.001f)
		return rt.local_color;
	rt.rl.R = reflected_ray(vector_mult_const(rt.D, -1), rt.rl.N);
	rt.O = vector_add(rt.rl.P, vector_mult_const(rt.rl.R, 0.01f));
	rt.D = rt.rl.R;
	rt.reflected_color = new_trace_ray(obj, scene, rt, recursion_depth - 1, 0.01f);
	return(color_sum_int(color_mult_int(rt.local_color, (1 - r)), color_mult_int(rt.reflected_color, r)));
	//return (color_mult_int(newRT.local_color, (1 - r)) + color_mult_int(newRT.reflected_color, r));
}

void canvas_to_viewport(t_raytracer *rt, float x, float y)
{
	t_camera *cam;
	float d = 1;

	cam = vars()->scene->camera;
    // Calculate the direction vector
    //rt->D = vector(x*(1.0f/WIDTH)*2*tan(cam->fov / 2.0 * M_PI / 180.0), -y*(1.0f/HEIGHT)*(HEIGHT/WIDTH), d);
        // Convert x and y to the viewport coordinates
    float viewport_x = x * (1.0f / WIDTH);
    float viewport_y = -y * (1.0f / HEIGHT);
    float aspect_ratio = (float)WIDTH / (float)HEIGHT;

    float fov_radians = cam->fov * (M_PI / 180.0f);
	d = (1.0f / tan(fov_radians / 2.0f));
    // Calculate the half-height and half-width at the focal plane

    // Calculate the direction vector
    //rt->D = vector(viewport_x * 2.0f * half_width, viewport_y * 2.0f * half_height, d);
    rt->D = vector(x * (1.0f / WIDTH) * aspect_ratio, -y * (1.0f / HEIGHT), d);
    
	//rt->D = vector(x*(1.0f/WIDTH), -y*(1.0f/HEIGHT), d);
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
                new_trace_ray(NULL, vars()->scene, threads->rt, 1, 1.0f);
		}
        //usleep(50);
        s.sx++;
	}
    pthread_mutex_unlock(&threads->th_mut);
}
