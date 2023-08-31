#include "includes/minirt.h"

/* Esta funcao recebe uma esfera e um raio retorna 
os pixels onde intersetam.
Ray equation: P = O + t(V - O)*/
static t_values intersect(t_raytracer *rt, t_cylinder *this)
{
	t_values local;
	float close;

	rt->a = rt->D.x*rt->D.x + rt->D.y*rt->D.y;
	rt->b = 2.0f*rt->D.x*rt->O.x + 2.0f*rt->D.y*rt->O.y;
	rt->c = rt->O.x*rt->O.x + rt->O.y*rt->O.y - this->diameter/2;
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

t_object* new_cylinder(t_vector axis, t_vector coord, float diameter, float height, t_color color, int specular, float reflective)
{
	t_cylinder *cylinder;

	cylinder = new_object(sizeof(t_cylinder));
	cylinder->intersect = intersect;
	cylinder->type = CYLINDER;
	cylinder->vector = coord;
	cylinder->color = color;
	cylinder->diameter = diameter;
	cylinder->height = reflective;
	cylinder->specular = specular;
	cylinder->refletive = reflective;
	cylinder->axis = axis;
	return ((t_object *)cylinder);
}
	