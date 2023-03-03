/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:23:48 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/03 16:25:19 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_color(char *str)
{
    int i;
	int	len;
    int val;

	val = 0;
	i = 0;
	while (str[i] != 'x' && str[i] != ' ' && str[i])
	{
		i++;
		if (str[i] == ' ' || str[i] == '\0')
			return (16777215);
	}
	len = i;
	while (str[len] != ' ' && str[len])
	{
		if (str[len] >= 97 && str[len] <= 122)
			str[len] = str[len] - 32;
		len++;
	}
	while (i++ < len)
	{
    	if (str[i] <= 57)
        	val += (str[i] - 48) * (1 << (4 * (len - 1 - i)));
    	else
        	val += (str[i] - 55) * (1 << (4 * (len - 1 - i)));
	}
	return (val);
}

int	get_color_line(int color1, int color2)
{
    int color;

	color = 0;
	if (color1 == color2)
		color = color1;
	else
		color = color2;
	return(color);
}