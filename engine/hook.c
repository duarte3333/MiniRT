/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:39:30 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/08 17:09:44 by duarte33         ###   ########.fr       */
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
	if (keycode == XK_c || keycode == XK_v)
	 	vars()->scene->camera->qsi += ((keycode == XK_c) - (keycode == XK_v)) * 0.01;
}


static void translate(int keycode)
{
	vars()->scene->select->vector.y +=  ((keycode == XK_Up) - (keycode == XK_Down)) * 0.05;
	vars()->scene->select->vector.x +=  ((keycode == XK_Right) - (keycode == XK_Left)) * 0.05;
	vars()->scene->select->vector.z +=  ((keycode == XK_z) - (keycode == XK_x)) * 0.05;	
}

/* This function after update the angles, update the direction */
static void rotate(int keycode)
{
	vars()->scene->select->theta +=  ((keycode == XK_i) - (keycode == XK_k)) * 0.01;
	vars()->scene->select->phi +=  ((keycode == XK_j) - (keycode == XK_l)) * 0.01;
	vars()->scene->select->qsi +=  ((keycode == XK_u) - (keycode == XK_o)) * 0.01;
	vars()->scene->select->rotate(vars()->scene->select);
}

static void translate_light(int keycode)
{
	vars()->scene->select_light->vector.y +=  ((keycode == XK_Up) - (keycode == XK_Down)) * 0.1;
	vars()->scene->select_light->vector.x +=  ((keycode == XK_Right) - (keycode == XK_Left)) * 0.1;
	vars()->scene->select_light->vector.z +=  ((keycode == XK_z) - (keycode == XK_x)) * 0.1;	
}


// static void rotate_light(int keycode)
// {
// 	vars()->scene->select_light->theta +=  ((keycode == XK_i) - (keycode == XK_k)) * 0.01;
// 	vars()->scene->select_light->phi +=  ((keycode == XK_j) - (keycode == XK_l)) * 0.01;
// 	vars()->scene->select_light->qsi +=  ((keycode == XK_u) - (keycode == XK_o)) * 0.01;
// 	vars()->scene->select_light->rotate(vars()->scene->select_light);
// }

int	ft_key(int keycode)
{	
	int menu;
	//threads_update();
	if (keycode == XK_Escape)
		ft_close(vars());
	menu = vars()->menu;
	if (keycode == XK_m && menu == 1)
		vars()->menu = 0;
	if (keycode == XK_m && menu == 0)
		vars()->menu = 1;
	// if (keycode == XK_r)
	// 	vars()->scene->select_light = vars()->scene->light;
	if (keycode == XK_t)
	{
		if (!vars()->scene->select_light || !vars()->scene->select_light->next)
			vars()->scene->select_light = vars()->scene->light;
		else if (vars()->scene->select_light->next)
			vars()->scene->select_light = vars()->scene->select_light->next;
	}
	if (!vars()->scene->select && vars()->scene->select_light)
		translate_light(keycode);
	
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


