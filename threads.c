#include "includes/minirt.h"

void    raytracer_threads(t_ray_thread *thread)
{
	t_chunk     s;
    t_raytracer rt;

    pthread_mutex_lock(&thread->th_mut);
    bzero(&rt, sizeof(t_raytracer));
    rt.O = vector(0, 0, 0);
    s.sx = 0;
    s.x = thread->x_i - 1;
	while (++s.x < thread->x_f)
	{
        s.sy = 0;
        s.y = -HEIGHT_2 - 1;
		while (++s.y < HEIGHT_2)
		{
            rt.closest_obj = NULL;
			canvas_to_viewport(&rt, s.x, s.y); //get D
			thread->color[s.sy++ * thread->delta + s.sx] = \
                new_trace_ray(NULL, rt.O, rt.D, vars()->scene, &rt, 1);
		}
        usleep(50);
        s.sx++;
	}
    pthread_mutex_unlock(&thread->th_mut);
}

void    *routine(void *arg)
{
    t_ray_thread *thread;

    thread = (t_ray_thread*)arg;
    while (1)
    {  
        raytracer_threads(thread);
        pthread_mutex_lock(&vars()->mut);
        vars()->count++;
        pthread_mutex_unlock(&vars()->mut);
        //usleep(100);
    }
    //free(thread->color);
    if (pthread_join(thread->thread, NULL))
    {
        printf("Error joining threads\n");
        return (-1);
    }
    return (NULL);
}

void create_chunks(t_ray_thread *thread, int i)
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
       thread[i].color = calloc(sizeof(int), (int)(HEIGHT) * thread[i].delta);
   }
   else
   {
        thread[i].delta = (int)(WIDTH / vars()->n_threads);
        thread[i].x_i = -WIDTH_2 + i*thread[i].delta;
        if (i < vars()->n_threads)
            thread[i].x_f = -WIDTH_2 + (i+1)*thread[i].delta;
        thread[i].color = calloc(sizeof(int), (int)(HEIGHT) * (int)WIDTH / vars()->n_threads);
   }
}

int ft_init_threads()
{
    int i;
    t_ray_thread *threads;

    threads = calloc(sizeof(t_ray_thread), vars()->n_threads);
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