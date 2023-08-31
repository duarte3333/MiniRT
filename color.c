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

t_color int_to_color(int color)
{
	t_color new;

	new.r = (color >> 16 & 255);
	new.g = (color >> 8 & 255);
	new.b = (color & 255);
	return new;

}
int	color_multiply(t_color color, float brightness)
{
	int fcolor;
	
	fcolor = get_rgb(color.r, color.g, color.b);
	color.r = (fcolor >> 16 & 255) * brightness;
	color.g = (fcolor >> 8 & 255) * brightness;
	color.b = (fcolor & 255) * brightness;
	return (get_rgb(color.r , color.g, color.b));
}

t_color compute_color_contribution(t_color color1, t_color color2)
{
	t_color new_color;
	float c1[3];
	float c2[3];

	
	c1[0] = (float)color1.r / 255;
	c1[1] = (float)color1.g / 255;
	c1[2] = (float)color1.b / 255;
	c2[0] = (float)color2.r / 255;
	c2[1] = (float)color2.g / 255;
	c2[2] = (float)color2.b / 255;
	c1[0] = c1[0] * c2[0];
	c1[1] = c1[1] * c2[1];
	c1[2] = c1[2] * c2[2];

	new_color.r = c1[0] * 255;
	new_color.g = c1[1] * 255;
	new_color.b = c1[2] * 255;

	return new_color;

}

int	color_mult_int(int color, float brightness)
{
	int r;
	int g;
	int b;
	
	r = (color >> 16 & 255) * brightness;
	g = (color >> 8 & 255) * brightness;
	b = (color & 255) * brightness;
	return (get_rgb(r , g, b));
}

int color_sum_int(int color1, int color2) {
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;

    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;

    int r_sum = r1 + r2;
    int g_sum = g1 + g2;
    int b_sum = b1 + b2;

    // Certifique-se de que os valores estejam no intervalo válido [0, 255]
    r_sum = (r_sum > 255) ? 255 : (r_sum < 0) ? 0 : r_sum;
    g_sum = (g_sum > 255) ? 255 : (g_sum < 0) ? 0 : g_sum;
    b_sum = (b_sum > 255) ? 255 : (b_sum < 0) ? 0 : b_sum;

    return (r_sum << 16) | (g_sum << 8) | b_sum;
}
// int	color_sum_int(int color, float brightness)
// {
// 	int r;
// 	int g;
// 	int b;
	
// 	r = (color >> 16 & 255) + brightness;
// 	g = (color >> 8 & 255) + brightness;
// 	b = (color & 255) + brightness;
// 	return (get_rgb(r , g, b));
// }


int	color_sum(t_color color, float brightness)
{
	int fcolor;
	
	fcolor = get_rgb(color.r, color.g, color.b);
	color.r = (fcolor >> 16 & 255) + brightness;
	color.g = (fcolor >> 8 & 255) + brightness;
	color.b = (fcolor & 255) + brightness;
	return (get_rgb(color.r , color.g, color.b));
}