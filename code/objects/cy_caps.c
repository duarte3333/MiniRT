/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_caps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:58:25 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/11 17:40:52 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/minirt.h"
/* Esta funcao recebe uma cilindro e um raio retorna 
os pixels onde intersetam.
Ray equation: P = O + t(V - O)*/

// float	distance(t_vector v1, t_vector v2)
// {
// 	return (sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) \
// 		+ pow(v1.z - v2.z, 2)));
// }

// int min(int a, int b) {
//     return (a < b) ? a : b;
// }

// static t_values check_height(t_raytracer *rt, t_cylinder *this, t_values t)
// {
// 	t_vector p;
// 	t_vector b;
// 	float	 k;

// 	p = vector_add(rt->o, vector_mult_const(rt->d, t.t1));
// 	k = dot(p, this->axis) - dot(this->vector, this->axis) / dot(this->axis, this->axis); 
// 	b = vector_add(this->vector, vector_mult_const(this->axis, k));
// 	if (abs(distance(b, this->vector)) > this->height / 2 )
// 		t.t1 = INT_MAX;
// 	p = vector_add(rt->o, vector_mult_const(rt->d, t.t2));
// 	k = dot(p, this->axis) - dot(this->vector, this->axis) / dot(this->axis, this->axis); 
// 	b = vector_add(this->vector, vector_mult_const(this->axis, k));
// 	if (abs(distance(b, this->vector)) > this->height/2)
// 		t.t2 = INT_MAX;
// 	return t;
// }

// static float check_width(t_plane *this, t_raytracer *rt, float t, float diameter)
// {
// 	t_vector p_cap = vector_add(rt->o, vector_mult_const(rt->d, t));
// 	t_vector v = vector_subtract(p_cap, this->vector);
// 	return (t * (module(v) <= (diameter / 2)));
// }

// static void rotate(t_cylinder *this)
// {	
//     rotation_x(&this->axis, this->theta);
// 	rotation_y(&this->axis, this->phi);
// 	rotation_z(&this->axis, this->qsi);

// 	rotation_x(&this->up_cap->direction.x, this->theta);
// 	rotation_y(&this->up_cap->direction.y, this->phi);
// 	rotation_z(&this->up_cap->direction.z, this->qsi);

// 	rotation_x(&this->down_cap->direction.x, this->theta);
// 	rotation_y(&this->down_cap->direction.y, this->phi);
// 	rotation_z(&this->down_cap->direction.z, this->qsi);

// 	this->theta = 0.0f;
// 	this->phi = 0.0f;
// 	this->qsi = 0.0f;
// 	this->up_cap->theta = 0.0f;
// 	this->up_cap->phi = 0.0f;
// 	this->up_cap->qsi = 0.0f;
// 	this->down_cap->theta = 0.0f;
// 	this->down_cap->phi = 0.0f;
// 	this->down_cap->qsi = 0.0f;
// }



// float choose_smallest_positive(float a, float b) {
//     if (a >= 0 && b >= 0) {
//         return (a < b) ? a : b;
//     } else if (a >= 0) {
//         return a;
//     } else if (b >= 0) {
//         return b;
//     } else {
//         return INT_MAX;  // No valid intersection
//     }
// }

// static t_values intersect_plane(t_raytracer *rt, t_plane *this)
// {
// 	t_values local;

// 	rt->c = -dot(this->direction, vector_subtract(rt->o, this->vector));
// 	rt->b = dot(rt->d, this->direction);
// 	if (rt->b < 0.0001f && rt->b > -0.0001f)
// 	{
// 		local.t1 = INT_MAX;
// 		local.t2 = INT_MAX;
// 		return (local);
// 	}
// 	local.t1 = rt->c / rt->b;
// 	local.t2 = INT_MAX;
// 	return (local);
// }

// static t_values intersect(t_raytracer *rt, t_cylinder *this)
// {
// 	t_values local;
// 	t_values local_up_cap;
// 	t_values local_down_cap;
// 	t_vector co;

// 	co = vector_subtract(rt->o, this->vector);
// 	rt->a = dot(rt->d, rt->d) * pow(module(this->axis), 2) - \
// 		pow(dot(rt->d, this->axis), 2);
// 	rt->b = 2.0f * dot(co, rt->d) * pow(module(this->axis), 2) - \
// 		2.0f * dot(rt->d, this->axis) * dot(co, this->axis);
// 	rt->c = (dot(co, co) - pow(this->diameter / 2, 2)) * pow(module(this->axis), 2) - \
// 		pow(dot(co, this->axis), 2);
// 	rt->discriminant = rt->b * rt->b - 4.0f * rt->a * rt->c;
// 	if (rt->discriminant < 0.001f) // No solution
// 	{
// 		local.t1 = INT_MAX;
// 		local.t2 = INT_MAX;
// 		return local;
// 	}
// 	local.t1 = ((-rt->b + sqrt(rt->discriminant)) / (2.0f * rt->a));
// 	local.t2 = ((-rt->b - sqrt(rt->discriminant)) / (2.0f * rt->a));
// 	local = check_height(rt, this, local);
// 	local_up_cap = this->up_cap->intersect(rt, this->up_cap);
// 	local_down_cap = this->down_cap->intersect(rt, this->down_cap);
// 	local_up_cap.t1 = check_width(this->up_cap, rt, local_up_cap.t1, this->diameter);
// 	local_down_cap.t1 = check_width(this->down_cap, rt, local_down_cap.t1, this->diameter);
// 	local.t1 = choose_smallest_positive(local.t1, local.t2);
// 	local.t1 = choose_smallest_positive(local.t1, local_up_cap.t1);
// 	local.t1 = choose_smallest_positive(local.t1, local_down_cap.t1);
// 	return local;
// }

// void	t_discover(float *t, t_cylinder *this)
// {
//     float quadratic[3];

//     quadratic[0] = dot(this->axis, this->axis);
//     quadratic[1] = 0;
//     quadratic[2] = -pow(this->diameter / 2, 2);
//     t[0] = (-quadratic[1] - sqrt(pow(quadratic[1], 2) - 4 * quadratic[0] * quadratic[2])) / (2 * quadratic[0]);
//     t[1] = (-quadratic[1] + sqrt(pow(quadratic[1], 2) - 4 * quadratic[0] * quadratic[2])) / (2 * quadratic[0]);
// }


// void create_upper_cap(t_cylinder *cylinder, float t)
// {
//     cylinder->up_cap = (t_object *)new_object(sizeof(t_plane));
//     cylinder->up_cap->intersect = intersect_plane;
//     cylinder->up_cap->rotate = rotate;
//     cylinder->up_cap->type = PLANE;

//     t_vector cap_position = vector_add(cylinder->vector, vector_mult_const(cylinder->axis, t));
//     cylinder->up_cap->vector = cap_position;
//     cylinder->up_cap->direction = cylinder->axis;
// }

// void create_lower_cap(t_cylinder *cylinder, float t)
// {
//     cylinder->down_cap = (t_object *)new_object(sizeof(t_plane));
//     cylinder->down_cap->intersect = intersect_plane;
//     cylinder->down_cap->rotate = rotate;
//     cylinder->down_cap->type = PLANE;

//     t_vector cap_position = vector_add(cylinder->vector, vector_mult_const(cylinder->axis, -t));
//     cylinder->down_cap->vector = cap_position;
//     cylinder->down_cap->direction = vector_mult_const(cylinder->axis, -1);  // Invert the axis for the lower cap
// }

// t_object* new_cylinder(char* line)
// {
// 	t_cylinder	*cylinder;
// 	float 		t[2];

// 	cylinder = new_object(sizeof(t_cylinder));
// 	cylinder->intersect = intersect;
// 	cylinder->rotate = rotate;
// 	cylinder->type = CYLINDER;
// 	cylinder->vector.x = ft_atof(&line);
// 	cylinder->vector.y = ft_atof(&line);
// 	cylinder->vector.z = ft_atof(&line);
// 	cylinder->axis.x = ft_atof(&line);
// 	cylinder->axis.y = ft_atof(&line);
// 	cylinder->axis.z = ft_atof(&line);
// 	cylinder->diameter = ft_atof(&line);
// 	cylinder->height = ft_atof(&line);
// 	cylinder->color.r = (int)ft_atof(&line);
//     cylinder->color.g = (int)ft_atof(&line);
//     cylinder->color.b = (int)ft_atof(&line);
// 	cylinder->specular = (int)ft_atof(&line);
// 	cylinder->refletive = ft_atof(&line);
// 	cylinder->intensity = ft_atof(&line);
// 	cylinder->checkerboard = (int)ft_atof(&line);
// 	cylinder->theta = 0.0f;
// 	cylinder->phi = 0.0f;
// 	cylinder->qsi = 0.0f;
// 	t_discover(&t, cylinder);
// 	create_lower_cap(cylinder, t[0]);
// 	create_upper_cap(cylinder, t[1]);
// 	return ((t_object *)cylinder);
// }

// 	if (vars()->scene->select->type == CYLINDER)
// {
// 	((t_cylinder *)vars()->scene->select)->up_cap->vector.y \
// 		+= ((keycode == XK_Up) - (keycode == XK_Down)) * 0.05;
// 	((t_cylinder *)vars()->scene->select)->up_cap->vector.x \
// 		+= ((keycode == XK_Right) - (keycode == XK_Left)) * 0.05;
// 	((t_cylinder *)vars()->scene->select)->up_cap->vector.z \
// 		+= ((keycode == XK_z) - (keycode == XK_x)) * 0.05;
// 	((t_cylinder *)vars()->scene->select)->down_cap->vector.y \
// 		+= ((keycode == XK_Up) - (keycode == XK_Down)) * 0.05;
// 	((t_cylinder *)vars()->scene->select)->down_cap->vector.x \
// 		+= ((keycode == XK_Right) - (keycode == XK_Left)) * 0.05;
// 	((t_cylinder *)vars()->scene->select)->down_cap->vector.z \
// 		+= ((keycode == XK_z) - (keycode == XK_x)) * 0.05;
// }