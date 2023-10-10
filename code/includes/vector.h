/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:53:57 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 19:28:00 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


# include "../minilibx/mlx.h"
# include "X11/X.h"
# include "X11/keysym.h"

typedef struct s_data		t_data;
typedef struct s_vars		t_vars;
typedef struct s_object		t_object;
typedef struct s_plane		t_plane;
typedef struct s_sphere		t_sphere;
typedef struct s_cylinder	t_cylinder;
typedef struct s_cone		t_cone;
typedef struct s_camera		t_camera;
typedef enum e_type			t_type;
typedef struct s_light		t_light;
typedef struct s_scene		t_scene;
typedef enum e_rotation		t_rotation;
typedef t_object*			(*t_new_objects)();
typedef struct s_vector		t_vector;

struct s_vector
{
	float	x;
	float	y;
	float	z;
};

//Vector
t_vector	vector_subtract(t_vector vec, t_vector vec2);
t_vector	vector_add(t_vector vec, t_vector vec2);
t_vector	vector_multiply(t_vector vec, t_vector vec2);
t_vector	vector_divide(t_vector vec, t_vector vec2);	
float		dot(t_vector va, t_vector vb);
float		module(t_vector vec);
t_vector	vector_mult_const(t_vector vec, float value);
t_vector	vector_div_const(t_vector vec, float value);
#endif