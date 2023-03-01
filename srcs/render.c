/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:58:09 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/01 16:57:42 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	img_pix_put(t_data *fdf, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = fdf->bpp - 8;
    pixel = fdf->addr + (y * fdf->line_len + x * (fdf->bpp / 8));
	while (i >= 0)
	{
		if (fdf->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (fdf->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render_background(t_data *fdf, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(fdf, j++, i, color);
		++i;
	}
}

void	render_grid(t_data *fdf)
{
	int	i;
	int	j;

	i = 0;
	fdf->map.y1 = 0;
	fdf->map.x1 = 0;
	while (i < fdf->map.nbline)
	{
		j = 0;
		//fdf->map.y1 = fdf->map.pixel[i][j].y;
		while (j < fdf->map.nbcol)
		{
			fdf->map.x1 = (fdf->map.pixel[i][j].x - fdf->map.pixel[i][j].y) * cos(0.5236);
			fdf->map.y1 = -fdf->map.pixel[i][j].alti + sin(0.5236) * (fdf->map.pixel[i][j].x + fdf->map.pixel[i][j].y);
			//fdf->map.x1 = (fdf->map.pixel[i][j].x);
			if ((fdf->map.x1 > 0 && fdf->map.x1 < WINDOW_WIDTH) && (fdf->map.y1 > 0 && fdf->map.y1 < WINDOW_HEIGHT))
				img_pix_put(fdf, fdf->map.x1, fdf->map.y1, fdf->map.pixel[i][j].color);
			j++;
		}
		i++;
	}
}

// void	render_grid(t_data *fdf)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < fdf->map.nbline)
// 	{
// 		j = 0;
// 		while (j < fdf->map.nbcol)
// 		{
// 			if ((fdf->map.pixel[i][j].x > 0 && fdf->map.pixel[i][j].x < WINDOW_WIDTH) && (fdf->map.pixel[i][j].y > 0 && fdf->map.pixel[i][j].y < WINDOW_HEIGHT))
// 				img_pix_put(fdf, fdf->map.pixel[i][j].x, fdf->map.pixel[i][j].y, fdf->map.pixel[i][j].color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

int	render(t_data *fdf)
{	
	if (fdf->win_ptr == NULL)
		return (-1);
	render_background(fdf, BLACK_PIXEL);
	// fdf->offset = 10;
	render_grid(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->mlx_img, 0, 0);
	return (0);
}

int	window(t_data fdf)
{
	fdf.mlx_ptr = mlx_init();
	if (fdf.mlx_ptr == NULL)
		return (-1);
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (fdf.win_ptr == NULL)
	{
		free(fdf.win_ptr);
		return (-1);
	}
	fdf.mlx_img = mlx_new_image(fdf.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf.addr = mlx_get_data_addr(fdf.mlx_img, &fdf.bpp, &fdf.line_len, &fdf.endian);

	mlx_loop_hook(fdf.mlx_ptr, &render, &fdf);
	mlx_hook(fdf.win_ptr, KeyPress, KeyPressMask, handle_keypress, &fdf);
	mlx_loop(fdf.mlx_ptr);
	mlx_destroy_image(fdf.mlx_ptr, fdf.mlx_img);
	mlx_destroy_display(fdf.mlx_ptr);
	free(fdf.mlx_ptr);

	return (0);
}
