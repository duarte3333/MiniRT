/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:39:30 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/09 16:31:00 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
extern int last_render;
int get_now();

void threads_update()
{
	int i;

	i = -1;
	pthread_mutex_lock(&vars()->mut);
	vars()->count = 0;
	pthread_mutex_unlock(&vars()->mut);
		
	while (++i < vars()->n_threads)
    {
	    pthread_mutex_lock(&vars()->threads[i].th_mut);
	    vars()->threads[i].work = true;
	    pthread_mutex_unlock(&vars()->threads[i].th_mut);
    }
	
	last_render = get_now();
}

int	ft_close(t_vars *vars)
{

	ft_join_threads(vars);
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	if (vars->win)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	free_objects(vars->scene);
	exit(0);
}
