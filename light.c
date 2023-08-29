#include "includes/minirt.h"

int shadow_light(t_vars *vars, t_raytracer *rt)
{
	t_vector tempO;
	t_vector tempD;
	t_object *obj;

	tempO = rt->O;
	tempD = rt->D;
	rt->O = rt->rl.P;
	rt->D = rt->rl.L;
	obj = closest_intersection(vars, rt, 0.01f, INT_MAX);
	rt->O = tempO;
	rt->D = tempD;
	return (obj != NULL);
}

void specular_light(t_vars *vars, t_raytracer *rt, int j)
{
	if (rt->rl.s)
	{
		rt->rl.aux = vector(2*dot(rt->rl.N, rt->rl.L), 2*dot(rt->rl.N, rt->rl.L), 2*dot(rt->rl.N, rt->rl.L));
		rt->rl.R = vector_subtract(vector_multiply(rt->rl.N, rt->rl.aux), rt->rl.L);
		rt->rl.r_dot_v = dot(rt->rl.R, rt->rl.V);
		if(rt->rl.r_dot_v > 0.001f) 
			rt->rl.i += vars->lights[j]->intensity * pow(rt->rl.r_dot_v / (module(rt->rl.R)*module(rt->rl.V)), rt->rl.s);
	}
}

void diffuse_light(t_vars *vars, t_raytracer *rt, int j)
{
	rt->rl.n_dot_l = dot(rt->rl.N, rt->rl.L);
	if (rt->rl.n_dot_l > 0.001f)
		rt->rl.i += (vars->lights[j]->intensity * rt->rl.n_dot_l)/(module(rt->rl.N)*module(rt->rl.L));
}

float compute_light(t_vars *vars, t_raytracer *rt)
{
	int j;
	//t_object *tempClosest;

	rt->rl.i = 0.0f;
	j = -1;
	//tempClosest = rt->closest_obj;
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
			if (shadow_light(vars, rt))
				continue;
			diffuse_light(vars, rt, j);
			specular_light(vars, rt, j);
		}
	}
	//rt->closest_obj = tempClosest;
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