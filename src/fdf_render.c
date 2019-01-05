/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 20:02:49 by jbeall            #+#    #+#             */
/*   Updated: 2019/01/05 14:40:24 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map_color(t_map *mp, int min_color, int max_color)
{
	t_point	z_min;
	t_point	z_max;
	int		i;
	int		j;

	i = 0;
	ft_bzero(&z_min, sizeof(z_min));
	ft_bzero(&z_max, sizeof(z_max));
	z_min.z = get_map_min(mp);
	z_max.z = get_map_max(mp);
	z_min.color = min_color;
	z_max.color = max_color;
	while (i < mp->rows)
	{
		j = -1;
		while (++j < mp->cols)
		{
			if (z_min.z == z_max.z)
				mp->map[i][j].color = z_min.color;
			else
				mp->map[i][j].color = get_color_z(mp->map[i][j].z,
					&z_min, &z_max);
		}
		++i;
	}
}

void	fdf_rotate(t_vector *v, t_cam *cam)
{
	double x;
	double y;
	double z;
	double temp_x;
	double temp_z;

	y = v->y * cos(cam->rotate_x) - v->z * sin(cam->rotate_x);
	z = sin(cam->rotate_x) * v->y + cos(cam->rotate_x) * v->z;
	temp_z = z;
	z = z * cos(cam->rotate_y) - v->x * sin(cam->rotate_y);
	x = v->x * cos(cam->rotate_y) + temp_z * sin(cam->rotate_y);
	temp_x = x;
	x = cos(cam->rotate_z) * x - sin(cam->rotate_z) * y;
	y = y * cos(cam->rotate_z) + temp_x * sin(cam->rotate_z);
	v->y = y;
	v->x = x;
	v->z = z;
}

t_point	fdf_project(t_point point, t_mlx *mlx)
{
	t_vector	v;
	t_point		new;

	v.x = point.x;
	v.y = point.y;
	v.z = point.z;
	v.x -= (double)mlx->mp->cols / 2.0;
	v.y -= (double)mlx->mp->rows / 2.0;
	v.x *= mlx->cam->scale;
	v.y *= mlx->cam->scale;
	v.z *= mlx->cam->scale;
	fdf_rotate(&v, mlx->cam);
	if (mlx->cam->persp_mode)
		fdf_persp(&v, mlx);
	v.x += mlx->cam->translate_x;
	v.y += mlx->cam->translate_y;
	new.x = v.x;
	new.y = v.y;
	new.z = v.z;
	new.color = point.color;
	return (new);
}

void	render(t_mlx *mlx)
{
	int i;
	int j;

	if (mlx->img.img)
		mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx->img.img = mlx_new_image(mlx->mlx, WINDOW_X, WINDOW_Y);
	mlx->img.buf = mlx_get_data_addr(mlx->img.img, &(mlx->img.bits_per_pixel),
		&(mlx->img.size_line), &(mlx->img.endian));
	i = -1;
	while (++i < mlx->mp->rows)
	{
		j = 0;
		while (j < mlx->mp->cols)
		{
			if (j < mlx->mp->cols - 1)
				plot_line_img(fdf_project(mlx->mp->map[i][j], mlx),
					fdf_project(mlx->mp->map[i][j + 1], mlx), mlx);
			if (i < mlx->mp->rows - 1)
				plot_line_img(fdf_project(mlx->mp->map[i][j], mlx),
					fdf_project(mlx->mp->map[i + 1][j], mlx), mlx);
			++j;
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img.img, 0, 0);
	mlx_string_put(mlx->mlx, mlx->window, 20, 20, mlx->def_color, WINDOW_NAME);
}

int		get_color_z(int z, t_point *a, t_point *b)
{
	int		r;
	int		g;
	int		blue;
	double	t;

	t = ((double)z - (double)a->z) / ((double)b->z - (double)a->z);
	r = ((a->color >> 16) & 0xFF) + (((b->color >> 16) & 0xFF) -
		((a->color >> 16) & 0xFF)) * t;
	g = ((a->color >> 8) & 0xFF) + (((b->color >> 8) & 0xFF) -
		((a->color >> 8) & 0xFF)) * t;
	blue = ((a->color >> 0) & 0xFF) + (((b->color >> 0) & 0xFF) -
		((a->color >> 0) & 0xFF)) * t;
	return (r << 16 | g << 8 | blue);
}
