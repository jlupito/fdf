/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:46:32 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/17 10:01:17 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// faire un GNL et dans une structure:
// stocker les les donnees dans un double tableau
// compter et stocker le nb de colonnes avec split
// compter et stocker le nb de lignes
// si couleur: stoker la couleur


int	count_col_line(char *argv, t_data *fdf)
{
	char *line;
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (-1);
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
		return (-1);
	return (0);
}

int	save_map(int fd, t_data *fdf)
{
	char **line_alti;
	char *line;
	
	if (!(fdf->map.map = create_double_tab(fdf->map.nbcol, fdf->map.nbline)))
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		fdf->map.x = 0;
		line_alti = ft_split(line, ' ');
		while (line_alti[fdf->map.x] != NULL)
		{
			fdf->map.map[fdf->map.y][fdf->map.x] = ft_atoi(line_alti[fdf->map.x]);
			free(line_alti[fdf->map.x]);
			fdf->map.x++;
		}
		free(line);
		line = get_next_line(fd);
		fdf->map.y++;
	}
	// int i = 0;
	// int j = 0;
	// while (i < fdf->map.nbline)
	// {
	// 	j = 0;
	// 	while (j < fdf->map.nbcol)
	// 	{
	// 		printf("altitude: %d\n", fdf->map.map[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
	free (line);
	return (0);
}

int	create_map(char *argv, t_data *fdf)
{
	int		fd;
	
	count_col_line(argv, fdf);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (-1);
	save_map(fd, fdf);
	if (close(fd) == -1)
		return (-1);
	return (0);
}