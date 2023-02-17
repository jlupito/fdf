/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:34:52 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/17 10:56:35 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv)
{
	t_data fdf;
	
	if (argc != 2)
		error_message(4);
	else if (check_map(argv[1]) == -1)
		return (-1);
	ft_bzero(&fdf, sizeof(t_data));
	create_map(argv[1], &fdf);
	window(&fdf);
	free(*(fdf.map.map));
	ft_bzero(&fdf, sizeof(t_data));
	return (0);
}