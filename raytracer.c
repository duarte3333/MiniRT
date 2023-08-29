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

t_object *closest_intersection(t_vars* vars ,t_raytracer *rt, float t_min, float t_max){
	t_object *obj;
	int 	 i;
	i = 0;

	obj = NULL;
	rt->closest_t = INT_MAX;
	while (vars->objects[i])
	{	
        rt->t = vars->objects[i]->intersect(rt, vars->objects[i]); //get t1 and t2
		if (inside(rt->t.t1, t_min, t_max) && rt->t.t1 < rt->closest_t ) 
		{
            rt->closest_t = rt->t.t1;
            obj = vars->objects[i];
        }
        if (inside(rt->t.t2, t_min, t_max) && rt->t.t2 < rt->closest_t) 
		{
            rt->closest_t = rt->t.t2;
            obj = vars->objects[i];
        }
		i++;
    }
	return obj;
}

t_vector reflected_ray(t_vector R, t_vector N)
{
	float 	 dotN_R;
	t_vector Rfinal;

	dotN_R = 2 * dot(N, R);
	Rfinal = vector_subtract(vector_multiply(N, vector(dotN_R, dotN_R, dotN_R)), R);
	return Rfinal;
}

t_object *trace_ray(t_vector O, t_vector D, t_vars *vars ,t_raytracer *rt, float t_min, float t_max, int recursion_depth)
{
	float 	 dotN_R;
	float	 r;

	rt->O = O;
	rt->D = D;
	rt->closest_obj = closest_intersection(vars, rt, 1, INT_MAX);
    if (!(rt->closest_obj))
       return NULL;
	light_prepare(rt, rt->closest_obj);
	rt->local_color = color_multiply(rt->closest_obj->color, compute_light(vars, rt));
	return (rt->closest_obj);
}

int new_trace_ray(t_vector O, t_vector D, t_vars *vars ,t_raytracer *rt, float t_min, float t_max, int recursion_depth)
{
	float	 r;
	t_object *obj;
	int		 reflected_color;
	int		 local_color;
	t_vector R;
	t_vector P;
	t_vector N;

	obj = NULL;
	rt->O = O;
	rt->D = D;
	obj = closest_intersection(vars, rt, 1, INT_MAX);
    if (!(obj))
       return WHITE;
	light_prepare(rt, obj);
	local_color = color_multiply(obj->color, compute_light(vars, rt));
	r = obj->refletive;
	if (recursion_depth <= 0 || r <= 0)
		return local_color;
	rt->rl.R = reflected_ray(vector_multiply(rt->D, vector(-1, -1, -1)), rt->rl.N);
	reflected_color = new_trace_ray(rt->rl.P, rt->rl.R, vars, rt, 0.001f, INT_MAX, recursion_depth - 1);
	return (color_sum_int(color_mult_int(local_color, 1.0f - r),color_mult_int(reflected_color, r)));
	//return (color_mult_int(rt->local_color, (r)));
	//return (color_mult_int(rt->reflected_color, 0.2f));
}

void canvas_to_viewport(t_raytracer *rt, float x, float y)
{
	float d = 1;
	rt->D = vector(x*(1.0f/WIDTH) , -y*(1.0f/HEIGHT), d);
}

void raytracer(t_vars *vars)
{
	t_raytracer rt;
	int			x;
	int			y;

	x = -WIDTH_2;
	rt.O = vector(0, 0, 0);
	while (x < WIDTH_2)
	{
		y = -HEIGHT_2;
		while (y < HEIGHT_2)
		{
			bzero(&rt, sizeof(t_raytracer));
			rt.closest_obj = NULL;
			canvas_to_viewport(&rt, x, y); //get D
			my_mlx_pixel_put(&vars->img, x + WIDTH_2, y + HEIGHT_2, \
				new_trace_ray(rt.O, rt.D, vars, &rt, 0.001f, INT_MAX, 0));
			y++;
		}
	 	x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}