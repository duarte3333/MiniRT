#include "includes/minirt.h"

static t_values intersect(t_vector O, t_vector D, t_sphere *this)
{
	t_values local;
	t_vector CO = vector_subtract(O, this->vector);
	float a  = dot(D, D);
	float b = 2.0f*dot(CO, D);
	float c = dot(CO, CO) - (this->diameter/2.0f)*(this->diameter/2.0f);
	float discriminant = b*b - 4.0f*(a)*(c);
	if (discriminant < 0.0001f) //sem solucao
	{
		local.t1 = INT_MAX;
		local.t2 = INT_MAX;
		return local;
	}
	local.t1 = ((-(b) + sqrt(discriminant)) / (2.0f*a));
	local.t2 = ((-(b) - sqrt(discriminant)) / (2.0f*a));
	return local;
}

int in_shadow(t_vars* vars ,t_vector O, t_vector D){
	int i;
	i = 0;

	t_values t;
	while (vars->objects[i])
	{	
        t = intersect(O, D, vars->objects[i]); //get t1 and t2
		if (t.t1 > 0.01f && t.t1 < 1.0f)
			return 1;
        if (t.t2 > 0.01f && t.t2 < 1.0f)
			return 1;
		i++;
    }
	return 0;
}

float compute_light(t_vars *vars, t_raytracer *rt)
{
	int j;
	t_object *shadow_object;
	t_object *tempClosest;
	t_vector tempO;
	t_vector tempD;

	rt->rl.i = 0.0f;
	j = -1;

	tempClosest = rt->closest_obj;
	tempO = rt->O;
	tempD = rt->D;
 	while(vars->lights[++j])
	{	
		if (vars->lights[j]->type == AMBIENT)
			rt->rl.i += vars->lights[j]->intensity;
		else
		{
			if (vars->lights[j]->type == POINT)
				rt->rl.L = vector_subtract(vars->lights[j]->position, rt->rl.P);
			else if(vars->lights[j]->type == DIRECTIONAL)
				rt->rl.L = vars->lights[j]->position;

			//Shadow Check
			rt->O = rt->rl.P;
			rt->D = rt->rl.L;
			shadow_object = closest_intersection(vars, rt, 0.01f, INT_MAX);
			rt->O = tempO;
			rt->D = tempD;
			if (shadow_object)
				continue;
			
			//Diffuse
			rt->rl.n_dot_l = dot(rt->rl.N, rt->rl.L);
			if (rt->rl.n_dot_l > 0.001f)
				rt->rl.i += (vars->lights[j]->intensity * rt->rl.n_dot_l)/(module(rt->rl.N)*module(rt->rl.L));
			
			//Specular
			if (rt->rl.s)
			{
				rt->rl.aux = vector(2*dot(rt->rl.N, rt->rl.L), 2*dot(rt->rl.N, rt->rl.L), 2*dot(rt->rl.N, rt->rl.L));
				rt->rl.R = vector_subtract(vector_multiply(rt->rl.N, rt->rl.aux), rt->rl.L);
				rt->rl.r_dot_v = dot(rt->rl.R, rt->rl.V);
				if(rt->rl.r_dot_v > 0.001f) 
					rt->rl.i += vars->lights[j]->intensity * pow(rt->rl.r_dot_v / (module(rt->rl.R)*module(rt->rl.V)), rt->rl.s);
			}

		}
	}
	rt->closest_obj = tempClosest;
	return rt->rl.i;
}


t_light *new_light(float intensity, t_vector pos, t_type type)
{
	t_light *new_light;
	
	new_light = (t_light*)new_object(sizeof(t_light));
	new_light->intensity = intensity;
	new_light->position = vector(pos.x, pos.y, pos.z);
	new_light->type = type;
	return (new_light);
}