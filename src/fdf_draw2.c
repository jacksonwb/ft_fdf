/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 20:10:26 by jbeall            #+#    #+#             */
/*   Updated: 2019/01/04 20:19:20 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ipart_double(double x)
{
	return ((int)x);
}

double	fpart_double(double x)
{
	return (x > 0 ? (x - floor(x)) : (x - ceil(x)));
}

double	rfpart_double(double x)
{
	return (1 - fpart_double(x));
}

int		get_color_x(int x, t_point *a, t_point *b)
{
	int		r;
	int		g;
	int		blue;
	double	t;

	t = ((double)x - (double)a->x) / ((double)b->x - (double)a->x);
	r = ((a->color >> 16) & 0xFF) + (((b->color >> 16) & 0xFF) -
		((a->color >> 16) & 0xFF)) * t;
	g = ((a->color >> 8) & 0xFF) + (((b->color >> 8) & 0xFF) -
		((a->color >> 8) & 0xFF)) * t;
	blue = ((a->color >> 0) & 0xFF) + (((b->color >> 0) & 0xFF) -
		((a->color >> 0) & 0xFF)) * t;
	return (r << 16 | g << 8 | blue);
}

int		get_color_y(int y, t_point *a, t_point *b)
{
	int		r;
	int		g;
	int		blue;
	double	t;

	t = ((double)y - (double)a->y) / ((double)b->y - (double)a->y);
	r = ((a->color >> 16) & 0xFF) + (((b->color >> 16) & 0xFF) -
		((a->color >> 16) & 0xFF)) * t;
	g = ((a->color >> 8) & 0xFF) + (((b->color >> 8) & 0xFF) -
		((a->color >> 8) & 0xFF)) * t;
	blue = ((a->color >> 0) & 0xFF) + (((b->color >> 0) & 0xFF) -
		((a->color >> 0) & 0xFF)) * t;
	return (r << 16 | g << 8 | blue);
}
