#include "../includes/minirt.h"

static t_values intersect(t_raytracer *rt, t_cone *this)
{
    t_values local;
    t_vector p;
    float    value;

    this->tmp = vector_mult_const(this->direction, this->height);
    this->direction = vector_div_const(this->tmp, module(this->tmp));
    this->m = pow(this->radius / this->height, 2);
    rt->CO = vector_subtract(rt->O, this->vector);
    rt->a = dot(rt->D, rt->D) - this->m * pow(dot(rt->D, this->direction), 2) - pow(dot(rt->D, this->direction), 2);
    rt->b = 2 * (dot(rt->D, rt->CO) - this->m * dot(rt->D, this->direction) * dot(rt->CO, this->direction) - dot(rt->D, this->direction) * dot(rt->CO, this->direction));
    rt->c = dot(rt->CO, rt->CO) - this->m * pow(dot(rt->CO, this->direction), 2) - pow(dot(rt->CO, this->direction), 2);
    rt->discriminant = rt->b*rt->b - 4.0f*(rt->a)*(rt->c);
	if (rt->discriminant < 0.0001f) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = ((-(rt->b) + sqrt(rt->discriminant)) / (2.0f*rt->a));
	local.t2 = ((-(rt->b) - sqrt(rt->discriminant)) / (2.0f*rt->a));
    p = vector_add(rt->O, vector_mult_const(rt->D, local.t1));
    value = dot(vector_subtract(p, this->vector), this->direction);
    if (value < 0.001f || value > module(this->tmp))
        local.t1 = INT_MAX;
    p = vector_add(rt->O, vector_mult_const(rt->D, local.t2));
    value = dot(vector_subtract(p, this->vector), this->direction);
    if (value < 0.001f || value > module(this->tmp))
        local.t2 = INT_MAX; 
	return local;
}

t_object* new_cone(char *line)
{
    t_cone *cone;

    cone = new_object(sizeof(t_cone));
    cone->intersect = intersect;
    cone->type = CONE;
    cone->vector.x = ft_atof(&line);
    cone->vector.y = ft_atof(&line);
    cone->vector.z = ft_atof(&line);
    cone->direction.x = ft_atof(&line);
    cone->direction.y = ft_atof(&line);
    cone->direction.z = ft_atof(&line);
    cone->height = ft_atof(&line);
    cone->radius = ft_atof(&line);
    cone->color.r = (int)ft_atof(&line);
    cone->color.g = (int)ft_atof(&line);
    cone->color.b = (int)ft_atof(&line);
    cone->specular = (int)ft_atof(&line);
	cone->refletive = ft_atof(&line);

	return ((t_object *)cone);
}

/* static t_values intersect(t_raytracer *rt, t_cone *this)
{
    t_values local;
    t_vector p;
    float    value;

    rt->CO = vector_subtract(rt->O, this->vector);
    rt->a = dot(rt->D, rt->D) - this->m * pow(dot(rt->D, this->direction), 2) - pow(dot(rt->D, this->direction), 2);
    rt->b = 2 * (dot(rt->D, rt->CO) - this->m * dot(rt->D, this->direction) * dot(rt->CO, this->direction) - dot(rt->D, this->direction) * dot(rt->CO, this->direction));
    rt->c = dot(rt->CO, rt->CO) - this->m * pow(dot(rt->CO, this->direction), 2) - pow(dot(rt->CO, this->direction), 2);
    rt->discriminant = rt->b*rt->b - 4.0f*(rt->a)*(rt->c);
	if (rt->discriminant < 0.0001f) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = ((-(rt->b) + sqrt(rt->discriminant)) / (2.0f*rt->a));
	local.t2 = ((-(rt->b) - sqrt(rt->discriminant)) / (2.0f*rt->a));
    p = vector_add(rt->O, vector_mult_const(rt->D, local.t1));
    value = dot(vector_subtract(p, this->vector), this->direction);
    if ((value < 0.001f && value > -0.001f) || value > module(this->tmp))
        local.t1 = INT_MAX;
    p = vector_add(rt->O, vector_mult_const(rt->D, local.t2));de coisas pra se sent
    value = dot(vector_subtract(p, this->vector), this->direction);
    if ((value < 0.001f && value > -0.001f) || value > module(this->tmp))
        local.t2 = INT_MAX; 
	return local;
}

t_object* new_cone(char *line)
{
    t_cone *cone;

    cone = new_object(sizeof(t_cone));
    cone->intersect = intersect;
    cone->type = CONE;
    cone->vector.x = ft_atof(&line);
    cone->vector.y = ft_atof(&line);
    cone->vector.z = ft_atof(&line);
    cone->base.x = ft_atof(&line);
    cone->base.y = ft_atof(&line);
    cone->base.z = ft_atof(&line);
    cone->tmp = vector_subtract(cone->base, cone->vector);
    cone->direction = vector_div_const(cone->tmp, module(cone->tmp));
    cone->radius = ft_atof(&line);
    cone->m = pow(cone->radius / module(cone->tmp), 2);
    cone->color.r = (int)ft_atof(&line);
    cone->color.g = (int)ft_atof(&line);
    cone->color.b = (int)ft_atof(&line);
    cone->specular = (int)ft_atof(&line);
	cone->refletive = ft_atof(&line);
	return ((t_object *)cone);
} */