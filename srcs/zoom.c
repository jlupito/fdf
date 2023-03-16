/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:05:33 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/15 17:11:31 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	zoom_in(t_data *fdf)
{
	int	i;
	int	j;

	if (fdf->offset >= 2)
		fdf->offset *= 1.5;
	i = 0;
	if (fdf->offset >= 2)
	{
		while (i < fdf->map.nbline)
		{
			j = 0;
			while (j < fdf->map.nbcol)
			{
				fdf->map.pixel[i][j].x = center_coord_x(j + 1, fdf) - 200;
				fdf->map.pixel[i][j].y = center_coord_y(i + 1, fdf);
				j++;
			}
			i++;
		}
	}
}

void	zoom_out(t_data *fdf)
{
	int	i;
	int	j;

	if (fdf->offset > 2)
		fdf->offset /= 1.5;
	i = 0;
	if (fdf->offset >= 2)
	{
		while (i < fdf->map.nbline)
		{
			j = 0;
			while (j < fdf->map.nbcol)
			{
				fdf->map.pixel[i][j].x = center_coord_x(j + 1, fdf) - 200;
				fdf->map.pixel[i][j].y = center_coord_y(i + 1, fdf);
				j++;
			}
			i++;
		}
	}
}

void	zoom_alti(t_data *fdf, int flag)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.nbline)
	{
		j = 0;
		while (j < fdf->map.nbcol)
		{
			if (fdf->map.pixel[i][j].save_alti != 0)
			{
				if ((flag == 1 && fdf->map.pixel[i][j].save_alti))
					fdf->map.pixel[i][j].alti += 5;
				if ((flag == 1 && fdf->map.pixel[i][j].save_alti < 0))
					fdf->map.pixel[i][j].alti -= 5;
				if ((flag == 2 && fdf->map.pixel[i][j].save_alti))
					fdf->map.pixel[i][j].alti -= 5;
				if ((flag == 2 && fdf->map.pixel[i][j].save_alti < 0))
					fdf->map.pixel[i][j].alti += 5;
			}
			j++;
		}
		i++;
	}
}

void	reverse_alti(t_data *fdf)
{
	int	i;
	int	j;

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
