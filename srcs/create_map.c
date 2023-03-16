/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:46:32 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/15 16:53:53 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	center_coord_x(int j, t_data *fdf)
{
	int	x;

	x = 0;
	if (j < (fdf->map.nbcol / 2) + (fdf->map.nbcol % 2))
		return (x = 0 - (((fdf->map.nbcol / 2)
					+ (fdf->map.nbcol % 2) - j) * fdf->offset));
	if (j == (fdf->map.nbcol / 2) + (fdf->map.nbcol % 2))
		return (x = 0);
	if (j > (fdf->map.nbcol / 2) + (fdf->map.nbcol % 2))
		return (x = (0 + (j - ((fdf->map.nbcol / 2)
						+ (fdf->map.nbcol % 2))) * fdf->offset));
	return (0);
}

int	center_coord_y(int i, t_data *fdf)
{
	int	y;

	y = 0;
	if (i < (fdf->map.nbline / 2) + (fdf->map.nbline % 2))
		return (y = (WINDOW_HEIGHT - (((fdf->map.nbline / 2)
						+ (fdf->map.nbline % 2) - i) * fdf->offset)));
	if (i == (fdf->map.nbline / 2) + (fdf->map.nbline % 2))
		return (y = WINDOW_HEIGHT);
	if (i > (fdf->map.nbline / 2) + (fdf->map.nbline % 2))
		return (y = (WINDOW_HEIGHT + (i - ((fdf->map.nbline / 2)
						+ (fdf->map.nbline % 2))) * fdf->offset));
	return (0);
}

t_pixel	*xyline(char *str, int i, t_pixel *pixel, t_data *fdf)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (j < fdf->map.nbcol)
	{
		while (str[k] == ' ' && str[k] && str[k] != '\n')
			k++;
		pixel[j].alti = ft_atoi(&str[k]);
		if (ft_atoi(&str[k]) > fdf->map.alt_max)
			fdf->map.alt_max = ft_atoi(&str[k]);
		if (ft_atoi(&str[k]) < fdf->map.alt_min)
			fdf->map.alt_min = ft_atoi(&str[k]);
		pixel[j].save_alti = pixel[j].alti;
		pixel[j].x = center_coord_x(j + 1, fdf) - 200;
		pixel[j].y = center_coord_y(i + 1, fdf);
		pixel[j].color = get_color(&str[k]);
		while (str[k] != ' ' && str[k])
			k++;
		j++;
	}
	return (pixel);
}

t_pixel	**save_map(int fd, t_pixel **pixel, t_data *fdf)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (i < fdf->map.nbline)
	{
		pixel[i] = malloc(sizeof(t_pixel) * (fdf->map.nbcol));
		if (!pixel[i])
			return (NULL);
		pixel[i] = xyline(line, i, pixel[i], fdf);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (pixel);
}

void	fill_map(char *argv, t_data *fdf)
{
	int		fd;
	t_pixel	**pixel;

	count_col_line(argv, fdf);
	fdf->map.alt_max = 0;
	fdf->map.alt_min = 0;
	offset(fdf);
	pixel = malloc(sizeof(t_pixel *) * (fdf->map.nbline));
	if (!pixel)
		return ;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return ;
	fdf->map.pixel = save_map(fd, pixel, fdf);
	reset_alti(fdf, fdf->map.alt_max - fdf->map.alt_min);
	if (close(fd) == -1)
		return ;
}
