/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:58:09 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/20 15:46:55 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	img_pix_put(t_data *fdf, int x, int y, int color)
{
	char	*pixel;
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

int	render(t_data *fdf)
{	
	if (fdf->win_ptr == NULL)
		return (-1);
	render_background(fdf, BLACK_PIXEL);
	draw_line(fdf, 0, 0);
	draw_column(fdf, 0, 0);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->mlx_img, 0, 0);
	return (0);
}

int	window(t_data fdf)
{
	fdf.mlx_ptr = mlx_init();
	if (fdf.mlx_ptr == NULL)
		return (-1);
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (fdf.win_ptr == NULL)
	{
		free(fdf.win_ptr);
		return (-1);
	}
	fdf.mlx_img = mlx_new_image(fdf.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf.addr = mlx_get_data_addr(fdf.mlx_img, &fdf.bpp,
			&fdf.line_len, &fdf.endian);
	mlx_loop_hook(fdf.mlx_ptr, &render, &fdf);
	mlx_hook(fdf.win_ptr, KeyPress, KeyPressMask, handle_keypress, &fdf);
	mlx_hook(fdf.win_ptr, 17, 0, handle_buttonpress, &fdf);
	mlx_loop(fdf.mlx_ptr);
	mlx_destroy_image(fdf.mlx_ptr, fdf.mlx_img);
	mlx_destroy_display(fdf.mlx_ptr);
	free(fdf.mlx_ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	fdf;
	int		i;

	i = 0;
	if (argc != 2)
	{
		error_message(4);
		return (-1);
	}
	else if (check_map(argv[1]) == -1)
		return (-1);
	fill_map(argv[1], &fdf);
	window(fdf);
	while (i < fdf.map.nbline)
		free(fdf.map.pixel[i++]);
	free(fdf.map.pixel);
	return (0);
}
