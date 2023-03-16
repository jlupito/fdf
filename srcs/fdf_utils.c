/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:55:56 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/15 11:44:50 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	count_col(char *str, char c)
{
	int	i;
	int	col;

	i = 0;
	col = 0;
	while (str[i] != '\n' && str[i])
	{
		if (str[i] != c)
		{
			col++;
			while (str[i] != c && str[i] != '\n')
				i++;
		}
		if (str[i] == c)
			i++;
	}
	return (col);
}

void	count_col_line(char *argv, t_data *fdf)
{
	char	*line;
	int		fd;

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
	if (close(fd) == -1)
		return ;
}

void	offset(t_data *fdf)
{
	fdf->horizontal = 0;
	fdf->vertical = 0;
	if (fdf->map.nbcol <= 20)
		fdf->offset = 25;
	else if (fdf->map.nbcol >= 20 && fdf->map.nbcol < 50)
		fdf->offset = 20;
	else if (fdf->map.nbcol >= 50 && fdf->map.nbcol < 100)
		fdf->offset = 15;
	else if (fdf->map.nbcol >= 100 && fdf->map.nbcol < 200)
		fdf->offset = 8;
	else if (fdf->map.nbcol >= 200 && fdf->map.nbcol < 500)
		fdf->offset = 5;
	else
		fdf->offset = 2;
}

void	reset_alti(t_data *fdf, int alti)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.nbline)
	{
		j = 0;
		while (j < fdf->map.nbcol)
		{
			if (alti >= 50 && alti < 100)
				fdf->map.pixel[i][j].alti /= 1.5;
			if (alti >= 100 && alti < 150)
				fdf->map.pixel[i][j].alti /= 2;
			if (alti >= 150 && alti < 250)
				fdf->map.pixel[i][j].alti /= 3;
			if (alti >= 250 && alti < 350)
				fdf->map.pixel[i][j].alti /= 4;
			if (alti >= 350)
				fdf->map.pixel[i][j].alti /= 5;
			j++;
		}
	i++;
	}
}
