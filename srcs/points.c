/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:58:09 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/24 13:18:41 by jarthaud         ###   ########.fr       */
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

t_pixel	*ft_xyline(char *str, int count, t_pixel *pixel)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ' && str[i])
			i++;
		// if (fdf->proj == 1)
		pixel[j].altitude = ft_atoi(&str[i]);
		pixel[j].x = (WINDOW_WIDTH / 2) + (j * 5) - (count * 5);
		pixel[j].y = (WINDOW_WIDTH / 3) - (pixel[j].altitude * 5) + (count * 5);
		if (str[i + 2] == ',')
			pixel[j].color = get_color(&str[i]);
		else
			pixel[j].color = WHITE_PIXEL;
		while (str[i] != ' ' && str[i])
			i++;
		j++;
	}
	return (pixel);
}

t_pixel	**get_pixel(t_data *fdf, t_pixel **pixel)
{
	int		count;
	
	count = 0;
	while(fdf->map->tabtab[count])
	{
		if (!(pixel[count] = malloc(sizeof(t_pixel) * (fdf->map->nbcol + 1))))
			return (NULL);
		pixel[count] = ft_xyline(fdf->map->tabtab[count], count, pixel[count]);
		count++;
	}
	pixel[count] = NULL;
	return (pixel);
}

void	set_pixel(t_data *fdf)
{
	t_pixel **pixel;
	int	i;
	int	j;

	i = 0;
	if (!(pixel = malloc(sizeof(t_pixel*) * (fdf->map->nbline + 1))))
		return ;
	pixel = get_pixel(fdf, pixel);
	while (pixel[i])
	{
		j = 0;
		while (fdf->map->nbcol > j)
		{
			img_pix_put(fdf, pixel[i][j].x, pixel[i][j].y, pixel[i][j].color);
			j++;
		}
		i++;
	}
}
