/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:23:48 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/20 13:23:42 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_color_int(int i, int len, char *str)
{
	int	val;

	val = 0;
	while (i++ < len)
	{
		if (str[i] <= 57)
			val += (str[i] - 48) * (1 << (4 * (len - 1 - i)));
		else
			val += (str[i] - 55) * (1 << (4 * (len - 1 - i)));
	}
	return (val);
}

int	get_color(char *str)
{
	int	i;
	int	len;
	int	val;

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
	if (str[len] == '\0')
		len--;
	val = get_color_int(i, len, str);
	return (val);
}

double	lerp(double col1, double col2, double percent)
{
	if (col1 == col2)
		return (col1);
	return (col1 * (1.0 - percent) + (col2 * percent));
}

int	color_lerp(int col1, int col2, double percent)
{
	int	r;
	int	g;
	int	b;

	if (col1 == col2)
		return (col1);
	if (percent == 0.0)
		return (col1);
	if (percent == 1.0)
		return (col2);
	r = (int)lerp(((col1 >> 16) & 0xFF), ((col2 >> 16) & 0xFF), percent);
	g = (int)lerp(((col1 >> 8) & 0xFF), ((col2 >> 8) & 0xFF), percent);
	b = (int)lerp((col1 & 0xFF), (col2 & 0xFF), percent);
	return (r << 16 | g << 8 | b);
}

double	percent(double x0, double x1, double x2)
{
	if (x1 == x0)
		return (0.0);
	if (x1 == x2)
		return (1.0);
	if (x0 == x2)
		return (0.0);
	return ((x1 - x0) / (x2 - x0));
}
