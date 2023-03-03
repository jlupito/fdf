/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:11:43 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/03 16:41:45 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void    prep_bresenham(t_data *fdf)
{
    fdf->map.x1 = fdf->map.x3;
    fdf->map.y1 = fdf->map.y3;
    fdf->map.x2 = fdf->map.x4;
    fdf->map.y2 = fdf->map.y4;
}

void bresenham(t_data *fdf, int color1, int color2, int flag)
{  
    if (flag == 1)
        prep_bresenham(fdf);
    fdf->map.dx =  abs(fdf->map.x2 - fdf->map.x1);
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
    while (fdf->map.x1 < fdf->map.x2 || fdf->map.y1 < fdf->map.y2)
    {
        if ((fdf->map.x1 > 0 && fdf->map.x1 < WINDOW_WIDTH) && (fdf->map.y1 > 0 && fdf->map.y1 < WINDOW_HEIGHT))
            img_pix_put(fdf, fdf->map.x1, fdf->map.y1, get_color_line(color1, color2));
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

void    draw_line(t_data *fdf)
{
   	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.nbline)
	{
		j = 0;
		while (j < fdf->map.nbcol)
		{
            fdf->map.x1 = (fdf->map.pixel[i][j].x - fdf->map.pixel[i][j].y) * cos(0.5236);
	        fdf->map.y1 = -fdf->map.pixel[i][j].alti + sin(0.5236) * (fdf->map.pixel[i][j].x + fdf->map.pixel[i][j].y);
	        if (j < fdf->map.nbcol - 1)
            {
                fdf->map.x2 = (fdf->map.pixel[i][j + 1].x - fdf->map.pixel[i][j + 1].y) * cos(0.5236);
	            fdf->map.y2 = -fdf->map.pixel[i][j + 1].alti + sin(0.5236) * (fdf->map.pixel[i][j + 1].x + fdf->map.pixel[i][j + 1].y);
                bresenham(fdf, fdf->map.pixel[i][j].color, fdf->map.pixel[i][j + 1].color, 0);
            }
			j++;
		}
		i++;
    }
}

void    draw_column(t_data *fdf)
{
    int i;
    int j;
    
    j = 0;
    while (j < fdf->map.nbcol)
	{
        i = fdf->map.nbline - 1;
		while (i > 0)
		{
            fdf->map.x3 = (fdf->map.pixel[fdf->map.nbline - i][j].x - fdf->map.pixel[fdf->map.nbline - i][j].y) * cos(0.5236);
	        fdf->map.y3 = -fdf->map.pixel[fdf->map.nbline - i][j].alti + sin(0.5236) * (fdf->map.pixel[fdf->map.nbline - i][j].x + fdf->map.pixel[fdf->map.nbline - i][j].y);
            fdf->map.x4 = (fdf->map.pixel[fdf->map.nbline - i - 1][j].x - fdf->map.pixel[fdf->map.nbline - i - 1][j].y) * cos(0.5236);
	        fdf->map.y4 = -fdf->map.pixel[fdf->map.nbline - i - 1][j].alti + sin(0.5236) * (fdf->map.pixel[fdf->map.nbline - i - 1][j].x + fdf->map.pixel[fdf->map.nbline - i - 1][j].y);
            bresenham(fdf, fdf->map.pixel[fdf->map.nbline - i][j].color, fdf->map.pixel[fdf->map.nbline - i - 1][j].color, 1);
			i--;
		}
		j++;
	} 
}