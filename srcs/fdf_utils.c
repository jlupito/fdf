/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:55:56 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/24 11:26:32 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	count_col(char *str, char c)
{
	int i;
	int col;

	i = 0;
	col = 0;
	while (str[i] != '\n' && str[i])
	{
		if (str[i] != c)
		{
			col++;
			while (str[i] != c && str[i] != '\n')
				i++;
		}
		if (str[i] == c)
			i++;
	}
	return (col);
}

// int	**create_double_tab(size_t x, size_t y)
// {
// 	size_t	i;
// 	int	**tab;
// 	int	*tab2;

// 	i = 0;
// 	tab = (int**)malloc(sizeof(tab) * y);
// 	if (!tab)
// 		return (NULL);
// 	tab2 = (int*)malloc(sizeof(tab2) * (x * y));
// 	if (!tab2)
// 		return (NULL);
// 	while (i < y)
// 	{
// 		tab[i] = &tab2[i * x];
// 		i++;
// 	}
// 	return (tab);
// }