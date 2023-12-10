/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:43:22 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 21:17:20 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	*compute_light(t_raytracer *rt)
{
	int			i;
	t_object	*tmp;

	rt->rl.i[0] = 0.0f;
	rt->rl.i[1] = 0.0f;
	rt->rl.i[2] = 0.0f;
	tmp = vars()->scene->light;
	while (tmp)
	{
		if (tmp->type == AMBIENT)
			ambient_light(rt, tmp);
		else
		{
			if (point_and_directional_light(rt, &tmp))
				continue ;
		}
		tmp = tmp->next;
	}
	i = -1;
	while (++i < 3)
	{
		if (rt->rl.i[i] > 0.99f)
			rt->rl.i[i] = 1;
	}
	return (rt->rl.i);
}
