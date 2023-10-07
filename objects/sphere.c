#include "../includes/minirt.h"

/* Esta funcao recebe uma esfera e um raio retorna 
os pixels onde intersetam.
Ray equation: P = O + t(V - O)*/
static t_values intersect(t_raytracer *rt, t_sphere *this)
{
	t_values local;
	
	rt->CO = vector_subtract(rt->O, this->vector);
	rt->a  = dot(rt->D, rt->D);
	rt->b = 2.0f*dot(rt->CO, rt->D);
	rt->c = dot(rt->CO, rt->CO) - (this->diameter/2.0f)*(this->diameter/2.0f);
	rt->discriminant = rt->b*rt->b - 4.0f*(rt->a)*(rt->c);
	if (rt->discriminant < 0.0001f)
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = ((-(rt->b) + sqrt(rt->discriminant)) / (2.0f*rt->a));
	local.t2 = ((-(rt->b) - sqrt(rt->discriminant)) / (2.0f*rt->a));
	return local;
}

t_object* new_sphere(char *line)
{
	t_sphere *sphere;

	sphere = new_object(sizeof(t_sphere));
	sphere->intersect = intersect;
	sphere->type = SPHERE;
	sphere->vector.x = ft_atof(&line);
	sphere->vector.y = ft_atof(&line);
	sphere->vector.z = ft_atof(&line);
	sphere->diameter = ft_atof(&line);
	sphere->color.r = (int)ft_atof(&line);
    sphere->color.g = (int)ft_atof(&line);
    sphere->color.b = (int)ft_atof(&line);
	sphere->specular = (int)ft_atof(&line);
	sphere->refletive = ft_atof(&line);
	sphere->intensity = ft_atof(&line);
	sphere->next = NULL;
	return ((t_object *)sphere);
}
	
