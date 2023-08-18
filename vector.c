#include "minirt.h"

t_vector vector(int x, int y, int z){
	return ((t_vector){x, y, z});
}

t_vector vector_operation(t_vector vec, char operation, float nb)
{
	switch(operation)
    {
        case '+':
			vec.x += nb;
			vec.y += nb;
			vec.z += nb;
            break;

        case '-':
			vec.x -= nb;
			vec.y -= nb;
			vec.z -= nb;
            break;

        case '*':
			vec.x *= nb;
			vec.y *= nb;
			vec.z *= nb;
            break;

        case '/':
			vec.x /= nb;
			vec.y /= nb;
			vec.z /= nb;
            break;
	}
	return (vec);
}

float dot(t_vector va, t_vector vb)
{
	return ((va.x)*(vb.x) + (va.y)*(vb.y) + (va.z)*(vb.z));
}