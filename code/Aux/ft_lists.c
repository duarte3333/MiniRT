/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:42:09 by duarte33          #+#    #+#             */
/*   Updated: 2023/10/10 17:21:56 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	lst_add_back(t_scene *scene, t_type type, char *line)
{
	t_object	*new;

	new = parse_next(type, line);
	if (new)
	{
		if (scene->object == NULL)
			scene->object = new;
		else
			scene->end->next = new;
		scene->end = new;
	}
	else
		scene->syntax = true;
}

void	light_add_back(t_scene *scene, t_type type, char *line)
{
	t_object	*new;

	new = parse_next(type, line);
	if (new)
	{
		if (scene->light == NULL)
			scene->light = new;
		else
			scene->end_light->next = new;
		scene->end_light = new;
	}
}

// void addback_bonito(t_list** lst, t_list* new) {
//     static t_list* end;

//     if (!lst)
//         return;
//     if (!(*lst)) 
//     {
//         *lst = new;
//         end = new;
//     } 
//     else 
//     {
//         end->next = new;
//         end = new;
//     }
// }