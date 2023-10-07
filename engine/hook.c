/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:39:30 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/07 22:05:36 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void camera_move(int keycode)
{
	if (keycode == XK_w || keycode == XK_s)
		vars()->scene->camera->vector.z += ((keycode == XK_w) - (keycode == XK_s))*0.05;
	if (keycode == XK_a || keycode == XK_d)
		vars()->scene->camera->vector.x += ((keycode == XK_d) - (keycode == XK_a))*0.05;
	if (keycode == XK_1 || keycode == XK_2)
		vars()->scene->camera->vector.y += ((keycode == XK_1) - (keycode == XK_2)) * 0.05;
	if (keycode == XK_q || keycode == XK_e)
	 	vars()->scene->camera->phi += ((keycode == XK_e) - (keycode == XK_q)) * 0.01;
	if (keycode == XK_3 || keycode == XK_4)
	 	vars()->scene->camera->theta += ((keycode == XK_3) - (keycode == XK_4)) * 0.01;
}

// static void lights_move(int keycode)
// {
// 	if (keycode == XK_w || keycode == XK_s)
// 		vars()->scene->camera->vector.z += ((keycode == XK_w) - (keycode == XK_s))*0.05;
// 	if (keycode == XK_a || keycode == XK_d)
// 		vars()->scene->camera->vector.x += ((keycode == XK_d) - (keycode == XK_a))*0.05;
// 	if (keycode == XK_1 || keycode == XK_2)
// 		vars()->scene->camera->vector.y += ((keycode == XK_1) - (keycode == XK_2)) * 0.05;
// 	if (keycode == XK_q || keycode == XK_e)
// 	 	vars()->scene->camera->phi += ((keycode == XK_e) - (keycode == XK_q)) * 0.01;
// 	if (keycode == XK_3 || keycode == XK_4)
// 	 	vars()->scene->camera->theta += ((keycode == XK_3) - (keycode == XK_4)) * 0.01;
// }

static void translate(int keycode)
{
	vars()->scene->select->vector.y +=  ((keycode == XK_Up) - (keycode == XK_Down)) * 0.05;
	vars()->scene->select->vector.x +=  ((keycode == XK_Right) - (keycode == XK_Left)) * 0.05;
	vars()->scene->select->vector.z +=  ((keycode == 'z') - (keycode == 'x')) * 0.05;	
}

static void rotate(int keycode)
{
	vars()->scene->select->theta +=  ((keycode == 'i') - (keycode == 'k')) * 0.001;
	vars()->scene->select->phi +=  ((keycode == 'j') - (keycode == 'l')) * 0.001;
	vars()->scene->select->qsi +=  ((keycode == 'u') - (keycode == 'o')) * 0.001;
	vars()->scene->select->rotate(vars()->scene->select);
}

int	ft_key(int keycode)
{	

	//threads_update();
	if (keycode == XK_Escape)
	{
		ft_close(vars());
	}
	if (vars()->scene->select)
	{
		translate(keycode);
		if (vars()->scene->select->type != SPHERE)
			rotate(keycode);
	}
	camera_move(keycode);
	if (keycode == XK_8 && vars()->scene->next)
		vars()->scene = vars()->scene->next;
	if (keycode == XK_9 && vars()->scene->prev)
		vars()->scene = vars()->scene->prev;
	//threads_update();
	return (0);
}


