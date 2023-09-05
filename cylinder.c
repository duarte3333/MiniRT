#include "includes/minirt.h"

/* Esta funcao recebe uma esfera e um raio retorna 
os pixels onde intersetam.
Ray equation: P = O + t(V - O)*/
static t_values intersect(t_raytracer *rt, t_cylinder *this)
{
	t_values local;
	float close;
	t_vector CO;

	CO = vector_subtract(rt->O, this->vector);

	rt->a = pow(dot(rt->D, this->axis), 2) - pow(module(rt->D), 2) * pow(module(this->axis),2);
	rt->b = 2.0f*dot(CO, this->axis)*dot(rt->D, this->axis) - \
		2.0f*module(CO)*module(rt->D)*pow(module(this->axis),2);
	rt->c = pow(dot(CO, this->axis), 2) - pow(module(this->axis),2)*pow(module(CO),2) \
		- pow(module(this->axis),2)*pow((this->diameter/2), 2);
	rt->discriminant = rt->b*rt->b - 4.0f*(rt->a)*(rt->c);
	if (rt->discriminant < 0.0001f) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = ((-(rt->b) + sqrt(rt->discriminant)) / (2.0f*rt->a));
	local.t2 = ((-(rt->b) - sqrt(rt->discriminant)) / (2.0f*rt->a));
	return local;
	// float r = rt->D.y + close*1;
	// if (r > this->vector.y && (r <= (this->vector.y + this->height)))
	// 	return local;
	// else
	// {
	// 	local.t1 = INT_MAX;
	// 	local.t2 = INT_MAX;
	// 	return local;
	// }
	// float r = rt->D.y + rt->closest_t * this->axis.y;
	// if (r >  this->vector.y && (r <= (this->vector.y + HEIGHT)))
	// 	return local;
	// else 
	// {
	// 	local.t1 = INT_MAX;
	// 	local.t2 = INT_MAX;
	// 	return local;
	//}
}

t_object* new_cylinder(char* line)
{
	t_cylinder *cylinder;

	cylinder = new_object(sizeof(t_cylinder));
	cylinder->intersect = intersect;
	cylinder->type = CYLINDER;
	cylinder->vector.x = ft_atof(&line);
	cylinder->vector.y = ft_atof(&line);
	cylinder->vector.z = ft_atof(&line);
	cylinder->axis.x = ft_atof(&line);
	cylinder->axis.y = ft_atof(&line);
	cylinder->axis.z = ft_atof(&line);
	cylinder->diameter = ft_atof(&line);
	cylinder->height = ft_atof(&line);
	cylinder->color.r = (int)ft_atof(&line);
    cylinder->color.g = (int)ft_atof(&line);
    cylinder->color.b = (int)ft_atof(&line);
	cylinder->specular = (int)ft_atof(&line);
	cylinder->refletive = ft_atof(&line);
	return ((t_object *)cylinder);
}
	