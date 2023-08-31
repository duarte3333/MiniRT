#include "includes/minirt.h"

bool inside(float t, float t_min, float t_max)
{
	if (t >= t_min && t < t_max )
		return true;
	return false;
}

void light_prepare(t_raytracer* rt, t_object *obj)
{
	float module_N;
	float_t closest_t;

	closest_t = rt->closest_t;
	rt->rl.P = vector_add(rt->O, vector_multiply(rt->D, vector(closest_t, closest_t, closest_t)));
	rt->rl.N = vector_subtract(rt->rl.P, obj->vector);
	module_N = module(rt->rl.N);
	rt->rl.N = vector_divide(rt->rl.N, vector(module_N, module_N, module_N));
	rt->rl.s = obj->specular;
	rt->rl.V = vector_multiply((rt->D), vector(-1, -1, -1));
}

t_object *closest_intersection(t_vars* vars ,t_raytracer *rt, float t_min, float t_max)
{
	t_object *obj;
	t_object *tmp;

	tmp = vars->object;
	obj = NULL;
	rt->closest_t = INT_MAX;
	while (tmp)
	{	
        rt->t = tmp->intersect(rt, tmp); //get t1 and t2
		if (inside(rt->t.t1, t_min, t_max) && rt->t.t1 < rt->closest_t ) 
		{
            rt->closest_t = rt->t.t1;
            obj = tmp;
        }
        if (inside(rt->t.t2, t_min, t_max) && rt->t.t2 < rt->closest_t) 
		{
            rt->closest_t = rt->t.t2;
            obj = tmp;
        }
		tmp = tmp->next;
    }
	return obj;
}

t_vector reflected_ray(t_vector R, t_vector N)
{
	double 	 dotN_R;
	t_vector Rfinal;

	dotN_R = 2.0f*dot(N, R);
	Rfinal = vector_subtract(vector_multiply(N, vector(dotN_R, dotN_R, dotN_R)), R);
	return Rfinal;
}

t_object *trace_ray(t_vector O, t_vector D, t_vars *vars ,t_raytracer *rt, float t_min, float t_max, int recursion_depth)
{
	float 	 dotN_R;
	float	 r;
	t_raytracer newRT;

	newRT = *(rt);
	newRT.O = O;
	newRT.D = D;
	newRT.closest_obj = closest_intersection(vars, &newRT, 0.001f, INT_MAX);
    if (!(newRT.closest_obj))
       return NULL;
	light_prepare(&newRT, newRT.closest_obj);
	newRT.local_color = color_multiply(newRT.closest_obj->color, compute_light(vars, &newRT));
	return (newRT.closest_obj);
}

// int new_trace_ray(t_vector O, t_vector D, t_vars *vars ,t_raytracer *rt, float t_min, float t_max, int recursion_depth, t_color contribution)
// {
// 	float	 r;
// 	t_object *obj;
// 	t_vector R;
// 	t_raytracer newRT = *(rt);
// 	int incomingLight;

// 	if (recursion_depth <= 0)
// 		return 0;
// 	newRT.O = O;
// 	newRT.D = D;
// 	obj = NULL;
// 	incomingLight = BLACK;
// 	obj = closest_intersection(vars, &newRT, t_min, t_max);
//     if (!(obj))
//     {
// 		t_color skyLight = compute_color_contribution(contribution, color(64,191,169));
// 		return  0;
// 	};
// 	r = obj->refletive;
// 	if (recursion_depth <= 0 || r <= 0.001f)
// 		return 0;
//     //printf("oi\n");
// 	light_prepare(&newRT, obj);
// 	//newRT.local_color = obj->color; //color_multiply(obj->color, compute_light(vars, &newRT));
// 	t_color new_contr = int_to_color(color_multiply(obj->color, r));
// 	//printf("[%d] obj color: %d,%d,%d; contribution: %d,%d,%d;\n", recursion_depth, obj->color.r, obj->color.g, obj->color.b,  new_contr.r, new_contr.g, new_contr.b);
// 	contribution = compute_color_contribution(contribution, new_contr);
// 	//printf("[%d] overall contr: %d,%d,%d;\n", recursion_depth, contribution.r, contribution.g, contribution.b);
// 	incomingLight = color_multiply(contribution, compute_light(vars,&newRT));
// 	if (incomingLight > 0xFFFFFF)
// 		incomingLight = WHITE;
// 	t_color n = int_to_color(incomingLight);
// 	//printf("[%d] rayLight: %d,%d,%d;\n", recursion_depth, n.r, n.g, n.b);
// 	newRT.rl.R = reflected_ray(vector_multiply(newRT.D, vector(-1, -1, -1)), newRT.rl.N);
// 	incomingLight += new_trace_ray(newRT.rl.P, newRT.rl.R, vars, \
// 		rt, 0.001f, INT_MAX, recursion_depth - 1, contribution);
// 	if (incomingLight > 0xFFFFFF)
// 		incomingLight = WHITE;
// 	n = int_to_color(incomingLight);
// 	//printf("[%d] nested light: %d,%d,%d;\n", recursion_depth, n.r, n.g, n.b);
// 	return incomingLight;//(color_mult_int(newRT.local_color, (1 - r)) + color_mult_int(newRT.reflected_color, r));
// }

int new_trace_ray(t_object *last_obj, t_vector O, t_vector D, t_vars *vars ,t_raytracer *rt, float t_min, float t_max, int recursion_depth)
{
	float	 r;
	t_object *obj;
	t_vector R;
	t_raytracer newRT = *(rt);

	obj = NULL;
	newRT.O = O;
	newRT.D = D;
	obj = closest_intersection(vars, &newRT, t_min, t_max);
    if (!(obj))
       return BLACK;
	if (last_obj && obj == last_obj)
		return BLACK;
	light_prepare(&newRT, obj);
	newRT.local_color = color_multiply(obj->color, compute_light(vars, &newRT));
	r = obj->refletive;
	if (recursion_depth <= 0 || r <= 0.001f)
		return newRT.local_color;
	newRT.rl.R = reflected_ray(vector_multiply(newRT.D, vector(-1, -1, -1)), newRT.rl.N);
	newRT.reflected_color = new_trace_ray(obj, vector_add(newRT.rl.P, vector_multiply(newRT.rl.R, vector(t_min,t_min,t_min))), newRT.rl.R, vars, \
		rt, 0.001f, INT_MAX, recursion_depth - 1);
	return (color_mult_int(newRT.local_color, (1 - r)) + color_mult_int(newRT.reflected_color, r));
}

void canvas_to_viewport(t_raytracer *rt, float x, float y)
{
	float d = 1;
	rt->D = vector(x*(1.0f/WIDTH) , -y*(1.0f/HEIGHT), d);
}

void raytracer(t_vars *vars)
{
	t_raytracer rt;
	int			x;
	int			y;

	x = -WIDTH_2;
	bzero(&rt, sizeof(t_raytracer));
	rt.O = vector(0, 0, 0);
	while (x < WIDTH_2)
	{
		y = -HEIGHT_2;
		while (y < HEIGHT_2)
		{
			rt.closest_obj = NULL;
			canvas_to_viewport(&rt, x, y); //get D
			//printf("antes\n");
			my_mlx_pixel_put(&vars->img, x + WIDTH_2, y + HEIGHT_2, \
				new_trace_ray(NULL, rt.O, rt.D, vars, &rt, 0.001f, INT_MAX, 1));//, color(255, 255, 255)));
			//printf("depois\n");
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

	// if (obj->type == CYLINDER)
	// {
	// 	float r = rt->D.z + rt->closest_t;
	// 	if (r > obj->vector.z && (r <= (obj->vector.z + obj->height)))
	// 		;
	// 	else
	// 		rt->closest_t = INT_MAX;
	// }