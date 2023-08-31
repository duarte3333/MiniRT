#include "includes/minirt.h"


/* Esta funcao recebe uma esfera e um raio retorna 
os pixels onde intersetam.
Ray equation: P = O + t(V - O)*/
static t_values intersect(t_raytracer *rt, t_plane *this)
{
	t_values local;
	float d;

	d = -dot(this->direction, this->vector);
	rt->b = dot(this->direction, rt->D);
	rt->c = (-1)*dot(this->direction, rt->O) + d;
	if (rt->b < 0.0001f) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = rt->c / rt->b; 
	local.t2 = rt->c / rt->b; 
	return local;
}
	
t_object* new_plane(char *line)
{
	t_plane *plane;

	plane = new_object(sizeof(t_plane));
	plane->intersect = intersect;
	plane->type = PLANE;
	plane->vector.x = ft_atof(&line, 1.0f, 0.0f, 0.0f);
	plane->vector.y = ft_atof(&line, 1.0f, 0.0f, 0.0f);
	plane->vector.z = ft_atof(&line, 1.0f, 0.0f, 0.0f);
	plane->direction.x = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    plane->direction.y = ft_atof(&line, 1.0f, 0.0f, 0.0f);
    plane->direction.z = ft_atof(&line, 1.0f, 0.0f, 0.0f);

	plane->color.r = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    plane->color.g = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
    plane->color.b = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
	plane->specular = (int)ft_atof(&line, 1.0f, 0.0f, 0.0f);
	plane->refletive = ft_atof(&line, 1.0f, 0.0f, 0.0f);
	return ((t_object *)plane);
}
