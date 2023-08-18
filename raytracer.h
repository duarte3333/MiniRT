#ifndef RAYTRACER_H
# define RAYTRACER_H

typedef struct  s_values 	 t_values;
typedef struct 	s_raytracer  t_raytracer;
typedef struct  s_vector 	 t_vector;

struct s_vector
{
	float x;
	float y;
	float z;
};

struct s_values
{
	float t1;
	float t2;
};

struct s_raytracer{
	float a;
	float b;
	float c;
	float discriminant;
	float t1;
	float t2;
	t_vector CO;
	t_vector O;
	t_vector D;
	int color;
	t_values t;
};


# endif