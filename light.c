#include "includes/minirt.h"

float compute_light(t_vars *vars, t_object *this, t_raylight *rl)
{
	int j;

	rl->i = 0.0f;
	j = -1;
 	while(vars->lights[++j])
	{
		if (vars->lights[j]->type == AMBIENT)
			rl->i += vars->lights[j]->intensity;
		else
		{
			if (vars->lights[j]->type == POINT)
				rl->L = vector_subtract(vars->lights[j]->position, rl->P);
			else if(vars->lights[j]->type == DIRECTIONAL)
				rl->L = vars->lights[j]->position;
			rl->n_dot_l = dot(rl->N, rl->L);
			if (rl->n_dot_l > 0.0001)
				rl->i += (vars->lights[j]->intensity * rl->n_dot_l)/(module(rl->N)*module(rl->L));
		}
	}
	return rl->i;
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