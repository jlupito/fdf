/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:05:33 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/08 17:18:18 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void zoom(t_data *fdf, int flag)
{
	int i;
	int j;
	
	// if (flag == 1)
	// 	fdf->offset += 1;
	// if (flag == 2)
	// 	fdf->offset -= 1;
	// {
		i = 0;
		while (i < fdf->map.nbline)
		{
			j = 0;
			while (j < fdf->map.nbcol)
			{
				if (flag == 1)
				{
					fdf->offset++;;
					// fdf->map.pixel[i][j].y -= fdf->offset;
				}
				if (flag == 2)
				{
					fdf->map.pixel[i][j].x += fdf->offset;
					fdf->map.pixel[i][j].y += fdf->offset;
				}
				// if ((flag == 1 && fdf->map.pixel[i][j].save_alti) || (flag == 4 && fdf->map.pixel[i][j].save_alti))
				// 	{
				// 		fdf->map.pixel[i][j].alti += 1;
				// 		if (fdf->map.pixel[i][j].alti == 0)
				// 			fdf->map.pixel[i][j].alti = fdf->map.pixel[i][j].save_alti;
				// 	}
				// if ((flag == 2 && fdf->map.pixel[i][j].save_alti) || (flag == 3 && fdf->map.pixel[i][j].save_alti))
				// 	{
				// 		if (fdf->map.pixel[i][j].alti > 0)
				// 			fdf->map.pixel[i][j].alti -= 1;
				// 	}
				j++;
			}
			i++;
		}
	// }
}

void zoom_alti(t_data *fdf, int flag)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->map.nbline)
	{
		j = 0;
		while (j < fdf->map.nbcol)
		{
			if ((flag == 1 && fdf->map.pixel[i][j].save_alti))
					fdf->map.pixel[i][j].alti *= 1.5;
			if ((flag == 2 && fdf->map.pixel[i][j].save_alti))
					fdf->map.pixel[i][j].alti /= 1.5;
			j++;
		}
		i++;
	}
}

void reverse_alti(t_data *fdf)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->map.nbline)
	{
		j = 0;
		while (j < fdf->map.nbcol)
		{
			fdf->map.pixel[i][j].alti = -fdf->map.pixel[i][j].alti;
			j++;
		}
		i++;
	}
}

int	handle_keypress(int keysym, t_data *fdf)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		fdf->win_ptr = NULL;
	}
	if (keysym == XK_Left)
		fdf->horizontal -= 10;
	if (keysym == XK_Right)
		fdf->horizontal += 10;
	if (keysym == XK_Up)
		fdf->vertical += 10;
	if (keysym == XK_Down)
		fdf->vertical -= 10;
	if (keysym == XK_g)
		reverse_alti(fdf);
	if (keysym == XK_KP_Add)
		zoom(fdf, 1);
	if (keysym == XK_KP_Subtract)
		zoom(fdf, 2);
	if (keysym == XK_h)
		zoom_alti(fdf, 1);
	if (keysym == XK_j)
		zoom_alti(fdf, 2);
	return (0);
}

int	handle_buttonpress(t_data *fdf)
{
	int	i;

	i = 0;
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	fdf->win_ptr = NULL;
	mlx_destroy_image(fdf->mlx_ptr, fdf->mlx_img);
	mlx_destroy_display(fdf->mlx_ptr);
	free(fdf->mlx_ptr);
	while (i < fdf->map.nbline)
		free(fdf->map.pixel[i++]);
	free(fdf->map.pixel);
	exit (0);
}

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