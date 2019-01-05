/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 12:30:34 by jbeall            #+#    #+#             */
/*   Updated: 2019/01/04 20:17:25 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		draw_pixel_img(t_point *point, t_mlx *mlx)
{
	unsigned int c;
	unsigned int p;

	c = mlx_get_color_value(mlx->mlx, point->color);
	p = point->y * mlx->img.size_line + point->x * mlx->img.bits_per_pixel / 8;
	*((unsigned int*)(mlx->img.buf + p)) = c;
	return (0);
}

void	packet_point(t_point *new, int x, int y, int color)
{
	new->y = y;
	new->x = x;
	new->color = color;
}

void	plot_in_y(t_line vals, t_point *a, t_point *b, t_mlx *mlx)
{
	t_point new;

	while (vals.y < vals.y1 && vals.y < WINDOW_Y)
	{
		vals.x_d = ((double)(vals.y - a->y) / vals.slope) + a->x;
		vals.x_d = vals.x_d < 1 ? 1 : vals.x_d;
		if (vals.y < WINDOW_Y && vals.y > 0 && vals.x_d < WINDOW_X &&
			vals.x_d > 1)
		{
			packet_point(&new, vals.x_d, vals.y,
		scale_brightness(get_color_y(vals.y, a, b), fpart_double(vals.x_d)));
			draw_pixel_img(&new, mlx);
			packet_point(&new, vals.x_d - 1, vals.y,
		scale_brightness(get_color_y(vals.y, a, b), rfpart_double(vals.x_d)));
			draw_pixel_img(&new, mlx);
		}
		++vals.y;
	}
}

void	plot_in_x(t_line vals, t_point *a, t_point *b, t_mlx *mlx)
{
	t_point new;

	while (vals.x < vals.x1 && vals.x < WINDOW_X)
	{
		vals.y_d = a->y + (double)(vals.x - a->x) * vals.slope;
		vals.y_d = vals.y_d < 1 ? 1 : vals.y_d;
		if (vals.y_d < WINDOW_Y && vals.y_d > 0 && vals.x < WINDOW_X &&
			vals.x > 0)
		{
			packet_point(&new, vals.x, vals.y_d,
		scale_brightness(get_color_x(vals.x, a, b), fpart_double(vals.y_d)));
			draw_pixel_img(&new, mlx);
			packet_point(&new, vals.x, vals.y_d - 1,
		scale_brightness(get_color_x(vals.x, a, b), rfpart_double(vals.y_d)));
			draw_pixel_img(&new, mlx);
		}
		++vals.x;
	}
}

int		plot_line_img(t_point a, t_point b, t_mlx *mlx)
{
	t_line	vals;

	vals.slope = ((double)b.y - (double)a.y) / ((double)b.x - (double)a.x);
	vals.x = a.x < b.x ? a.x : b.x;
	vals.x1 = a.x > b.x ? a.x : b.x;
	vals.y1 = a.y > b.y ? a.y : b.y;
	vals.y = a.y < b.y ? a.y : b.y;
	if (fabs(vals.slope) > 1)
	{
		plot_in_y(vals, &a, &b, mlx);
		return (0);
	}
	plot_in_x(vals, &a, &b, mlx);
	return (0);
}
