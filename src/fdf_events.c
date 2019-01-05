/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 15:46:55 by jbeall            #+#    #+#             */
/*   Updated: 2019/01/05 15:14:05 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_set_proj(int keycode, t_mlx *mlx)
{
	if (keycode == 18)
	{
		mlx->cam->rotate_x = 0;
		mlx->cam->rotate_y = 0;
		mlx->cam->rotate_z = 0;
	}
	if (keycode == 19)
	{
		mlx->cam->rotate_x = 1.5708;
		mlx->cam->rotate_y = 0;
		mlx->cam->rotate_z = 0;
	}
	if (keycode == 20)
	{
		mlx->cam->rotate_x = 0;
		mlx->cam->rotate_y = 1.5708;
		mlx->cam->rotate_z = 0;
	}
	if (keycode == 21 && (mlx->cam->scale = DEF_SCALE))
	{
		mlx->cam->rotate_x = DEF_ROT_X;
		mlx->cam->rotate_y = DEF_ROT_Y;
		mlx->cam->rotate_z = DEF_ROT_Z;
		mlx->cam->focal_length = FOCAL_L;
	}
}

int		key_press(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 124)
		mlx->cam->rotate_z += 0.1;
	if (keycode == 123)
		mlx->cam->rotate_z -= 0.1;
	if (keycode == 125)
		mlx->cam->scale -= 1;
	if (keycode == 126)
		mlx->cam->scale += 1;
	if (keycode == 35)
		mlx->cam->persp_mode ^= 1;
	if (keycode == 24 && mlx->cam->focal_length < FOCAL_MAX)
		mlx->cam->focal_length += 100;
	if (keycode == 27 && mlx->cam->focal_length > FOCAL_MIN)
		mlx->cam->focal_length -= 100;
	key_set_proj(keycode, mlx);
	key_set_color(keycode, mlx);
	render(mlx);
	return (0);
}

int		mouse_release(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (button == 1)
		mlx->mouse.isdown ^= M_BUTTON_1;
	if (button == 2)
		mlx->mouse.isdown ^= M_BUTTON_2;
	return (0);
}

int		mouse_press(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (button == 1)
		mlx->mouse.isdown |= M_BUTTON_1;
	if (button == 2)
		mlx->mouse.isdown |= M_BUTTON_2;
	return (0);
}

int		mouse_move(int x, int y, t_mlx *mlx)
{
	mlx->mouse.lastx = mlx->mouse.x;
	mlx->mouse.lasty = mlx->mouse.y;
	mlx->mouse.x = x;
	mlx->mouse.y = y;
	if (mlx->mouse.isdown & M_BUTTON_1)
	{
		mlx->cam->rotate_x -= (mlx->mouse.lasty - y) / 200.0;
		mlx->cam->rotate_y += (mlx->mouse.lastx - x) / 200.0;
	}
	if (mlx->mouse.isdown & M_BUTTON_2)
	{
		mlx->cam->scale += (mlx->mouse.lasty - y) / 2.0;
		if (mlx->cam->scale < 0)
			mlx->cam->scale = 0;
	}
	render(mlx);
	return (0);
}
