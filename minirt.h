/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:29:15 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/08/21 16:35:24 by duarte33         ###   ########.fr       */
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

typedef enum 	e_shape  t_shape;
typedef struct  s_data	 t_data;
typedef struct	s_vars	 t_vars;
typedef struct 	s_object t_object;
typedef struct 	s_plane  t_plane;
typedef struct 	s_sphere t_sphere;



enum e_shape{
	PLANE,
	SPHERE,
	CYLINDER
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
	t_object *objects[4];
};

struct 	s_object {
	t_vector vector;
	t_shape shape;
	unsigned int	color;
	void (*render)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	
};

struct 	s_plane {
	t_vector vector;
	t_shape shape;
	unsigned int	color;
	void (*render)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	//
	t_vector direction;
};

struct 	s_sphere {
	t_vector vector;
	t_shape shape;
	unsigned int	color;
	void (*render)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	//
	float diameter;
};

//Hook's
int			ft_close(int keycode, t_vars *vars);

//Draw
void		my_mlx_pixel_put(t_data *img, int x, int y, int color);
int			ft_render(t_vars *vars);
void* 		new_object(int size);
t_object*	new_plane(t_vector coord, t_vector v, int color);
t_object* 	new_sphere(t_vector coord, float diameter, int color);
t_vector 	vector(float x, float y, float z);
t_vector 	vector_operation(t_vector vec, t_vector center);
float 		dot(t_vector va, t_vector vb);


void raytracer(t_vars *vars);


#endif
