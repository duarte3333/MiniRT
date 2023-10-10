/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:42:49 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 17:58:45 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	wait_threads(void)
{
	while (1)
	{
		pthread_mutex_lock(&vars()->mut);
		if (vars()->count != vars()->n_threads)
		{
			vars()->count = 0;
			pthread_mutex_unlock(&vars()->mut);
			break ;
		}
		pthread_mutex_unlock(&vars()->mut);
	}
}

static void	paint_chunk(t_ray_thread *thread)
{
	t_chunk	s;

	s.sx = 0;
	s.x = thread->x_i - 1;
	pthread_mutex_lock(&thread->th_mut);
	while (++s.x < thread->x_f)
	{
		s.sy = 0;
		s.y = -HEIGHT_2 - 1;
		while (++s.y < HEIGHT_2)
			my_mlx_pixel_put(&vars()->img, s.x + WIDTH_2, \
				s.y + HEIGHT_2, thread->color[(s.sy++) * thread->delta + s.sx]);
		s.sx++;
	}
	pthread_mutex_unlock(&thread->th_mut);
}

void	paint(void)
{
	int	n;
	int	i;

	if (!vars()->work_all)
		return ;
	i = -1;
	while (++i < vars()->n_threads)
	{
		pthread_mutex_lock(&vars()->threads[i].th_mut);
		vars()->threads[i].work = true;
		pthread_mutex_unlock(&vars()->threads[i].th_mut);
	}
	wait_threads();
	n = -1;
	while (++n < vars()->n_threads)
		paint_chunk(&vars()->threads[n]);
	mlx_put_image_to_window(vars()->mlx, vars()->win, vars()->img.img, 0, 0);
	if (vars()->menu == 0)
		ft_menu();
	vars()->work_all = false;
}
