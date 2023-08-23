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

t_color int_to_rgb(int crr_color)
{
	t_color new;
	new.r  = (crr_color & 0x00ff0000) >> 16;
	new.g  = (crr_color & 0x0000ff00) >> 8;
	new.b  = (crr_color & 0x000000ff);
	if (new.r > 255)
		new.r = 255;
	if (new.g > 255)
		new.g = 255;
	if (new.b > 255)
		new.b = 255;
	return new;
}

t_color ft_multiply_color(t_color color, float i)
{
	t_color new;

	new.r *= i;
	new.g *= i;
	new.b *= i;
	if (new.r > 255)
		new.r = 255;
	if (new.g > 255)
		new.g = 255;
	if (new.b > 255)
		new.b = 255;
	return new;
}