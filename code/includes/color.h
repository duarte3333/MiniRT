/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:06:37 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 16:06:45 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color	t_color;

struct	s_color {
	int	r;
	int	g;
	int	b;
};

t_color	color(int r, int g, int b);
t_color	color_texture(t_color color, float texture);
int		create_trgb(int t, t_color color);
int		get_rgb(int r, int g, int b);
int		multiply_color(int color, float brightness);
int		color_multiply(t_color color, float *brightness, float texture);
int		color_mult_int(int color, float brightness);
int		color_sum(t_color color, float brightness);
int		color_sum_int(int color, int color2);

#endif