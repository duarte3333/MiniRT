#ifndef COLOR_H
# define COLOR_H

typedef struct 	s_color t_color;

struct  s_color {
	int r;
	int g;
	int b;
};

t_color color(int r, int g, int b);
int		create_trgb(int t, t_color color);
int		get_rgb(int r, int g, int b);
t_color int_to_rgb(int crr_color);
t_color ft_multiply_color(t_color color, float i);
int	multiply_color(int color, float brightness);



#endif