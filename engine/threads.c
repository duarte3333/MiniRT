#include "../includes/minirt.h"

void    *routine(void *arg)
{
    t_ray_thread *thread;
    bool n;

    thread = (t_ray_thread*)arg;
    thread->running = true;

    while (1)
    {
        usleep(20);
        pthread_mutex_lock(&thread->th_mut);
        n = thread->running;
        pthread_mutex_unlock(&thread->th_mut);
        if (!n)
            break ;
        pthread_mutex_unlock(&thread->th_mut);
        raytracer_threads(thread);
        pthread_mutex_lock(&vars()->mut);
        vars()->count++;
        pthread_mutex_unlock(&vars()->mut);
     
        /* if (pthread_join(thread->thread, NULL))
        {
            printf("Error joining threads\n");
            return (-1);
        } */
    }
    return (NULL);
}


static void create_chunks(t_ray_thread *thread, int i)
{
   int rest;

   rest =  (int)WIDTH % (vars()->n_threads);
   thread[i].index = i;
   if ((i == vars()->n_threads - 1) && rest != 0)
   {
       thread[i].x_i = thread[i - 1].x_f;
       thread[i].delta = (int)WIDTH - (vars()->n_threads - 1)* \
            ((int)WIDTH/vars()->n_threads);
       thread[i].x_f =  thread[i].delta + thread[i].x_i;
       thread[i].color = ft_calloc(sizeof(int), (int)(HEIGHT) * thread[i].delta);
   }
   else
   {
        thread[i].delta = (int)(WIDTH / vars()->n_threads);
        thread[i].x_i = -WIDTH_2 + i*thread[i].delta;
        if (i < vars()->n_threads)
            thread[i].x_f = -WIDTH_2 + (i+1)*thread[i].delta;
        thread[i].color = ft_calloc(sizeof(int), (int)(HEIGHT) * (int)WIDTH / vars()->n_threads);
   }
}

int	ft_join_threads(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->n_threads)
	{
        pthread_mutex_lock(&vars->threads[i].th_mut);
        vars->threads[i].running = false;
        pthread_mutex_unlock(&vars->threads[i].th_mut);
		if (pthread_join(vars->threads[i].thread, NULL))
		{
			printf("Error joining thread\n");
			return (-1);
		}
	}
	return (0);
}

int ft_init_threads()
{
    int i;
    t_ray_thread *threads;

    threads = ft_calloc(sizeof(t_ray_thread), vars()->n_threads);
    vars()->threads = threads;
    vars()->count = 0;
    pthread_mutex_init(&vars()->mut, NULL);
    i = -1;
    while (++i < vars()->n_threads)
    {
        create_chunks(threads, i);
        pthread_mutex_init(&vars()->threads[i].th_mut, NULL);
        if (pthread_create(&(vars()->threads[i].thread), NULL, \
        &routine, (void *)(&threads[i])) != 0)
        {
            printf("Error creating thread\n");
            return (-1);
        }
    }
    return (0);
}