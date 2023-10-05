#ifndef VECTOR_H
# define VECTOR_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <fcntl.h>
# include <pthread.h>
# include <math.h>


# include "../minilibx/mlx.h"
# include "X11/X.h"
# include "X11/keysym.h"

typedef struct  s_vector 	 t_vector;

struct s_vector
{
	float x;
	float y;
	float z;
};

//Vector
t_vector 	vector(float x, float y, float z);
t_vector 	vector_subtract(t_vector vec, t_vector vec2);
t_vector 	vector_add(t_vector vec, t_vector vec2);
t_vector 	vector_multiply(t_vector vec, t_vector vec2);
t_vector 	vector_divide(t_vector vec, t_vector vec2);	
float 		dot(t_vector va, t_vector vb);
float 		module(t_vector vec);
t_vector 	vector_mult_const(t_vector vec, float value);
t_vector 	vector_div_const(t_vector vec, float value);
#endif