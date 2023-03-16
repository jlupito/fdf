/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:36:58 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/15 12:53:18 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	error_message(int i)
{
	if (i == 1)
		ft_putendl_fd("Map is not .fdf format", 2);
	if (i == 2)
		ft_putendl_fd("Map is empty", 2);
	if (i == 3)
		ft_putendl_fd("Map lines are unconsistent", 2);
	if (i == 4)
		ft_putendl_fd("No map submitted", 2);
}
