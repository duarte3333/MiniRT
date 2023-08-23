#include "includes/minirt.h"

bool inside(float t, float t_min, float t_max)
{
	if (t >= t_min && t < t_max )
		return true;
	return false;
}

void light_prepare(t_object obj, t_raytracer* rt, float_t closest_t)
{
	rt->rl.P = vector_add(rt->O, vector_multiply(rt->D, vector(closest_t, closest_t, closest_t)));
	rt->rl.N = vector_subtract(rt->rl.P, obj.vector);
	rt->rl.N = vector_divide(rt->rl.N, vector(module(rt->rl.N), module(rt->rl.N), module(rt->rl.N)));
}

t_object *trace_ray(t_vars* vars ,t_raytracer* rt, float t_min, float t_max)
{
	float closest_t = INT_MAX;
	t_object *closest_obj = NULL;
	int i = 0;
	while (vars->objects[i])
	{	
        rt->t = vars->objects[i]->intersect(rt, vars->objects[i]); //get t1 and t2
		if (inside(rt->t.t1, t_min, t_max) && rt->t.t1 < closest_t ) 
		{
            closest_t = rt->t.t1;
            closest_obj = vars->objects[i];
        }
        if (inside(rt->t.t2, t_min, t_max) && rt->t.t2 < closest_t) 
		{
            closest_t = rt->t.t2;
            closest_obj = vars->objects[i];
        }
		i++;
    }
	if (closest_obj)
		light_prepare(*closest_obj, rt, closest_t);
    if (!closest_obj)
       return NULL;
	return (closest_obj);
}

void canvas_to_viewport(t_raytracer *rt, float x, float y)
{
	float d = 1;
	rt->D = vector(x*(1.0f/WIDTH) , -y*(1.0f/HEIGHT), d);
}

void raytracer(t_vars *vars)
{

	t_object 	*obj;
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
			
			canvas_to_viewport(&rt, x, y); //get D
			obj = trace_ray(vars, &rt, 1.0f, INT_MAX); //get color
			if (!obj)
				my_mlx_pixel_put(&vars->img, x + WIDTH_2, y + HEIGHT_2, WHITE);
			else
			{
				rt.rl.final_rgb = ft_multiply_color(obj->color, compute_light(vars, obj, &rt.rl));
				my_mlx_pixel_put(&vars->img, x + WIDTH_2, y + HEIGHT_2, create_trgb(0, rt.rl.final_rgb)); //draw
				//my_mlx_pixel_put(&vars->img, x + WIDTH_2, y + HEIGHT_2, create_trgb(0, obj->color)); //draw
			}
			y++;
		}
	 	x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}