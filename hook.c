#include "minirt.h"

int	ft_close(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	//mlx_destroy_display(vars->mlx);
	//free(vars->mlx);
	exit(0);
	return (0);
}