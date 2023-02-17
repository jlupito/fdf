/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:58:09 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/17 15:06:22 by jarthaud         ###   ########.fr       */
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

int render_grid(t_data *fdf)
{
	int	i;
	int j;

	fdf->coord = (t_coord){WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3, (WINDOW_WIDTH / 3) * 2, (WINDOW_HEIGHT / 3) * 2, WHITE_PIXEL};
	i = fdf->coord.y;
	while (i <= fdf->coord.ymax)
	{
		j = fdf->coord.x;
		while (j <= fdf->coord.xmax)
			mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, j++, i, WHITE_PIXEL);
		++i;
	}
	return (0);
}
