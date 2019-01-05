/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 20:06:43 by jbeall            #+#    #+#             */
/*   Updated: 2019/01/05 15:07:44 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_render_color(int color, t_mlx *mlx)
{
	mlx->def_color = color;
	set_map_color(mlx->mp, MIN_COLOR, color);
}

int		close_fdf(void)
{
	exit(0);
}

void	fdf_print_map(t_map *mp)
{
	int i;
	int j;

	i = 0;
	while (i < mp->rows)
	{
		j = 0;
		while (j < mp->cols)
			ft_printf("%2d ", mp->map[i][j++].z);
		ft_printf("\n");
		i++;
	}
}

void	key_set_color(int keycode, t_mlx *mlx)
{
	if (keycode == 23)
		set_render_color(MAX_COLOR, mlx);
	if (keycode == 22)
		set_render_color(0x900C3F, mlx);
	if (keycode == 26)
		set_render_color(0x3498DB, mlx);
	if (keycode == 28)
		set_render_color(0x28B463, mlx);
	if (keycode == 25)
		set_render_color(0x8E44AD, mlx);
}

int		scale_brightness(int color, double brightness)
{
	int new_color;

	new_color = 0;
	new_color += (0x0000FF & color) * brightness;
	new_color += (int)((0x0000FF & color >> 8) * brightness) << 8;
	new_color += (int)((0x0000FF & color >> 16) * brightness) << 16;
	return (new_color);
}
