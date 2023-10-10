/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:42:30 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 17:17:00 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	dot(t_vector va, t_vector vb)
{
	return (va.x * vb.x + va.y * vb.y + va.z * vb.z);
}

float	module(t_vector vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vector	vector_mult_const(t_vector vec, float value)
{
	vec.x *= value;
	vec.y *= value;
	vec.z *= value;
	return (vec);
}

t_vector	vector_div_const(t_vector vec, float value)
{
	vec.x /= value;
	vec.y /= value;
	vec.z /= value;
	return (vec);
}
