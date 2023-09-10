#include "../includes/minirt.h"

/* Esta funcao recebe uma cilindro e um raio retorna 
os pixels onde intersetam.
Ray equation: P = O + t(V - O)*/

float	distance(t_vector v1, t_vector v2)
{
	return (sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) \
		+ pow(v1.z - v2.z, 2)));
}

static float check_height(t_raytracer *rt, t_cylinder *this, float t)
{
	t_vector P_local;
	t_vector new_P;

	P_local =vector_add(rt->O, vector_multiply(rt->D, vector(t, t, t)));
	float k = dot(P_local, this->axis) - dot(this->vector, this->axis) / dot(this->axis, this->axis); 
	new_P = vector_add(this->vector, vector_multiply(vector(k,k,k), this->axis));
	if (distance(new_P, this->vector) > this->height / 2 )
		return INT_MAX;
	return t;
}

static void rotate(t_cylinder *this, t_rotation rotation)
{
	float increment;

	increment = 0.05;
	this->theta *= ((rotation == X_theta_1) - (rotation == X_theta_2))*increment;
	rotation_x(&this->axis, this->theta);
	this->phi *= ((rotation == Y_phi_1) - (rotation == Y_phi_2))*increment;
	rotation_y(&this->axis, this->phi);
	this->qsi *= ((rotation == Z_qsi_1) - (rotation == Z_qsi_2))*increment;
	rotation_z(&this->axis, this->qsi);
}

static t_values intersect(t_raytracer *rt, t_cylinder *this)
{
	t_values local;
	t_vector CO;

	rotation_z(&this->axis, this->qsi);
	CO = vector_subtract(rt->O, this->vector);

	rt->a = dot(rt->D, rt->D) * pow(module(this->axis),2) - \
		pow(dot(rt->D, this->axis), 2);
	rt->b = 2.0f*dot(CO, rt->D)*pow(module(this->axis), 2) - \
		2.0f*dot(rt->D, this->axis)*dot(CO, this->axis);
	rt->c = (dot(CO, CO) - pow(this->diameter/2, 2))*pow(module(this->axis), 2) - \
		pow(dot(CO, this->axis), 2);

	rt->discriminant = rt->b*rt->b - 4.0f*(rt->a)*(rt->c);
	if (rt->discriminant < 0.001f) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = ((-(rt->b) + sqrt(rt->discriminant)) / (2.0f*rt->a));
	local.t1 = check_height(rt, this, local.t1);
	local.t2 = ((-(rt->b) - sqrt(rt->discriminant)) / (2.0f*rt->a));
	local.t2 = check_height(rt, this, local.t2);
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
	cylinder->rotate = rotate;
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
	cylinder->theta = 0.0f;
	cylinder->phi = 0.0f;
	cylinder->qsi = 0.0f;
	return ((t_object *)cylinder);
}
	