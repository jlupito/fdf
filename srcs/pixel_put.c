/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:58:09 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/20 17:00:11 by jarthaud         ###   ########.fr       */
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

int render_grid(t_data *fdf, t_coord coord)
{
	int	i;
	int j;

	i = coord.y;
	while (i < coord.ymax)
	{
		j = coord.x;
		while (j < coord.xmax)
		{
			img_pix_put(fdf, j, i, WHITE_PIXEL);
			j += ((coord.xmax - coord.x) / (fdf->map.nbcol - 1));
		}
		i += ((coord.ymax - coord.y) / (fdf->map.nbline - 1));
	}
	return (0);
}
