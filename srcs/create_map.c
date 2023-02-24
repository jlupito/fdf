/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:46:32 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/24 11:35:51 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_map	*count_col_line(char *argv, t_data *fdf)
{
	char *line;
	int	fd;

	fdf->map->nbline = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	fdf->map->nbcol = count_col(line, ' ');
	while (line != NULL)
	{
		fdf->map->nbline++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (close(fd) == -1)
		return (NULL);
	return (fdf->map);
}

char	**save_map(int fd, t_data *fdf)
{
	char *line;
	int	i;
	int	j;
	
	fdf->map->tabtab[fdf->map->nbline] = NULL;
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		if (!(fdf->map->tabtab[i] = malloc(sizeof(char) * (ft_strlen(line) + 1))))
			return (NULL);
		j = 0;
		while (line[j])
		{
			fdf->map->tabtab[i][j] = line[j];
			j++;	
		}
		fdf->map->tabtab[i][j] = '\0';
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free (line);
	return (fdf->map->tabtab);
}

t_data	*create_map(char *argv, t_data *fdf)
{
	int		fd;
	
	fdf->map = count_col_line(argv, fdf);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if(!(fdf->map->tabtab = malloc(sizeof(char*) * (fdf->map->nbline + 3))))
		return (NULL);
	fdf->map->tabtab = save_map(fd, fdf);
	if (close(fd) == -1)
		return (NULL);
	return (fdf);
}