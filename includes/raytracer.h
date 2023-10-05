#ifndef RAYTRACER_H
# define RAYTRACER_H

typedef struct  s_values 	 t_values;
typedef struct 	s_raytracer  t_raytracer;
typedef struct  s_raylight 	 t_raylight;
typedef struct	s_ray_thread t_ray_thread;
typedef struct	s_chunk 	 t_chunk;

struct s_values
{
	float t1;
	float t2;
};

struct s_chunk
{
	int x;
	int y;
	int sx;
	int sy;
};

struct s_raylight{
	//Diffuse
	t_vector 	P;
	t_vector 	N;
	t_vector 	L;
	float 		n_dot_l;
	//Specular
	t_vector 	R;
	t_vector 	V;
	t_vector	aux;
	float		s;
	float		r_dot_v;
	//Intensity
	float 		i[3];
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
	t_object	*closest_obj;
	float		closest_t;
	int	 	 	local_color;
	int			reflected_color;
	int			final_color;
};

struct s_ray_thread
{
	bool running;
	bool work;
	pthread_t	*thread;
	pthread_mutex_t th_mut;
    t_raytracer rt;
	int	index;
	int	x_i;
	int	x_f;
	int	delta;
	int	*color;
	int check_paint;
};


# endif