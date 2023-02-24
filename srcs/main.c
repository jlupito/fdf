/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:34:52 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/24 12:08:06 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv)
{
	t_data *fdf;

	if (argc != 2)
		error_message(4);
	else if (check_map(argv[1]) == -1)
		return (-1);
	if (!(fdf = malloc(sizeof(t_data))))
		return (-1);
	if (!(fdf->map = malloc(sizeof(t_map))))
		return (-1);
	fdf = create_map(argv[1], fdf);
	window(fdf);
	free(fdf->map->tabtab[0]);
	free(fdf->map->tabtab);
	free(fdf);
	return (0);
}