/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:41:20 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 16:22:11 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	color(int r, int g, int b)
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
