/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:44:40 by dsa-mora          #+#    #+#             */
/*   Updated: 2022/10/22 12:44:40 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minirt.h"

//Esta funcao aloca memoria para n bytes com o malloc
//e depois coloca zeros em todos os bytes que alocou
void	*ft_calloc(size_t nelem, size_t elsize)
{
	char	*arr;
	size_t	i;

	i = -1;
	arr = malloc(elsize * nelem);
	if (!arr)
		return (NULL);
	if (nelem != 0)
	{
		while (++i < (elsize * nelem))
			arr[i] = 0;
		return ((void *)arr);
	}
	return ((void *)arr);
}
