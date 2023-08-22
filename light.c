#include "minirt.h"

t_light *new_light(float intensity, t_vector pos)
{
	t_light *new_light;
	
	new_light = (t_light*) calloc(sizeof(t_light) , 1);
	new_light->intensity = intensity;
	new_light->position = vector(pos.x, pos.y, pos.z);
	return (new_light);
}