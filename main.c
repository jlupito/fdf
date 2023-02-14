/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:34:52 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/14 16:09:58 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"

int	main(int argc, char **argv)
{
	t_env fdf;
	
	if (argc != 2)
		error_message(4);
	else if (check_map(argv[1]) == -1)
		return (-1);
	ft_bzero(&fdf, sizeof(t_env));
	create_map(argv[1], &fdf);
	return (0);
}