/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:45:21 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 21:23:27 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

typedef struct s_values			t_values;
typedef struct s_raytracer		t_raytracer;
typedef struct s_raylight		t_raylight;
typedef struct s_ray_thread		t_ray_thread;
typedef struct s_chunk			t_chunk;

struct s_values
{
	float	t1;
	float	t2;
};

struct s_chunk
{
	int	x;
	int	y;
	int	sx;
	int	sy;
};

struct s_raylight{
	t_vector	p;
	t_vector	n;
	t_vector	l;
	float		n_dot_l;
	t_vector	r;
	t_vector	v;
	t_vector	aux;
	float		s;
	float		r_dot_v;
	float		i[3];
};

struct s_raytracer{
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_vector	co;
	t_vector	o;
	t_vector	d;
	t_values	t;
	t_raylight	rl;
	t_object	*closest_obj;
	float		closest_t;
	int			local_color;
	int			reflected_color;
	int			final_color;
};

struct s_ray_thread
{
	bool			running;
	bool			work;
	pthread_t		*thread;
	pthread_mutex_t	th_mut;
	t_raytracer		rt;
	int				index;
	int				x_i;
	int				x_f;
	int				delta;
	int				*color;
	int				check_paint;
};

#	endif