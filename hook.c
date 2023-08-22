#include "minirt.h"

int	ft_key(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->select)
	{
		vars->select->vector.y +=  ((keycode == XK_Up) - (keycode == XK_Down)) * 0.05;
		vars->select->vector.x +=  ((keycode == XK_Right) - (keycode == XK_Left)) * 0.05;
		vars->select->vector.z +=  ((keycode == 'z') - (keycode == 'x')) * 0.05;
		printf("y: %f, x: %f z: %f\n", vars->select->vector.y, vars->select->vector.x, vars->select->vector.z);
	}
	//mlx_destroy_display(vars->mlx);
	//free(vars->mlx);
	//exit(0);
	return (0);
}

int ft_mouse_down(int button, int x, int y, t_vars *vars)
{
	t_raytracer rt;
	printf("CLICK x: %d, y: %d\n", x, y);
	x -= WIDTH_2;
	y -= HEIGHT_2;

	if ((button == 5) || (button == 4))
		return (ft_mouse_scroll(button, x, y, vars));
	if (vars->select && button == 3)
	{
		//vars->select->vector.x = ((float)x)*(1.0f/WIDTH);
		//vars->select->vector.y = -((float)y)*(1.0f/HEIGHT);
		printf("x: %d, y: %d\n", x, y);
		printf("antes: y: %f, x: %f\n", vars->select->vector.y, vars->select->vector.x);
		vars->select->vector.x = ((float)(x))*(1.5f/WIDTH_2);
		vars->select->vector.y = -((float)(y))*(1.5f/HEIGHT_2);
		printf("depois y: %f, x: %f\n",((float)(x))*(1.0f/WIDTH),-((float)(y))*(1.0f/HEIGHT));

		return (0);
	}
	rt.O = vector(0, 0, 0);	
	canvas_to_viewport(&rt, x, y); //get D
	vars->select = trace_ray(vars, &rt, 1.0f, INT_MAX); //get color
	return 0;
}

int ft_mouse_scroll(int button, int x, int y, t_vars *vars)
{
	if (vars->select)
		vars->select->vector.z +=  ((button == 5) - (button == 4)) * 0.05;
	return 0;
}

/* Rato lado direito */
int ft_mouse_up(int button, int x, int y, t_vars *vars)
{	
	// x -= 250;
	// y -= 250;
	// if (vars->select)
	// {
	// 	vars->select->vector.x = ((float)x)*(1.0f/500.0f);
	// 	vars->select->vector.y = -((float)y)*(1.0f/500.0f);
	// 	printf("x: %d, y:%d\n", x, y);
	// }
	return 0;
}

// int	ft_close(int keycode, t_vars *vars)
// {
// 	mlx_destroy_window(vars->mlx, vars->win);
// 	//mlx_destroy_display(vars->mlx);
// 	//free(vars->mlx);
// 	exit(0);
// 	return (0);
// }