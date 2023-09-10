#include "../includes/minirt.h"

void* new_object(int size)
{
	t_object *object;

	object = (t_object *)ft_calloc(size, 1);
	return (object);
}

