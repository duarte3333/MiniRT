/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:41:20 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/05 14:11:01 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	if (r > 255)
		r = 255;
	if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	if (b < 0)
		b = 0;
	return (r << 16 | g << 8 | b);

}

/* Recebe o inteiro e depois da right shift para
levar os ter 8 bits do r, g ou b para o mais a 
direita possivel. O &255 assegura que nao existe 
overflow de cores.*/

float random_number(unsigned int* seed)
{
	*seed = *seed * 747796405 + 2891336453;
    unsigned long result = ((*seed >> ((*seed >> 28) + 4)) ^ *seed) * 277803737;
    return result / (float)UINT_MAX;
}

float generate()
{
	struct timeval tv;
	
	gettimeofday(&tv,  NULL);
	float nb1 = random_number(&tv.tv_usec) * 70.0f - 30.f;
	float nb2 = random_number(&tv.tv_usec) * 70.0f - 30.f;
	// gettimeofday(&tv,  NULL);
	// srand(tv.tv_usec);
	// float nb1 = rand() % 100;
	// float nb2 = rand() % 100;
	return nb1 - nb2;
}

int	color_multiply(t_color color, float *brightness)
{
	int fcolor;
	//float a = (float)generate();
	fcolor = get_rgb(color.r + (float)generate()*0.7,  color.g + (float)generate()*0.5, color.b + (float)generate()*0.5);
	//fcolor = get_rgb(color.r ,  color.g , color.b );
	color.r = (fcolor >> 16) * brightness[0];
	color.g = (fcolor >> 8 & 255) * brightness[1];
	color.b = (fcolor & 255) * brightness[2];
	//printf("red %d, green %d, blue %d\n",color.r, color.g, color.b);
	return (get_rgb(color.r , color.g, color.b));
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

int	color_sum(t_color color, float brightness)
{
	int fcolor;
	
	fcolor = get_rgb(color.r, color.g, color.b);
	color.r = (fcolor >> 16 & 255) + brightness;
	color.g = (fcolor >> 8 & 255) + brightness;
	color.b = (fcolor & 255) + brightness;
	return (get_rgb(color.r , color.g, color.b));
}