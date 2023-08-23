#ifndef RAYTRACER_H
# define RAYTRACER_H

typedef struct  s_values 	 t_values;
typedef struct 	s_raytracer  t_raytracer;
typedef struct  s_raylight 	 t_raylight;

struct s_values
{
	float t1;
	float t2;
};

struct s_raylight{
	t_vector 	P;
	t_vector 	N;
	t_vector 	L;
	float 		n_dot_l;
	float 		i;
	int			after_color;
	t_color		final_rgb;
};

struct s_raytracer{
	float		a;
	float 		b;
	float 		c;
	float 		discriminant;
	t_vector 	CO;
	t_vector 	O;
	t_vector 	D;
	t_values 	t;
	t_raylight 	rl;
};


# endif