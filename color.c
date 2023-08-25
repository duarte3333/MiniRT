#include "includes/minirt.h"

t_color color(int r, int g, int b)
{
	return ((t_color){r, g, b});
}

int	create_trgb(int t, t_color color)
{
	(void)t;
	return (color.r << 16 | color.g << 8 | color.b);
}

int	get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/* Recebe o inteiro e depois da right shift para
levar os ter 8 bits do r, g ou b para o mais a 
direita possivel. O &255 assegura que nao existe 
overflow de cores.*/
int	color_multiply(t_color color, float brightness)
{
	int fcolor;
	
	fcolor = get_rgb(color.r, color.g, color.b);
	color.r = (fcolor >> 16 & 255) * brightness;
	color.g = (fcolor >> 8 & 255) * brightness;
	color.b = (fcolor & 255) * brightness;
	return (get_rgb(color.r , color.g, color.b));
}