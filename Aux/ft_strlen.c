/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duarte33 <duarte33@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:39:36 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/09/10 18:40:06 by duarte33         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//Retorna o numero de elementos de uma str sem contar com o NULL
int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// int main(void)
// {
//     printf("%i", ft_strlen("duarte"));
// }