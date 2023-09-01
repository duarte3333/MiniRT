#include "includes/minirt.h"

bool inside(float t, float t_min, float t_max)
{
	if (t >= t_min && t < t_max )
		return true;
	return false;
}

void light_prepare(t_raytracer* rt, t_object *obj)
{
	float module_N;
	float_t closest_t;

	closest_t = rt->closest_t;
	rt->rl.P = vector_add(rt->O, vector_multiply(rt->D, vector(closest_t, closest_t, closest_t)));
	rt->rl.N = vector_subtract(rt->rl.P, obj->vector);
	module_N = module(rt->rl.N);
	rt->rl.N = vector_divide(rt->rl.N, vector(module_N, module_N, module_N));
	rt->rl.s = obj->specular;
	rt->rl.V = vector_multiply((rt->D), vector(-1, -1, -1));
}

t_object *closest_intersection(t_raytracer *rt, float t_min, float t_max)
{
	t_object *obj;
	t_object *tmp;

	tmp = vars()->scene->object;
	obj = NULL;
	rt->closest_t = INT_MAX;
	while (tmp)
	{	
        rt->t = tmp->intersect(rt, tmp); //get t1 and t2
		if (inside(rt->t.t1, t_min, t_max) && rt->t.t1 < rt->closest_t ) 
		{
            rt->closest_t = rt->t.t1;
            obj = tmp;
        }
        if (inside(rt->t.t2, t_min, t_max) && rt->t.t2 < rt->closest_t) 
		{
            rt->closest_t = rt->t.t2;
            obj = tmp;
        }
		tmp = tmp->next;
    }
	return obj;
}

static t_vector reflected_ray(t_vector R, t_vector N)
{
	double 	 dotN_R;
	t_vector Rfinal;

	dotN_R = 2.0f*dot(N, R);
	Rfinal = vector_subtract(vector_multiply(N, vector(dotN_R, dotN_R, dotN_R)), R);
	return Rfinal;
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
	obj = closest_intersection(&newRT, 0.001f, INT_MAX);
    if (!(obj) || (last_obj && obj == last_obj))
       return BLACK;
	light_prepare(&newRT, obj);
	newRT.local_color = color_multiply(obj->color, compute_light(&newRT));
	r = obj->refletive;
	if (recursion_depth <= 0 || r <= 0.001f)
		return newRT.local_color;
	newRT.rl.R = reflected_ray(vector_multiply(newRT.D, vector(-1, -1, -1)), newRT.rl.N);
	newRT.reflected_color = new_trace_ray(obj, vector_add(newRT.rl.P, vector_multiply(newRT.rl.R, vector(0.001f, 0.001f, 0.001f))), newRT.rl.R, scene, \
		rt, recursion_depth - 1);
	return (color_mult_int(newRT.local_color, (1 - r)) + color_mult_int(newRT.reflected_color, r));
}

void canvas_to_viewport(t_raytracer *rt, float x, float y)
{
	float d = 1;
	rt->D = vector(x*(1.0f/WIDTH) , -y*(1.0f/HEIGHT), d);
}

void raytracer(t_scene *scene)
{
	t_raytracer rt;
	int			x;
	int			y;

	scene = vars()->scene;
	x = -WIDTH_2;
	bzero(&rt, sizeof(t_raytracer));
	rt.O = vector(0, 0, 0);
	while (x < WIDTH_2)
	{
		y = -HEIGHT_2;
		while (y < HEIGHT_2)
		{
			rt.closest_obj = NULL;
			canvas_to_viewport(&rt, x, y); //get D
			my_mlx_pixel_put(&vars()->img, x + WIDTH_2, y + HEIGHT_2, \
				new_trace_ray(NULL, rt.O, rt.D, scene, &rt, 1));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(vars()->mlx, vars()->win, vars()->img.img, 0, 0);
}

	// if (obj->type == CYLINDER)
	// {
	// 	float r = rt->D.z + rt->closest_t;
	// 	if (r > obj->vector.z && (r <= (obj->vector.z + obj->height)))
	// 		;
	// 	else
	// 		rt->closest_t = INT_MAX;
	// }