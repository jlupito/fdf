/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarthaud <jarthaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:31:11 by jarthaud          #+#    #+#             */
/*   Updated: 2023/03/03 16:13:44 by jarthaud         ###   ########.fr       */
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
#define BLACK_PIXEL 0x000000

#define WINDOW_WIDTH 1800
#define WINDOW_HEIGHT 1200

typedef struct s_pixel {
	int	x;
	int	y;
	int	alti;
	int	color;
}			t_pixel;

typedef struct	s_map {
	t_pixel	**pixel;
	int		nbline;
	int		nbcol;
	int		x1;
	int 	y1;
	int		x2;
	int		y2;
	int		x3;
	int		y3;
	int		x4;
	int		y4;
	int 	dx;
    int 	dy;
    int 	err;
    int 	sx;
    int 	sy;
    int 	e2;
	int		win_width;
	int		win_height;
}				t_map;

typedef struct	s_data {
	void			*mlx_ptr;
	void			*win_ptr;
	void			*mlx_img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	struct s_map	map;
	int				proj;
	int				offset;
}					t_data;

int	check_map(char *argv);
int check_fdf(char *str);
int	check_data_map(char *argv);
int	check_line(char *argv);
int	count_col(char *str, char c);
int	handle_keypress(int keysym, t_data *fdf);
int	render(t_data *fdf);
int	window(t_data fdf);
int	get_color(char *str);
int	get_color_line(int color1, int color2);
t_pixel	*xyline(char *str, int count, t_pixel *pixel, t_data *fdf);
t_pixel	**save_map(int fd, t_pixel **pixel, t_data *fdf);
void	fill_map(char *argv, t_data *fdf);
void	render_background(t_data *fdf, int color);
void	render_grid(t_data *fdf);
void 	error_message(int i);
void	count_col_line(char *argv, t_data *fdf);
void	img_pix_put(t_data *fdf, int x, int y, int color);
void	render_grid(t_data *fdf);
void 	bresenham(t_data *fdf, int color1, int color2, int flag);
void    prep_bresenham(t_data *fdf);
void    draw_line(t_data *fdf);
void    draw_column(t_data *fdf);
void	offset(t_data *fdf);
void	position_map(t_data *fdf);

#endif

// void proj(t_data *fdf, int i, int j);
// int	calculate_rotate(int degree, s_coord coord);
// void	create_map(char *argv, t_data *fdf);
// int	**create_double_tab(size_t x, size_t y);
// t_pixel	**get_pixel(t_data *fdf, t_pixel **pixel);
// void	set_pixel(t_data *fdf);
// char	**save_map(int fd, t_data *fdf);