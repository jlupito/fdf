/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:19:48 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/01 18:07:59 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	calculate_rot_x(int degree, t_data fdf)
{
	float	sinus;
	float	cosinus;

	sinus = sin(0.01745329252 * degree);
	cosinus = cos(0.01745329252 * degree);
	fdf.map.x1 = (int)roundf(fdf.map.pixel[i][j].x * cosinus) - (fdf.map.pixel[i][j].y * sinus); 
	fdf.map.y1 = (int)roundf(fdf.map.pixel[i][j].y * sinus) - (fdf.map.pixel[i][j].yx * cosinus);
	
	return (coord);
}

int	calculate_rot_y(int degree, t_data fdf)
{
	float	sinus;
	float	cosinus;

	sinus = sin(0.01745329252 * degree);
	cosinus = cos(0.01745329252 * degree);
	fdf.map.x1 = (int)roundf(fdf.map.pixel[i][j].x * cosinus) - (fdf.map.pixel[i][j].y * sinus); 
	fdf.map.y1 = (int)roundf(fdf.map.pixel[i][j].y * sinus) - (fdf.map.pixel[i][j].yx * cosinus);
	
	return (coord);
}

void	render_grid(t_data *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.nbline)
	{
		j = 0;
		while (j < fdf->map.nbcol)
		{
			if ((fdf->map.pixel[i][j].x > 0 && fdf->map.pixel[i][j].x < WINDOW_WIDTH) && (fdf->map.pixel[i][j].y > 0 && fdf->map.pixel[i][j].y < WINDOW_HEIGHT))
				img_pix_put(fdf, fdf->map.pixel[i][j].x, fdf->map.pixel[i][j].y, fdf->map.pixel[i][j].color);
			j++;
		}
		i++;
	}
}

 int    ft_draw(t_fdf *fdf)
{
    int    i;
    int    j;

    i = 0;
    while (i < fdf->map.len_col)
    {
        j = 0;
        while (j < fdf->map.len_row)
        {
            if (j < fdf->map.len_row - 1)
                ft_print_line(i, j, fdf, 1);
            if (i < fdf->map.len_col - 1)
                ft_print_line(i, j, fdf, 2);
            j++;
        }
        i++;
    }
    return (0);
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