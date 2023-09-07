#include "../includes/minirt.h"

void* new_object(int size)
{
	t_object *object;

	object = (t_object *)calloc(size, 1);
	return (object);
}

