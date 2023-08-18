#include "minirt.h"

bool inside(float t, float t_min, float t_max)
{
	if (t >= t_min && t <= t_max )
		return false;
	return true;
}

/* Esta funcao recebe uma esfera e um raio retorna 
os pixels onde intersetam */
t_values intersect_ray_sphere(t_raytracer *rt, t_sphere *this)
{
	t_values local;
	rt->CO = vector_operation(rt->O, '-', this->diameter/2);
	rt->a  = dot(rt->D, rt->D);
	rt->b = 2*dot(rt->CO, rt->D);
	rt->c = dot(rt->CO, rt->CO) - pow((this->diameter/2), 2);

	rt->discriminant = rt->b*rt->b - 4*rt->a*rt->c;
	if (rt->discriminant < 0) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = (-(rt->b) + sqrt(rt->discriminant) / (2*rt->a));
	local.t2 = (-(rt->b) - sqrt(rt->discriminant) / (2*rt->a));
	return local;

}

/*  */
int trace_ray(t_vars* vars ,t_raytracer* rt, float t_min, float t_max)
{
	float closest_t = INT_MAX;
	t_sphere *closest_sphere = NULL;
	int i = 0;
	while (vars->objects[i] && vars->objects[i]->shape == SPHERE)
	{	
        rt->t = intersect_ray_sphere(rt, vars->objects[i]); //get t1 and t2
		printf("t1 %i, t2 %i\n", rt->t.t1, rt->t.t2);
		if (inside(rt->t1, t_min, t_max) && rt->t1 < closest_t) 
		{
            closest_t = rt->t1;
            closest_sphere = vars->objects[i];
        }
        if (inside(rt->t2, t_min, t_max) && rt->t2 < closest_t) 
		{
            closest_t = rt->t2;
            closest_sphere = vars->objects[i];
        }
		i++;
    }
    if (!closest_sphere) {
       return (WHITE);
    }
    return closest_sphere->color;	
}

void canvas_to_viewport(t_raytracer *rt, int x, int y)
{
	int d = 1;
	rt->D = vector(x*(1/500) , y*(1/500), d);
}

void raytracer(t_vars *vars)
{
	t_raytracer rt;
	int			x;
	int			y;

	x = -250;
	y = -250;
	rt.O = vector(0, 0, 0);
	while (y < 250)
	{
		while (x < 250)
		{
			canvas_to_viewport(&rt, x, y); //get D
			trace_ray(vars, &rt, 1, INT_MAX); //get color
			my_mlx_pixel_put(&vars->img, (int)x + 250, (int)y + 250, rt.color); //draw
			x++;
		}
		y++;
	}
}