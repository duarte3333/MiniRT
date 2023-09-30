/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:29:15 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/09/30 20:41:20 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "vector.h"
# include "color.h"
# include "get_next_line.h"

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define HEIGHT 1000.0f
# define WIDTH 1000.0f
# define HEIGHT_2 500.0f
# define WIDTH_2 500.0f

typedef struct  s_data		t_data;
typedef struct	s_vars		t_vars;
typedef struct 	s_object	t_object;
typedef struct 	s_plane 	t_plane;
typedef struct 	s_sphere	t_sphere;
typedef struct 	s_cylinder	t_cylinder;
typedef struct 	s_cone		t_cone;
typedef struct 	s_camera	t_camera;
typedef enum 	e_type		t_type;
typedef struct 	s_light		t_light;
typedef struct 	s_scene		t_scene;
typedef enum 	e_rotation	t_rotation;
typedef t_object*	(*new_objects)();

# include "raytracer.h"
# include "parse.h"


enum e_rotation{
	X_theta_1,
	X_theta_2,
	Y_phi_1,
	Y_phi_2,
	Z_qsi_1,
	Z_qsi_2,
};

enum e_type{
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	AMBIENT,
	POINT,
	DIRECTIONAL,
	CAMERA,
	ERROR,
	EMPTY_LINE,
	COMMENT,
};

struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct s_scene{
	t_camera *camera;
	t_object *object;
	t_object *light;
	t_object *select;
    t_object *end;
    t_object *end_light;
	t_scene  *next;
	t_scene  *prev;
	int	 	 f;
	bool 	 syntax;
};

struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	 img;
	t_scene	 *scene;
	t_scene  *last;
	char 	 *map_file;
	//
	int		n_threads;
	t_ray_thread *threads;
	pthread_mutex_t mut;
	int		**color;
	int		count;
	new_objects new_objects[15];
	
	//
	t_ray_thread *rt_var;
};

struct 	s_object {
	t_object	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*rotate)();
	void (*resize)(int ratio);
	float height;
	float  intensity;
};

struct 	s_camera {
	t_object	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*rotate)();
	void (*resize)(int ratio);
	float height;
	float  intensity;
	//
	t_vector direction;
	float theta;
	float phi;
	float qsi;
	float fov;
};

struct 	s_light {
	t_light	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*rotate)();
	void (*resize)(int ratio);
	float height;
	float  intensity;
	//
};

struct 	s_plane {
	t_object	*next;
	t_vector direction;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*rotate)();
	void (*resize)(int ratio);
	float height;
	float  intensity;
	//
	t_vector vector;
};

struct 	s_sphere {
	t_object	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*rotate)();
	void (*resize)(int ratio);
	float height;
	float  intensity;
	//
	float diameter;
};

struct 	s_cylinder{
	t_object	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*rotate)();
	void (*resize)(int ratio);	
	float height;
	float  intensity;
	//
	t_vector axis;
	float diameter;
	float theta;
	float phi;
	float qsi;

};

struct s_cone
{
	t_object	*next;
	t_vector vector;
	t_type type;
	t_color	color;
	int specular;
	float refletive;
	t_values (*intersect)();
	void (*move)(int x, int y);
	void (*resize)(int ratio);
	float height;
	float  intensity;
	//
	float theta;
	t_vector base;
	t_vector direction;
	t_vector tmp;
	float 	 m;
	float	 radius;
};

t_vars *vars();

//Syntax
int		test_syntax(char *str);

//Hook's
int			ft_key(int keycode);
int 		ft_mouse_up(int button, int x, int y);
int 		ft_mouse_down(int button, int x, int y);
int			ft_close(t_vars *vars);

//Objects
void* 		new_object(int size);
t_object*	new_plane(char *line);
t_object* 	new_sphere(char *line);
t_object* 	new_cylinder(char* line);
t_object* 	new_cone(char *line);
t_camera* 	new_camera(char *line);

//Camera
void	rotation_x(t_vector *vec, float theta);
void	rotation_y(t_vector *vec, float theta);
void	rotation_z(t_vector *vec, float theta);

//Ligh
t_object 	*new_light(char *line, t_type type);
float 		*compute_light(t_raytracer *rt);
void 		light_prepare(t_raytracer* rt, t_object *obj);

//Raytracer
void		my_mlx_pixel_put(t_data *img, int x, int y, int color);
void    	raytracer_threads(t_ray_thread *thread);
void		raytracer(t_scene *scene);
void 		canvas_to_viewport(t_raytracer *rt, float x, float y);
int 		new_trace_ray(t_object *last_obj, t_scene *scene ,t_raytracer rt, int recursion_depth);
t_object 	*closest_intersection(t_raytracer *rt);
bool 		inside(float t, float t_min, float t_max);
void 		choose_normal(t_raytracer* rt, t_object *obj);
t_vector 	reflected_ray(t_vector R, t_vector N);

//Threads
int 	ft_init_threads();
int		ft_join_threads(t_vars *vars);
void    *routine(void *arg);
//Paint
void 	paint();

//Aux
void	*ft_calloc(size_t nelem, size_t elsize);
char	*get_next_line(int fd);
int		ft_strlen(const char *str);
int		ft_isdigit(int i);
int		ft_isspace(char c);
double  ft_atof(char **line);
void    lst_add_back(t_scene *scene, t_type type, char *line);
void    light_add_back(t_scene *scene, t_type type, char *line);

//Free
void 	free_objects(t_scene *head);
void	free_array(char **arr);



#endif
