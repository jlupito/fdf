/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:46:32 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/08 17:09:38 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	offset(t_data *fdf)
{
	fdf->horizontal = 0;	
	fdf->vertical = 0;	
	if (fdf->map.nbcol <= 20)
		fdf->offset = 30;
	else if (fdf->map.nbcol >= 20 && fdf->map.nbcol < 50)
		fdf->offset = 25;
	else if (fdf->map.nbcol >= 50 && fdf->map.nbcol < 100)
		fdf->offset = 20;
	else if (fdf->map.nbcol >= 100 && fdf->map.nbcol < 200)
		fdf->offset = 10;
	else if (fdf->map.nbcol >= 200 && fdf->map.nbcol < 500)
		fdf->offset = 5;
	else
		fdf->offset = 1;
}

int	center_coord(int i, int j, int flag, t_data *fdf)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	if (flag == 1)
	{
		if (j < (fdf->map.nbcol / 2) + (fdf->map.nbcol % 2))
			return (x = ((WINDOW_WIDTH / 2) - (((fdf->map.nbcol / 2) + (fdf->map.nbcol % 2) - j) * fdf->offset)));
		if (j == (fdf->map.nbcol / 2) + (fdf->map.nbcol % 2))
			return (x = (WINDOW_WIDTH / 2));
		if (j > (fdf->map.nbcol / 2) + (fdf->map.nbcol % 2))
			return (x = ((WINDOW_WIDTH / 2) + ((j - ((fdf->map.nbcol / 2) + (fdf->map.nbcol % 2))) * fdf->offset)));
	}
	if (flag == 2)
	{
		if (i < (fdf->map.nbline / 2) + (fdf->map.nbline % 2))
			return (y = ((WINDOW_HEIGHT / 2) - (((fdf->map.nbline / 2) + (fdf->map.nbline % 2) - i) * fdf->offset)));
		if (i == (fdf->map.nbline / 2) + (fdf->map.nbline % 2))
			return (y = (WINDOW_HEIGHT/ 2));
		if (i > (fdf->map.nbline / 2) + (fdf->map.nbline % 2))
			return (y = ((WINDOW_HEIGHT/ 2) + ((i - (fdf->map.nbline / 2 + (fdf->map.nbline % 2))) * fdf->offset)));
	}
	return (0);
}

t_pixel	*xyline(char *str, int i, t_pixel *pixel, t_data *fdf)
{
	int	k;
	int j;

	k = 0;
	j = 0;
	while (j < fdf->map.nbcol)
	{
		while (str[k] == ' ' && str[k])
			k++;
		pixel[j].alti = ft_atoi(&str[k]) * fdf->offset;
		if (ft_atoi(&str[k]) > fdf->map.alt_max)
			fdf->map.alt_max = ft_atoi(&str[k]);
		if (ft_atoi(&str[k]) < fdf->map.alt_min)
			fdf->map.alt_min = ft_atoi(&str[k]);
		pixel[j].save_alti = pixel[j].alti;
		pixel[j].x = center_coord(i + 1, j + 1, 1, fdf) - 1000; // ((WINDOW_WIDTH / 2) + (j * fdf->offset) - 1000;
		pixel[j].y = center_coord(i + 1, j + 1, 2, fdf) + 600; //(WINDOW_HEIGHT / 2) + (i * fdf->offset) + 500;
		pixel[j].color = get_color(&str[k]);
		while (str[k] != ' ' && str[k])
			k++;
		j++;
	}
	return (pixel);
}

t_pixel	**save_map(int fd, t_pixel **pixel, t_data *fdf)
{
	char *line;
	int	i;

	i = 0;
	line = get_next_line(fd);
	while (i < fdf->map.nbline)
	{
		if (!(pixel[i] = malloc(sizeof(t_pixel) * (fdf->map.nbcol))))
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
	t_pixel **pixel;
	
	count_col_line(argv, fdf);
	fdf->map.alt_max = 0;
	fdf->map.alt_min = 0;
	offset(fdf);
	if (!(pixel = malloc(sizeof(t_pixel*) * (fdf->map.nbline))))
		return ;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return ;
	fdf->map.pixel = save_map(fd, pixel, fdf);
	printf("alti: %d\n", fdf->map.alt_max - fdf->map.alt_min);
	printf("nbline: %d\n", fdf->map.nbline);
	printf("nbcol: %d\n", fdf->map.nbcol);
	printf("offset: %d\n", fdf->offset);
	reset_alti(fdf, fdf->map.alt_max - fdf->map.alt_min);
	if (close(fd) == -1)
		return ;
}
