/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 11:55:49 by jbeall            #+#    #+#             */
/*   Updated: 2019/01/05 15:13:18 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "ft_printf.h"
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define WINDOW_X 1000
# define WINDOW_Y 640
# define WINDOW_NAME "FdF"
# define DEF_SCALE 20
# define FOCAL_L 1000
# define FOCAL_MAX 5000
# define FOCAL_MIN 300
# define MAX_COLOR 0xFFA367
# define MIN_COLOR 0xFFFFFF
# define M_BUTTON_1 1
# define M_BUTTON_2 2
# define DEF_ROT_X -0.52;
# define DEF_ROT_Y 0.52;
# define DEF_ROT_Z 0.52;

typedef struct	s_vector
{
	double x;
	double y;
	double z;
}				t_vector;

typedef struct	s_point
{
	int	x;
	int	y;
	int z;
	int color;
}				t_point;

typedef struct	s_line
{
	int			x;
	int			x1;
	int			y;
	int			y1;
	double		slope;
	double		x_d;
	double		y_d;
}				t_line;

typedef struct	s_img
{
	void		*img;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*buf;
}				t_img;

typedef struct	s_cam
{
	double		translate_x;
	double		translate_y;
	double		rotate_x;
	double		rotate_y;
	double		rotate_z;
	double		scale;
	double		focal_length;
	int			persp_mode;
}				t_cam;

typedef struct	s_map
{
	t_point		**map;
	int			rows;
	int			cols;
	int			z_min;
	int			z_max;
}				t_map;

typedef struct	s_mouse
{
	int			x;
	int			y;
	int			lastx;
	int			lasty;
	int			isdown;
}				t_mouse;

typedef struct	s_mlx
{
	void		*mlx;
	void		*window;
	t_map		*mp;
	t_img		img;
	t_cam		*cam;
	t_mouse		mouse;
	int			def_color;
}				t_mlx;

/*
** fd_parse
*/
void			add_line(t_list **lst, char **line_split);
int				input_lst(t_list **lst, int fd);
int				*atoi_map(char **line_split, int len);
void			lst_map(t_map *mp, t_list *lst);
void			fdf_parse(char *arg, t_map *mp);
int				fdf_count_row(char **line_split);
void			fdf_free_lst(t_list *lst);
void			fdf_die(char *msg);

/*
**fdf_draw
*/

int				ipart_double(double x);
double			fpart_double(double x);
double			rfpart_double(double x);
int				get_color_x(int x, t_point *a, t_point *b);
int				get_color_y(int y, t_point *a, t_point *b);
int				draw_pixel_img(t_point *point, t_mlx *mlx);
void			packet_point(t_point *new, int x, int y, int color);
int				plot_line_img(t_point a, t_point b, t_mlx *mlx);

/*
** fdf_events
*/
int				key_press(int keycode, t_mlx *mlx);
int				close_fdf(void);
int				mouse_release(int button, int x, int y, t_mlx *mlx);
int				mouse_press(int button, int x, int y, t_mlx *mlx);
int				mouse_move(int x, int y, t_mlx *mlx);
void			fdf_print_map(t_map *mp);
void			set_render_color(int color, t_mlx *mlx);
void			fdf_persp(t_vector *v, t_mlx *mlx);

/*
** fdf_render
*/
void			render(t_mlx *mlx);
void			fdf_rotate(t_vector *v, t_cam *cam);
t_point			fdf_project(t_point point, t_mlx *mlx);
void			set_map_color(t_map *mp, int min_color, int max_color);
int				get_color_z(int z, t_point *a, t_point *b);

/*
** fdf_utils
*/
void			set_render_color(int color, t_mlx *mlx);
void			fdf_print_map(t_map *mp);
void			key_set_color(int keycode, t_mlx *mlx);
int				scale_brightness(int color, double brightness);

int				get_map_max(t_map *mp);
int				get_map_min(t_map *mp);
#endif
