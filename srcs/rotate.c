/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:19:48 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/06 18:02:52 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	calculate_rotate(int degree, t_data fdf)
{
	float	sinus;
	float	cosinus;

	sinus = sin(0.01745329252 * degree);
	cosinus = cos(0.01745329252 * degree);
	fdf.map.x1 = (int)roundf(fdf.map.pixel[i][j].x * cosinus) - (fdf.map.pixel[i][j].y * sinus); 
	fdf.map.y1 = (int)roundf(fdf.map.pixel[i][j].y * sinus) - (fdf.map.pixel[i][j].yx * cosinus);
	
	return (coord);
}



// void tranform()

// float	calculate_sin(int	degree)
// {
// 	float	sinus;

// 	sinus = sin(0.01745329252 * degree);
// 	return (sinus);
// }

// float	calculate_cos(int	degree)
// {
// 	float	cosinus;

// 	cosinus = cos(0.01745329252 * degree);
// 	return (cosinus);
// }

// int	rotate_x(int	degree, float x, float y)
// {
// 	int	x2;

// 	x2 = (int)roundf(x * calculate_cos(degree)) - (y * calculate_sin(degree));
// 	return (x2);
// }

// int	rotate_y(int	degree, float x, float  y)
// {
// 	int	y2;

// 	y2 = (int)roundf(y * calculate_sin(degree)) - (x * calculate_cos(degree));
// 	return (y2);
// }