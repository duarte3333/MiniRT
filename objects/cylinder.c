#include "../includes/minirt.h"

/* Esta funcao recebe uma cilindro e um raio retorna 
os pixels onde intersetam.
Ray equation: P = O + t(V - O)*/

static t_values intersect_planes(t_raytracer *rt, t_vector dir, t_vector point)
{
	t_values local;
	float d;

	d = -dot(dir, point);
	rt->b = dot(dir, rt->D);
	rt->c = (-1)*dot(dir, rt->O) - d;
	if (rt->b < 0.0001f && rt->b > -0.0001f) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = rt->c / rt->b; 
	local.t2 = rt->c / rt->b; 
	return local;
}

float	distance(t_vector v1, t_vector v2)
{
	return (sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) \
		+ pow(v1.z - v2.z, 2)));
}

static t_values check_height(t_raytracer *rt, t_cylinder *this, t_values t)
{
	t_vector P;
	t_vector B;
	float	 k;

	P = vector_add(rt->O, vector_mult_const(rt->D, t.t1));
	k = dot(P, this->axis) - dot(this->vector, this->axis) / dot(this->axis, this->axis); 
	B = vector_add(this->vector, vector_mult_const(this->axis, k));
	if (abs(distance(B, this->vector)) > this->height / 2 )
		t.t1 = INT_MAX;
	P = vector_add(rt->O, vector_mult_const(rt->D, t.t2));
	k = dot(P, this->axis) - dot(this->vector, this->axis) / dot(this->axis, this->axis); 
	B = vector_add(this->vector, vector_mult_const(this->axis, k));
	if (abs(distance(B, this->vector)) > this->height/2)
		t.t2 = INT_MAX;
	return t;
}

static t_values check_width(t_cylinder *this, t_raytracer *rt, t_values t)
{
	t_vector P;
	t_vector B;
	t_vector minus_B;
	float	 k;

	P = vector_add(rt->O, vector_mult_const(rt->D, t.t1));
	k = dot(P, this->axis) - dot(this->vector, this->axis) / dot(this->axis, this->axis); 
	B = vector_add(this->vector, vector_mult_const(this->axis, k));
	minus_B = vector_add(this->vector, vector_mult_const(this->axis, -k));
	if (abs(distance(B, this->vector)) > (this->height/2 - 0.001) && abs(distance(B, this->vector)) < (this->height/2 + 0.001))
	{
		t = intersect_planes(rt, this->axis, B);
		t = intersect_planes(rt, this->axis, minus_B);
	}
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
	//local.t1 = check_width(this, rt, local.t1);
	local.t2 = ((-(rt->b) - sqrt(rt->discriminant)) / (2.0f*rt->a));
	local = check_height(rt, this, local);
	//local = check_width(rt, this, local);

	//local.t2 = check_width(this, rt, local.t2);
	return local;
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
	