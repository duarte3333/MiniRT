#include "includes/minirt.h"

bool inside(float t, float t_min, float t_max)
{
	if (t >= t_min && t < t_max )
		return true;
	return false;
}

void light_prepare(t_object obj, t_raytracer* rt, float_t closest_t)
{
	float module_N;
	rt->rl.P = vector_add(rt->O, vector_multiply(rt->D, vector(closest_t, closest_t, closest_t)));
	rt->rl.N = vector_subtract(rt->rl.P, obj.vector);
	module_N = module(rt->rl.N);
	rt->rl.N = vector_divide(rt->rl.N, vector(module_N, module_N, module_N));
	rt->rl.s = obj.specular;
	rt->rl.V = vector_multiply((rt->D), vector(-1, -1, -1));
}

t_object *closest_intersection(t_vars* vars ,t_raytracer *rt, float t_min, float t_max){
	int i;
	i = 0;
	rt->closest_t = INT_MAX;
	rt->closest_obj = NULL;
	while (vars->objects[i])
	{	
        rt->t = vars->objects[i]->intersect(rt, vars->objects[i]); //get t1 and t2
		if (inside(rt->t.t1, t_min, t_max) && rt->t.t1 < rt->closest_t ) 
		{
            rt->closest_t = rt->t.t1;
            rt->closest_obj = vars->objects[i];
        }
        if (inside(rt->t.t2, t_min, t_max) && rt->t.t2 < rt->closest_t) 
		{
            rt->closest_t = rt->t.t2;
            rt->closest_obj = vars->objects[i];
        }
		i++;
    }
	return rt->closest_obj;
}

t_object *trace_ray(t_vars* vars ,t_raytracer *rt, float t_min, float t_max, int recursion_depth)
{
	float 	 dotN_R;
	float	 r;
	int	 	 local_color;
	int 	 reflected_color;
	t_vector tempO;
	t_vector tempD;
	t_object *obj;

	tempO = rt->O;
	tempD = rt->D;
	rt->closest_obj = closest_intersection(vars, rt, 1, INT_MAX);
    if (!(rt->closest_obj))
       return NULL;
	light_prepare(*(rt->closest_obj), rt, rt->closest_t);
	local_color = color_multiply(rt->closest_obj->color, compute_light(vars, rt));
	r = rt->closest_obj->refletive;
	if (recursion_depth  <= 0 || rt->closest_obj->refletive < 0)
	{
		rt->final_color = local_color;
		return rt->closest_obj;
	}
	//Reflected color
	
	dotN_R = 2 * dot(rt->rl.N,vector_multiply(rt->D, vector(-1, -1, -1)));
	rt->rl.R = vector_add( \
		vector_multiply(rt->rl.N, vector(dotN_R, dotN_R, dotN_R)), rt->D);
	rt->O = rt->rl.P;
	rt->D = rt->rl.R;
	rt->closest_obj = trace_ray(vars, rt, 0.001f, INT_MAX, recursion_depth - 1);
	reflected_color =  color_multiply(rt->closest_obj->color, r);
	rt->final_color = color_sum_int(color_mult_int(local_color, 1 - r), color_mult_int(reflected_color, r));
	return (rt->closest_obj);
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
	t_vector tempO;
	t_vector tempD;
	t_object *obj;
	bzero(&rt, sizeof(t_raytracer));
	rt.closest_obj = NULL;
	x = -WIDTH_2;
	rt.O = vector(0, 0, 0);
	while (x < WIDTH_2)
	{
		y = -HEIGHT_2;
		while (y < HEIGHT_2)
		{
			
			canvas_to_viewport(&rt, x, y); //get D
			tempO = rt.O;
			tempD = rt.D;
			rt.closest_obj = trace_ray(vars, &rt, 0.001f, INT_MAX, 2); //get color
			rt.O = tempO;
			rt.D = tempD;
			if (!rt.closest_obj)
				my_mlx_pixel_put(&vars->img, x + WIDTH_2, y + HEIGHT_2, WHITE);
			else
			{
				my_mlx_pixel_put(&vars->img, x + WIDTH_2, y + HEIGHT_2, rt.final_color); //draw w/ light
				//my_mlx_pixel_put(&vars->img, x + WIDTH_2, y + HEIGHT_2, create_trgb(0, obj->color)); //draw
			}
			y++;
		}
	 	x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}