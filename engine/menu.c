/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:39:30 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/08 01:59:16 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"



void	ft_part_one()
{
	mlx_string_put(vars()->mlx, vars()->win, 50, 50, 0xAFA9A9, "Objects: click to select a object :)");
	mlx_string_put(vars()->mlx, vars()->win, 50, 75, 0xAFA9A9, "< - left");
	mlx_string_put(vars()->mlx, vars()->win, 50, 100, 0xAFA9A9, "> - right");
	mlx_string_put(vars()->mlx, vars()->win, 50, 125, 0xAFA9A9, "\\/ - bottom");
	mlx_string_put(vars()->mlx, vars()->win, 50, 150, 0xAFA9A9, \
	"z and x - decrease/increase z");
	mlx_string_put(vars()->mlx, vars()->win, 50, 175, 0xAFA9A9, \
		"i and k - rotation x");
	mlx_string_put(vars()->mlx, vars()->win, 50, 200, 0xAFA9A9, \
		"j and l - rotation y");
	mlx_string_put(vars()->mlx, vars()->win, 50, 225, 0xAFA9A9, \
		"u and o - rotation z");
	mlx_string_put(vars()->mlx, vars()->win, 50, 275, 0xAFA9A9, \
		"scroll down to zoom in");
	mlx_string_put(vars()->mlx, vars()->win, 50, 300, 0xAFA9A9, \
		"scrool up to zoom out");
	mlx_string_put(vars()->mlx, vars()->win, 50, 325, 0xAFA9A9, \
		"Camera:");
}

char *choose_light()
{
	if (vars()->scene->select_light)
	{
		if (vars()->scene->select_light->type == 4)
			return ("Ambient Light");
		if (vars()->scene->select_light->type == 5)
			return ("Point Light");
		if (vars()->scene->select_light->type == 5)
			return ("Directional Light");
	}
	else
		return ("None selected");
	
}

void	ft_menu()
{
	ft_part_one();
	mlx_string_put(vars()->mlx, vars()->win, 50, 350, 0xAFA9A9, \
	"1 - go up with camera");
	mlx_string_put(vars()->mlx, vars()->win, 50, 375, 0xAFA9A9, \
	"2 - go down with camera");
	mlx_string_put(vars()->mlx, vars()->win, 50, 400, 0xAFA9A9, \
		"q / e - rotate camera along y axis");
	mlx_string_put(vars()->mlx, vars()->win, 50, 425, 0xAFA9A9, \
		"3 / 4 - rotate camera along x axis");
	mlx_string_put(vars()->mlx, vars()->win, 50, 450, 0xAFA9A9, \
		"c / v - rotate camera along z axis");
	mlx_string_put(vars()->mlx, vars()->win, WIDTH - 150, \
		20, 0xAFA9A9, "MAP NAME");
	mlx_string_put(vars()->mlx, vars()->win, WIDTH - 150, \
	 	40, 0xAFA9A9, vars()->scene->map_file);
	mlx_string_put(vars()->mlx, vars()->win, WIDTH - 150, \
		60, 0xAFA9A9, "LIGHT SELECTED");
	char *str = choose_light();
	mlx_string_put(vars()->mlx, vars()->win, WIDTH - 150, \
		80, 0xAFA9A9, choose_light());
	mlx_string_put(vars()->mlx, vars()->win, 100, \
		HEIGHT - 25, 0xAFA9A9, "By: Duarte Morais");
}
