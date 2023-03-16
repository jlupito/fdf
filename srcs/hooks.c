/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:05:33 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/15 16:52:20 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
	if (keysym == XK_KP_Add)
		zoom_in(fdf);
	if (keysym == XK_KP_Subtract)
		zoom_out(fdf);
	if (keysym == XK_a)
		zoom_alti(fdf, 1);
	if (keysym == XK_d)
		zoom_alti(fdf, 2);
	if (keysym == XK_s)
		reverse_alti(fdf);
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