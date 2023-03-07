/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:05:33 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/07 15:28:09 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void zoom(t_data *fdf, int flag)
{
	int i;
	int j;
	
	if (flag == 1)
		fdf->offset += 1;
	if (flag == 2)
		fdf->offset -= 1;
	{
		i = 0;
		while (i < fdf->map.nbline)
		{
			j = 0;
			while (j < fdf->map.nbcol)
			{
				if (flag == 1)
				{
					fdf->map.pixel[i][j].x += j * fdf->offset;
					fdf->map.pixel[i][j].y += i * fdf->offset;
				}
				if (flag == 2)
				{
					fdf->map.pixel[i][j].x -= j * fdf->offset;
					fdf->map.pixel[i][j].y -= i * fdf->offset;
				}
				if ((flag == 1 && fdf->map.pixel[i][j].save_alti) || (flag == 4 && fdf->map.pixel[i][j].save_alti))
					{
						fdf->map.pixel[i][j].alti += 1;
						if (fdf->map.pixel[i][j].alti == 0)
							fdf->map.pixel[i][j].alti = fdf->map.pixel[i][j].save_alti;
					}
				if ((flag == 2 && fdf->map.pixel[i][j].save_alti) || (flag == 3 && fdf->map.pixel[i][j].save_alti))
					{
						if (fdf->map.pixel[i][j].alti > 0)
							fdf->map.pixel[i][j].alti -= 1;
					}
				j++;
			}
			i++;
		}
	}
}


int	handle_keypress(int keysym, t_data *fdf)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		fdf->win_ptr = NULL;
	}
	if (keysym == XK_KP_Add)
		zoom(fdf, 1);
	if (keysym == XK_KP_Subtract)
		zoom(fdf, 2);
	if (keysym == XK_Left)
		fdf->horizontal -= 10;
	if (keysym == XK_Right)
		fdf->horizontal += 10;
	if (keysym == XK_Up)
		fdf->vertical += 10;
	if (keysym == XK_Down)
		fdf->vertical -= 10;
	if (keysym == XK_h)
		zoom(fdf, 3);
	if (keysym == XK_j)
		zoom(fdf, 4);
	if (keysym == XK_n)
		fdf->rotate -= 0.01;
	if (keysym == XK_m)
		fdf->rotate += 0.01;
	return (0);
}

// int	handle_buttonpress(int button, int x, int y, t_data *fdf)
// {
// 	if (button == Button1 && x >= WINDOW_WIDTH )
// 	{
// 		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
// 		fdf->win_ptr = NULL;
// 	}
// 	return (0);
// }

// void rotate(t_data *fdf, int flag)
// {
// 	int i;
// 	int j;
// 	i = 0;
// 	while (i < fdf->map.nbline)
// 	{
// 		j = 0;
// 		while (j < fdf->map.nbcol)
// 		{
// 				fdf->map.pixel[i][j].x += j * fdf->offset;
// 				fdf->map.pixel[i][j].y += i * fdf->offset;
// 			j++;
// 		}
// 		i++;
// 	}
// }