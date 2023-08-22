#include "minirt.h"

bool inside(float t, float t_min, float t_max)
{
	if (t >= t_min && t < t_max )
		return true;
	return false;
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
    if (!closest_obj)
       return NULL;
	return (closest_obj);
}

void canvas_to_viewport(t_raytracer *rt, float x, float y)
{
	float d = 1;
	rt->D = vector(x*(1.0f/WIDTH) , -y*(1.0f/HEIGHT), d);
}

time_t	get_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, 0);
	return ((curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000));
}

void raytracer(t_vars *vars)
{

	t_object 	*obj;
	t_raytracer rt;
	int			x;
	int			y;
	unsigned long start;
	start = get_time();

	x = -WIDTH_2;
	rt.O = vector(0, 0, 0);
	while (x < WIDTH_2)
	{
		y = -HEIGHT_2;

		while (y < HEIGHT_2)
		{
			
			canvas_to_viewport(&rt, x, y); //get D
			obj = trace_ray(vars, &rt, 1.0f, INT_MAX); //get color
			compute_light(vars);
			if (!obj)
				my_mlx_pixel_put(&vars->img, x + WIDTH_2, y + HEIGHT_2, WHITE);
			else
			{
				my_mlx_pixel_put(&vars->img, x + WIDTH_2, y + HEIGHT_2, obj->color); //draw
			}
			y++;
		}
	 	x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	//printf("duration: %lu\n", get_time() - start);
}