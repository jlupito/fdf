/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:39:56 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/20 16:54:58 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

int	render(t_data *fdf)
{
	
	if (fdf->win_ptr == NULL)
		return (-1);
	render_background(fdf, BLACK_PIXEL);
	render_grid(fdf, (t_coord){WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3, (WINDOW_WIDTH / 3) * 2, (WINDOW_HEIGHT / 3) * 2, WHITE_PIXEL});
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
	mlx_hook(fdf.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &fdf);
	mlx_loop(fdf.mlx_ptr);

	mlx_destroy_image(fdf.mlx_ptr, fdf.mlx_img);
	mlx_destroy_display(fdf.mlx_ptr);
	free(fdf.mlx_ptr);
	return (0);
}