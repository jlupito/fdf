/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:23:48 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/24 11:09:31 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_color(char *str)
{
    int i;
	int	len;
    int val;

	val = 0;
	i = 0;
	while (str[i] != 'x')
		i++;
	len = i;
	while (str[len] != ' ' && str[len])
		len++;
	while (i++ < len)
	{
    	if (str[i] <= 57)
        	val += (str[i] - 48) * (1 << (4 * (len - 1 - i)));
    	else
        	val += (str[i] - 55) * (1 << (4 * (len - 1 - i)));
	}
	return (val);
}
