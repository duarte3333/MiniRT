#include "includes/minirt.h"

static t_object *mouse_trace_ray(t_vars *vars ,t_raytracer *rt)
{
	float 	 dotN_R;
	float	 r;
	t_raytracer newRT;

	newRT = *(rt);
	newRT.O = rt->O;
	newRT.D = rt->D;
	newRT.closest_obj = closest_intersection(&newRT, 0.001f, INT_MAX);
    if (!(newRT.closest_obj))
       return NULL;
	light_prepare(&newRT, newRT.closest_obj);
	newRT.local_color = color_multiply(newRT.closest_obj->color, compute_light(&newRT));
	return (newRT.closest_obj);
}

static int ft_mouse_scroll(int button, int x, int y, t_scene *scene)
{
	if (scene->select)
		scene->select->vector.z +=  ((button == 5) - (button == 4)) * 0.05;
	return 0;
}

int	ft_close(t_vars *vars)
{
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	//mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

int	ft_key(int keycode)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(vars()->mlx, vars()->win);
		free(vars()->mlx);
		exit(0);
	}
	if (vars()->scene->select)
	{
		vars()->scene->select->vector.y +=  ((keycode == XK_Up) - (keycode == XK_Down)) * 0.05;
		vars()->scene->select->vector.x +=  ((keycode == XK_Right) - (keycode == XK_Left)) * 0.05;
		vars()->scene->select->vector.z +=  ((keycode == 'z') - (keycode == 'x')) * 0.05;
		//printf("y: %f, x: %f z: %f\n", vars->select->vector.y, vars->select->vector.x, vars->select->vector.z);
	}
	return (0);
}

int ft_mouse_down(int button, int x, int y)
{
	t_raytracer rt;
	x -= WIDTH_2;
	y -= HEIGHT_2;

	if ((button == 5) || (button == 4))
		return (ft_mouse_scroll(button, x, y, vars()->scene));
	if (vars()->scene->select && button == 3)
	{
		vars()->scene->select->vector.x = ((float)(x))*(1.5f/WIDTH_2);
		vars()->scene->select->vector.y = -((float)(y))*(1.5f/HEIGHT_2);
		return (0);
	}
	rt.O = vector(0, 0, 0);	
	canvas_to_viewport(&rt, x, y); //get D
	vars()->scene->select = mouse_trace_ray(vars, &rt); //get color
	return 0;
}
