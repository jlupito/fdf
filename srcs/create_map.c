/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:46:32 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/03 16:23:26 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// void	position_map(t_data *fdf)
// {
// 	if (fdf->map.nbcol / fdf->map.nbline > 1 && fdf->map.nbcol / fdf->map.nbline > 1)
// 		fdf->win_width = 25;
// 	else if (fdf->map.nbcol >= 20 && fdf->map.nbcol <= 50)
// 		fdf->win_width = 20;
// 	else if (fdf->map.nbcol >= 50 && fdf->map.nbcol <= 100)
// 		fdf->win_width = 15;
// 	else if (fdf->map.nbcol >= 100 && fdf->map.nbcol <= 200)
// 		fdf->win_width = 5;
// 	else
// 		fdf->win_width = 1;
// }

void	offset(t_data *fdf)
{
	if (fdf->map.nbcol <= 20)
		fdf->offset = 25;
	else if (fdf->map.nbcol >= 20 && fdf->map.nbcol <= 50)
		fdf->offset = 20;
	else if (fdf->map.nbcol >= 50 && fdf->map.nbcol <= 100)
		fdf->offset = 15;
	else if (fdf->map.nbcol >= 100 && fdf->map.nbcol <= 200)
		fdf->offset = 5;
	else
		fdf->offset = 1;
}

void	count_col_line(char *argv, t_data *fdf)
{
	char *line;
	int	fd;

	fdf->map.nbcol = 0;
	fdf->map.nbline = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	fdf->map.nbcol = count_col(line, ' ');
	while (line != NULL)
	{
		fdf->map.nbline++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	printf("col: %d\n", fdf->map.nbcol);
	printf("line: %d\n", fdf->map.nbline);
	if (close(fd) == -1)
		return ;
}

t_pixel	*xyline(char *str, int count, t_pixel *pixel, t_data *fdf)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (j < fdf->map.nbcol)
	{
		while (str[i] == ' ' && str[i])
			i++;
		pixel[j].alti = ft_atoi(&str[i]) * (fdf->offset / 2);
		pixel[j].x = (WINDOW_WIDTH / 2) + (j * fdf->offset); // - (count * 10);
		pixel[j].y = (WINDOW_HEIGHT / 4) + (count * fdf->offset); // - (pixel[j].alti * 5);
		pixel[j].color = get_color(&str[i]);
		while (str[i] != ' ' && str[i])
			i++;
		j++;
		
	}
	return (pixel);
}

t_pixel	**save_map(int fd, t_pixel **pixel, t_data *fdf)
{
	char *line;
	int	count;

	count = 0;
	line = get_next_line(fd);
	while (count < fdf->map.nbline)
	{
		if (!(pixel[count] = malloc(sizeof(t_pixel) * (fdf->map.nbcol))))
			return (NULL);
		pixel[count] = xyline(line, count, pixel[count], fdf);
		count++;
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
	offset(fdf);
	// position_map(fdf);
	if (!(pixel = malloc(sizeof(t_pixel*) * (fdf->map.nbline))))
		return ;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return ;
	fdf->map.pixel = save_map(fd, pixel, fdf);
	if (close(fd) == -1)
		return ;
}
