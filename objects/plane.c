#include "../includes/minirt.h"


static void rotate(t_cone *this)
{
    rotation_x(&this->direction, this->theta);
	rotation_y(&this->direction, this->phi);
	rotation_z(&this->direction, this->qsi);
}

/* Esta funcao recebe uma esfera e um raio retorna 
os pixels onde intersetam.
Ray equation: P = O + t(V - O)*/
static t_values intersect(t_raytracer *rt, t_plane *this)
{
	t_values local;
	float d;

	rt->c = -dot(this->direction, vector_subtract(rt->O, this->vector));
	rt->b = dot(rt->D, this->direction);
	if (rt->b < 0.0001f && rt->b > -0.0001f) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = rt->c / rt->b; 
	local.t2 = INT_MAX;
	return local;
}
	
t_object* new_plane(char *line)
{
	t_plane *plane;

	plane = new_object(sizeof(t_plane));
	plane->intersect = intersect;
	plane->rotate = rotate;
	plane->type = PLANE;
	plane->vector.x = ft_atof(&line);
	plane->vector.y = ft_atof(&line);
	plane->vector.z = ft_atof(&line);
	plane->direction.x = ft_atof(&line);
    plane->direction.y = ft_atof(&line);
    plane->direction.z = ft_atof(&line);
	plane->color.r = (int)ft_atof(&line);
    plane->color.g = (int)ft_atof(&line);
    plane->color.b = (int)ft_atof(&line);
	plane->specular = (int)ft_atof(&line);
	plane->refletive = ft_atof(&line);
	plane->theta = 0.0f;
	plane->phi = 0.0f;
	plane->qsi = 0.0f;
	return ((t_object *)plane);
}
