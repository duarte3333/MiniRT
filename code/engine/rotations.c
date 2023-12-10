/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:52:46 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/09 20:52:47 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	rotation_x(t_vector *vec, float theta)
{
	float	temp_z;
	float	temp_y;

	temp_z = vec->z;
	temp_y = vec->y;
	vec->y = temp_y * cos(theta) + temp_z * sin(theta);
	vec->z = -temp_y * sin(theta) + temp_z * cos(theta);
}

void	rotation_y(t_vector *vec, float phi)
{
	float	temp_x;
	float	temp_z;

	temp_x = vec->x;
	temp_z = vec->z;
	vec->x = temp_x * cos(phi) + temp_z * sin(phi);
	vec->z = -temp_x * sin(phi) + temp_z * cos(phi);
}

void	rotation_z(t_vector *vec, float qsi)
{
	float	temp_x;
	float	temp_y;

	temp_x = vec->x;
	temp_y = vec->y;
	vec->x = temp_x * cos(qsi) - temp_y * sin(qsi);
	vec->y = temp_x * sin(qsi) + temp_y * cos(qsi);
}
