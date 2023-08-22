/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:29:15 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/08/22 17:13:49 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include "minilibx/mlx.h"
# include "X11/X.h"
# include "X11/keysym.h"
# include "limits.h"
# include "raytracer.h"
# include <sys/time.h>

# define WHITE 0xFFFFFF
# define HEIGHT 1000.0f
# define WIDTH 1000.0f
# define HEIGHT_2 500.0f
# define WIDTH_2 500.0f



typedef enum 	e_shape  t_shape;
typedef struct  s_data	 t_data;
typedef struct	s_vars	 t_vars;
typedef struct 	s_object t_object;
typedef struct 	s_plane  t_plane;
typedef struct 	s_sphere t_sphere;

typedef enum 	e_type t_type;
typedef struct 	s_light t_light;



enum e_shape{
	PLANE,
	SPHERE,
	CYLINDER
};

enum e_type{
	AMBIENT,
	DIRECTION
};

struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	 img;
	t_object *objects[6];
	t_light  *lights[3];
	t_object *select;
};

struct	s_light {
	t_type type;
	float  intensity;
	t_vector position;
};

struct 	s_object {
	t_vector vector;
	t_shape shape;
	unsigned int	color;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);	
};

struct 	s_plane {
	t_vector direction;
	t_shape shape;
	unsigned int	color;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	//
	t_vector vector;
};

struct 	s_sphere {
	t_vector vector;
	t_shape shape;
	unsigned int	color;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);	
	//
	float diameter;
};

//Hook's
int			ft_key(int keycode, t_vars *vars);
int 		ft_mouse_scroll(int button, int x, int y, t_vars *vars);
int 		ft_mouse_up(int button, int x, int y, t_vars *vars);
int 		ft_mouse_down(int button, int x, int y, t_vars *vars);

//Draw
void		my_mlx_pixel_put(t_data *img, int x, int y, int color);
int			ft_render(t_vars *vars);
void* 		new_object(int size);
t_object*	new_plane(t_vector coord, t_vector v, int color);
t_object* 	new_sphere(t_vector coord, float diameter, int color);
t_vector 	vector(float x, float y, float z);
t_vector 	vector_operation(t_vector vec, t_vector center);
float 		dot(t_vector va, t_vector vb);


void 		raytracer(t_vars *vars);
void 		canvas_to_viewport(t_raytracer *rt, float x, float y);
t_object 	*trace_ray(t_vars* vars ,t_raytracer* rt, float t_min, float t_max);

//Light
t_light *new_light(float intensity, t_vector pos)

#endif
