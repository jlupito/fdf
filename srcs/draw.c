/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:11:43 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/16 18:19:38 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_bresenham(t_data *fdf, int col1, int col2)
{
	while (fdf->map.x1 <= fdf->map.x2 || fdf->map.y1 <= fdf->map.y2)
	{
		if ((fdf->map.x1 > 0 && fdf->map.x1 < WINDOW_WIDTH)
			&& (fdf->map.y1 > 0 && fdf->map.y1 < WINDOW_HEIGHT))
		{
			if (fdf->map.dx > fdf->map.dy)
				fdf->map.percent = percent(fdf->map.x0, fdf->map.x2, fdf->map.x1);
			else
				fdf->map.percent = percent(fdf->map.y0, fdf->map.y2, fdf->map.y1);
			printf("percent: %f\n", fdf->map.percent);
			img_pix_put(fdf, fdf->map.x1, fdf->map.y1,
				color_lerp(col1, col2, fdf->map.percent));
		}
		if (fdf->map.x1 == fdf->map.x2 && fdf->map.y1 == fdf->map.y2)
			break ;
		fdf->map.e2 = 2 * fdf->map.err;
		if (fdf->map.e2 >= fdf->map.dy)
		{
			fdf->map.err += fdf->map.dy;
			fdf->map.x1 += fdf->map.sx;
		}
		if (fdf->map.e2 <= fdf->map.dx)
		{
			fdf->map.err += fdf->map.dx;
			fdf->map.y1 += fdf->map.sy;
		}
	}
}

void	bresenham(t_data *fdf, int col1, int col2)
{
	fdf->map.x0 = fdf->map.x1;
	fdf->map.y0 = fdf->map.x1;
	fdf->map.dx = abs(fdf->map.x2 - fdf->map.x1);
	fdf->map.dy = -abs(fdf->map.y2 - fdf->map.y1);
	if (fdf->map.x1 < fdf->map.x2)
		fdf->map.sx = 1;
	else
		fdf->map.sx = -1;
	if (fdf->map.y1 < fdf->map.y2)
		fdf->map.sy = 1;
	else
		fdf->map.sy = -1;
	fdf->map.err = fdf->map.dx + fdf->map.dy;
	fdf->map.e2 = 0;
	draw_bresenham(fdf, col1, col2);
}

void	draw_line(t_data *fdf, int i, int j)
{
	while (i < fdf->map.nbline)
	{
		j = 0;
		while (j < fdf->map.nbcol)
		{
			fdf->map.x1 = cos(0.5236) * (fdf->map.pixel[i][j].y
					+ fdf->map.pixel[i][j].x) + fdf->horizontal;
			fdf->map.y1 = (fdf->map.pixel[i][j].y - fdf->map.pixel[i][j].x)
				* sin(0.5236) - (fdf->map.pixel[i][j].alti * fdf->offset)
				- fdf->vertical;
			if (j < fdf->map.nbcol - 1)
			{
				fdf->map.x2 = cos(0.5236) * (fdf->map.pixel[i][j + 1].y
						+ fdf->map.pixel[i][j + 1].x) + fdf->horizontal;
				fdf->map.y2 = (fdf->map.pixel[i][j + 1].y
						- fdf->map.pixel[i][j + 1].x) * sin(0.5236)
					- (fdf->map.pixel[i][j + 1].alti * fdf->offset)
					- fdf->vertical;
				bresenham(fdf, fdf->map.pixel[i][j].color,
					fdf->map.pixel[i][j + 1].color);
			}
			j++;
		}
		i++;
	}
}

void	draw_column(t_data *fdf, int i, int j)
{
	while (j < fdf->map.nbcol)
	{
		i = 0;
		while (i < fdf->map.nbline - 1)
		{
			fdf->map.x1 = cos(0.5236) * (fdf->map.pixel[i][j].y
					+ fdf->map.pixel[i][j].x) + fdf->horizontal;
			fdf->map.y1 = (fdf->map.pixel[i][j].y - fdf->map.pixel[i][j].x)
				* sin(0.5236) - (fdf->map.pixel[i][j].alti * fdf->offset)
				- fdf->vertical;
			if (i < fdf->map.nbline - 1)
			{
				fdf->map.x2 = cos(0.5236) * (fdf->map.pixel[i + 1][j].y
						+ fdf->map.pixel[i + 1][j].x) + fdf->horizontal;
				fdf->map.y2 = (fdf->map.pixel[i + 1][j].y
						- fdf->map.pixel[i + 1][j].x) * sin(0.5236)
					- (fdf->map.pixel[i + 1][j].alti * fdf->offset)
					- fdf->vertical;
				bresenham(fdf, fdf->map.pixel[i][j].color,
					fdf->map.pixel[i + 1][j].color);
			}
			i++;
		}
		j++;
	}
}

// void	prep_bresenham(t_data *fdf)
// {
// 	fdf->map.x1 = fdf->map.x3;
// 	fdf->map.y1 = fdf->map.y3;
// 	fdf->map.x2 = fdf->map.x4;
// 	fdf->map.y2 = fdf->map.y4;
// }
