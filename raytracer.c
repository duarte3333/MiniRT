#include "minirt.h"

bool inside(float t, float t_min, float t_max)
{
	if (t >= t_min && t < t_max )
		return true;
	return false;
}

/* Esta funcao recebe uma esfera e um raio retorna 
os pixels onde intersetam.
Ray equation: P = O + t(V - O)*/
t_values intersect_ray_sphere(t_raytracer *rt, t_sphere *this)
{
	t_values local;
	rt->CO = vector_operation(rt->O, this->vector);
	rt->a  = dot(rt->D, rt->D);
	rt->b = 2.0f*dot(rt->CO, rt->D);
	rt->c = dot(rt->CO, rt->CO) - (this->diameter/2.0f)*(this->diameter/2.0f);
	rt->discriminant = rt->b*rt->b - 4.0f*(rt->a)*(rt->c);
	//if (rt->discriminant < 0.0f)
	//printf("a:%f b:%f c:%f\n", rt->a, rt->b, rt->c);
	//printf("res: %f \n", ((-(rt->b) + sqrt(rt->discriminant)) / (2.0f*rt->a)));
	if (rt->discriminant < 0.0f) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	//printf("t1 %i, t2 %i\n", rt->t.t1, rt->t.t2);
	local.t1 = ((-(rt->b) + sqrt(rt->discriminant)) / (2.0f*rt->a));
	local.t2 = ((-(rt->b) - sqrt(rt->discriminant)) / (2.0f*rt->a));
	return local;

}

void trace_ray(t_vars* vars ,t_raytracer* rt, float t_min, float t_max)
{
	float closest_t = INT_MAX;
	t_sphere *closest_sphere = NULL;
	int i = 0;
	while (vars->objects[i] && vars->objects[i]->shape == SPHERE)
	{	
        rt->t = intersect_ray_sphere(rt, vars->objects[i]); //get t1 and t2
		//printf("t1 %f, t2 %f\n", rt->t.t1, rt->t.t2);
		if (inside(rt->t.t1, t_min, t_max) && rt->t.t1 < closest_t ) 
		{
            closest_t = rt->t.t1;
            closest_sphere = vars->objects[i];
        }
        if (inside(rt->t.t2, t_min, t_max) && rt->t.t2 < closest_t) 
		{
            closest_t = rt->t.t2;
            closest_sphere = vars->objects[i];
        }
		i++;
    }
    if (!closest_sphere)
       rt->color = (WHITE);
	else
	{
    	rt->color = closest_sphere->color;	
	}
}

void canvas_to_viewport(t_raytracer *rt, float x, float y)
{
	float d = 1;
	rt->D = vector(x*(1.0f/500.0f) , y*(1.0f/500.0f), d);
	//printf("D.x %f, D.y %f, D.z %f\n", rt->D.x, rt->D.y, rt->D.z);
}

time_t	get_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, 0);
	return ((curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000));
}

void raytracer(t_vars *vars)
{
	t_raytracer rt;
	int			x;
	int			y;
	unsigned long start;
	start = get_time();

	x = -250;
	rt.O = vector(0, 0, 0);
	while (x < 250)
	{
		y = -250;
		while (y < 250)
		{
			canvas_to_viewport(&rt, x, y); //get D
			//printf("x: %i, y: %i\n", x, y);
			//printf("D.x %f, D.y %f, D.z %f\n", rt.D.x, rt.D.y, rt.D.z);
			trace_ray(vars, &rt, 1.0f, INT_MAX); //get color
			my_mlx_pixel_put(&vars->img, x + 250, y + 250, rt.color); //draw
			y++;
		}
	 	x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	printf("duration: %lu\n", get_time() - start);
}