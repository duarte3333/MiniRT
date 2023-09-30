#include "../includes/minirt.h"


int shadow_light(t_scene *scene, t_raytracer *rt, t_vector light_vec)
{
	t_object *obj;
	t_raytracer newRT;

	newRT = *(rt);
	newRT.O = rt->rl.P;
	newRT.D = rt->rl.L;
	obj = closest_intersection(&newRT, (t_vector){0.01f, 1, 0});
/* 	if (obj)
		printf("color: %i\n", obj->color.g); */
	return (obj != NULL);
}

void specular_light(t_object *tmp, t_scene *scene, t_raytracer *rt)
{
	if (rt->rl.s)
	{
		rt->rl.aux = vector(2*dot(rt->rl.N, rt->rl.L), 2.0f*dot(rt->rl.N, rt->rl.L), 2.0f*dot(rt->rl.N, rt->rl.L));
		rt->rl.R = vector_subtract(vector_multiply(rt->rl.N, rt->rl.aux), rt->rl.L);
		rt->rl.r_dot_v = dot(rt->rl.R, rt->rl.V);
		if(rt->rl.r_dot_v > 0.001f) 
		{
			rt->rl.i[0] += tmp->intensity * pow(rt->rl.r_dot_v / (module(rt->rl.R)*module(rt->rl.V)), rt->rl.s) * ((float)tmp->color.r/255.0f);
			rt->rl.i[1] += tmp->intensity * pow(rt->rl.r_dot_v / (module(rt->rl.R)*module(rt->rl.V)), rt->rl.s) * ((float)tmp->color.g/255.0f);
			rt->rl.i[2] += tmp->intensity * pow(rt->rl.r_dot_v / (module(rt->rl.R)*module(rt->rl.V)), rt->rl.s) * ((float)tmp->color.b/255.0f);
		}
	}
}

void diffuse_light(t_object *tmp, t_scene *scene, t_raytracer *rt)
{
	rt->rl.n_dot_l = dot(rt->rl.N, rt->rl.L);
	if (rt->rl.n_dot_l > 0.001f)
	{
		rt->rl.i[0] += (tmp->intensity * rt->rl.n_dot_l)/(module(rt->rl.N)*module(rt->rl.L)) * ((float)tmp->color.r/255.0f);
		rt->rl.i[1] += (tmp->intensity * rt->rl.n_dot_l)/(module(rt->rl.N)*module(rt->rl.L)) * ((float)tmp->color.g/255.0f);
		rt->rl.i[2] += (tmp->intensity * rt->rl.n_dot_l)/(module(rt->rl.N)*module(rt->rl.L)) * ((float)tmp->color.b/255.0f);
	}
}

float *compute_light(t_raytracer *rt)
{
	t_object *tmp;

	rt->rl.i[0] = 0.0f;
	rt->rl.i[1] = 0.0f;
	rt->rl.i[2] = 0.0f;
	tmp = vars()->scene->light;
 	while(tmp)
	{	
		if (tmp->type == AMBIENT)
		{
			rt->rl.i[0] += tmp->intensity*((float)tmp->color.r / 255.0f);
			rt->rl.i[1] += tmp->intensity*((float)tmp->color.g / 255.0f);
			rt->rl.i[2] += tmp->intensity*((float)tmp->color.b / 255.0f);
		}
		else
		{
			if (tmp->type == POINT)
				rt->rl.L = vector_subtract(tmp->vector, rt->rl.P);
			else if(tmp->type == DIRECTIONAL)
				rt->rl.L = tmp->vector;
			if (shadow_light(vars()->scene, rt, tmp->vector))
			{
				tmp = tmp->next;
			 	continue;
			}
			diffuse_light(tmp, vars()->scene, rt);
			specular_light(tmp, vars()->scene, rt);
		}
		tmp = tmp->next;
	}
	int i = -1;
	while (rt->rl.i[++i])
	{
		if (rt->rl.i[i] > 0.99f)
			rt->rl.i[i] = 1;
	}
	return rt->rl.i;
}

t_object *new_light(char *line, t_type type)
{
	t_light *new_light;

	// if (!check_light())
	//  	return NULL;
	new_light = new_object(sizeof(t_light));
	new_light->type = type;
	if (new_light->type != AMBIENT)
	{
		new_light->vector.x = ft_atof(&line);
	    new_light->vector.y = ft_atof(&line);
	    new_light->vector.z = ft_atof(&line);
	}
	new_light->intensity = ft_atof(&line);
    new_light->color.r = (int)ft_atof(&line);
    new_light->color.g = (int)ft_atof(&line);
    new_light->color.b = (int)ft_atof(&line);
	return ((t_object *)new_light);
}