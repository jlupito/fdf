/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:49:41 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/27 10:52:37 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int check_fdf(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '.' && argv[i])
		i++;
	if (argv[i + 1] == 'f' && argv[i + 2] == 'd' && argv[i + 3] == 'f' && argv[i + 4] == '\0')
		return (0);
	else
		return (error_message(1), -1);
}

int	check_data_map(char *argv)
{
	int	fd;
	char *line;
	
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (line == NULL)
		return (error_message(2), -1);
	while(line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	check_line(char *argv)
{
	int	fd;
	int	flag;
	int col;
	char *line;

	flag = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	col = count_col(line, ' ');
	while (line != NULL)
	{
		if (count_col(line, ' ') != col)
			flag = 1;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (close(fd) == -1)
		return (-1);
	if (flag == 1)
		return (error_message(3), -1);
	return (0);
}

int	check_map(char *argv)
{
	if (check_fdf(argv) == -1)
		return (-1);
	if (check_data_map(argv) == -1)
		return (-1);
	if (check_line(argv) == -1)
		return (-1);
	return (0);
}





// t_pixel **pixel

// pixel[i][j].x 100;
// pixel[i][j].y = 120;
// pixel[i][j].nb = ft_atoi(nb);
// pixel[i][j].color = getcolor(str);

// 162604