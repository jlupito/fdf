/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:31:11 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/14 17:30:36 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include <math.h>
# include "./mlx_linux/mlx.h"

typedef struct	s_map {
	int	**map;
	int	nbline;
	int	nbcol;
	int	x;
	int	y;
	int	max;
	int	color;
}				t_map;

typedef struct	s_env {
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	int				win_length;
	int				win_width;
	int				keycode;
	int				proj;
	// struct s_color	color;
	struct s_map	map;
	// struct s_point	point;
	// struct s_mov	mov;
}					t_env;

int	check_map(char *argv);
int check_fdf(char *str);
int	check_data_map(char *argv);
int	check_line(char *argv);
int	count_col(char *str, char c);
void error_message(int i);
int	create_map(char *argv, t_env *fdf);
int	count_col_line(char *argv, t_env *fdf);
int	**create_double_tab(size_t x, size_t y);
int	save_map(int fd, t_env *fdf);

#endif
