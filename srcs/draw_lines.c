/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:11:43 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/08 15:34:45 by jarthaud         ###   ########.fr       */
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
    while (fdf->map.x1 <= fdf->map.x2 || fdf->map.y1 <= fdf->map.y2)
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
            fdf->map.x1 =  cos(0.5236) * (fdf->map.pixel[i][j].y + fdf->map.pixel[i][j].x) + fdf->horizontal;
	        fdf->map.y1 = (fdf->map.pixel[i][j].y - fdf->map.pixel[i][j].x) * sin(0.5236) - (fdf->map.pixel[i][j].alti) - fdf->vertical;
            if (j < fdf->map.nbcol - 1)
            {
                fdf->map.x2 =  cos(0.5236) * (fdf->map.pixel[i][j + 1].y + fdf->map.pixel[i][j + 1].x) + fdf->horizontal;
                fdf->map.y2 = (fdf->map.pixel[i][j + 1].y - fdf->map.pixel[i][j + 1].x) * sin(0.5236) - (fdf->map.pixel[i][j + 1].alti) - fdf->vertical;
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
        i = 0;
		while (i < fdf->map.nbline - 1)
		{
            fdf->map.x3 =  cos(0.5236) * (fdf->map.pixel[i][j].y + fdf->map.pixel[i][j].x) + fdf->horizontal;
	        fdf->map.y3 = (fdf->map.pixel[i][j].y - fdf->map.pixel[i][j].x) * sin(0.5236) - (fdf->map.pixel[i][j].alti) - fdf->vertical;
            if (i < fdf->map.nbline - 1)
            {
                fdf->map.x4 =  cos(0.5236) * (fdf->map.pixel[i + 1][j].y + fdf->map.pixel[i + 1][j].x) + fdf->horizontal;
	            fdf->map.y4 = (fdf->map.pixel[i + 1][j].y - fdf->map.pixel[i + 1][j].x) * sin(0.5236) - (fdf->map.pixel[i + 1][j].alti) - fdf->vertical;
                bresenham(fdf, fdf->map.pixel[i][j].color, fdf->map.pixel[i + 1][j].color, 1);
            }
			i++;
		}
		j++;
	} 
}
