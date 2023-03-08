/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:55:56 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/08 17:11:57 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	count_col(char *str, char c)
{
	int i;
	int col;

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
	if (close(fd) == -1)
		return ;
}

void	reset_alti(t_data *fdf, int alti)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	{
		i = 0;
		while (i < fdf->map.nbline)
		{
			j = 0;
			while (j < fdf->map.nbcol)
			{
				// if (alti < 50)
				// 	fdf->map.pixel[i][j].alti *= 1.5;
				if (alti >= 50 && alti < 100)
					fdf->map.pixel[i][j].alti /= 2;
				if (alti >= 100 && alti < 150)
					fdf->map.pixel[i][j].alti /= 6;
				if (alti >= 150 && alti < 250)
					fdf->map.pixel[i][j].alti /= 8;
				if (alti >= 250 && alti < 350)
					fdf->map.pixel[i][j].alti /= 10;
				if (alti >= 350)
					fdf->map.pixel[i][j].alti /= 12;
				j++;
			}
			i++;
		}
	}
}

