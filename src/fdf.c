/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 11:49:31 by jbeall            #+#    #+#             */
/*   Updated: 2019/01/05 15:24:14 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_map_min(t_map *mp)
{
	int i;
	int j;
	int z_min;

	i = 0;
	z_min = mp->map[0][0].z;
	while (i < mp->rows)
	{
		j = 0;
		while (j < mp->cols)
		{
			z_min = z_min <= mp->map[i][j].z ? z_min : mp->map[i][j].z;
			++j;
		}
		++i;
	}
	return (z_min);
}

int		get_map_max(t_map *mp)
{
	int i;
	int j;
	int z_max;

	i = 0;
	z_max = mp->map[0][0].z;
	while (i < mp->rows)
	{
		j = 0;
		while (j < mp->cols)
		{
			z_max = z_max >= mp->map[i][j].z ? z_max : mp->map[i][j].z;
			++j;
		}
		++i;
	}
	return (z_max);
}

void	fdf_init_mlx(t_mlx *mlx)
{
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, WINDOW_X, WINDOW_Y, WINDOW_NAME);
	mlx->mp = (t_map*)ft_memalloc(sizeof(t_map));
	mlx->cam = (t_cam*)ft_memalloc(sizeof(t_cam));
	mlx->def_color = MAX_COLOR;
}

void	fdf_init_cam(t_mlx *mlx)
{
	mlx->cam->translate_x = WINDOW_X / 2;
	mlx->cam->translate_y = WINDOW_Y / 2;
	mlx->cam->rotate_x = DEF_ROT_X;
	mlx->cam->rotate_y = DEF_ROT_Y;
	mlx->cam->rotate_z = DEF_ROT_Z;
	mlx->cam->scale = DEF_SCALE;
	mlx->cam->persp_mode = 0;
	mlx->cam->focal_length = FOCAL_L;
}

int		main(int argc, char **argv)
{
	t_mlx mlx;

	if (argc != 2)
		die("usage: fdf [map]");
	fdf_init_mlx(&mlx);
	fdf_init_cam(&mlx);
	fdf_parse(argv[1], mlx.mp);
	set_map_color(mlx.mp, MIN_COLOR, MAX_COLOR);
	render(&mlx);
	mlx_key_hook(mlx.window, &key_press, &mlx);
	mlx_hook(mlx.window, 4, 0, &mouse_press, &mlx);
	mlx_hook(mlx.window, 5, 0, &mouse_release, &mlx);
	mlx_hook(mlx.window, 6, 1L << 6, &mouse_move, &mlx);
	mlx_hook(mlx.window, 17, (1L < 17), &close_fdf, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
