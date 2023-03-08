/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:34:52 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/08 15:05:22 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv)
{
	t_data fdf;
	int i;

	i = 0;
	if (argc != 2)
		error_message(4);
	else if (check_map(argv[1]) == -1)
		return (-1);
	fill_map(argv[1], &fdf);
	window(fdf);
	while (i < fdf.map.nbline)
		free(fdf.map.pixel[i++]);
	free(fdf.map.pixel);
	return (0);
}