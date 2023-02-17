/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:31:11 by jarthaud          #+#    #+#             */
/*   Updated: 2023/02/17 15:03:57 by jarthaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "../libft/libft.h"
#include "../mlx_linux/mlx.h"
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define RED_PIXEL 0xFF0000
#define WHITE_PIXEL 0xFFFFFF
#define GREEN_PIXEL 0xFF00
#define BLACK_PIXEL 0x252426

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1000

typedef struct s_coord
{
	int	x;
	int	y;
	int xmax;
	int ymax;
	int color;
}	t_coord;

typedef struct	s_map {
	int	**map;
	int	nbline;
	int	nbcol;
	int	x;
	int	y;
	// int	max;
	int	color;
}				t_map;

typedef struct	s_data {
	void			*mlx_ptr;
	void			*win_ptr;
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				win_length;
	int				win_width;
	int				keycode;
	int				proj;
	// struct s_color	color;
	struct s_map	map;
	struct s_coord	coord;
	// struct s_mov	mov;
}					t_data;

int	check_map(char *argv);
int check_fdf(char *str);
int	check_data_map(char *argv);
int	check_line(char *argv);
int	count_col(char *str, char c);
void error_message(int i);
int	create_map(char *argv, t_data *fdf);
int	count_col_line(char *argv, t_data *fdf);
int	**create_double_tab(size_t x, size_t y);
int	save_map(int fd, t_data *fdf);
void	img_pix_put(t_data *fdf, int x, int y, int color);
int	handle_keypress(int keysym, t_data *data);
int	render(t_data *fdf);
int	window(t_data *fdf);
int render_grid(t_data *fdf);

#endif
