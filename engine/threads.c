#include "../includes/minirt.h"

void    *routine(void *arg)
{
    t_ray_thread *thread;
    bool run;
    bool status;

    thread = (t_ray_thread*)arg;
    thread->running = true;

    while (1)
    {
        usleep(500);
        pthread_mutex_lock(&thread->th_mut);
        run = thread->running;
        status = thread->work;
        pthread_mutex_unlock(&thread->th_mut);
        if (!run)
            break ;
        if (!status)
        {
            usleep(500);
            continue;
        }
        raytracer_threads(thread);
        pthread_mutex_lock(&vars()->mut);
        vars()->count++;
        pthread_mutex_unlock(&vars()->mut);
        pthread_mutex_lock(&thread->th_mut);
        thread->work = false;
        pthread_mutex_unlock(&thread->th_mut);
    }
    return (NULL);
}


static void create_chunks(int i)
{
   int rest;

   rest =  (int)WIDTH % (vars()->n_threads);
   thread[i].index = i;
   thread[i].work  = true;
   if ((i == vars()->n_threads - 1) && rest != 0)
   {
        vars()->threads[i].x_i = vars()->threads[i - 1].x_f;
        vars()->threads[i].delta = (int)WIDTH - (vars()->n_threads - 1)* \
             ((int)WIDTH/vars()->n_threads);
        vars()->threads[i].x_f =  vars()->threads[i].delta + vars()->threads[i].x_i;
        vars()->threads[i].color = ft_calloc(sizeof(int), (int)(HEIGHT) * vars()->threads[i].delta);
   }
   else
   {
        vars()->threads[i].delta = (int)(WIDTH / vars()->n_threads);
        vars()->threads[i].x_i = -WIDTH_2 + i * vars()->threads[i].delta;
        if (i < vars()->n_threads)
            vars()->threads[i].x_f = -WIDTH_2 + (i+1) * vars()->threads[i].delta;
        vars()->threads[i].color = ft_calloc(sizeof(int), (int)(HEIGHT) * (int)WIDTH / vars()->n_threads);
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
        free(vars->threads[i].color);
		pthread_mutex_destroy(&vars->threads[i].th_mut);
	}
    free(vars->threads);
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
        create_chunks(i);
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