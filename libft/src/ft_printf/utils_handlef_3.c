/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_handlef_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:57:59 by jbeall            #+#    #+#             */
/*   Updated: 2018/11/29 20:56:33 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_helper_f_nan(t_block *block)
{
	block->p = 0;
	block->p_flag = 1;
	block->zero_flag = 0;
	block->hash_flag = 0;
}

void	flag_manager_f(long double f, t_block *block)
{
	if (is_nan(f) || is_inf(f))
	{
		flag_helper_f_nan(block);
		if (is_nan(f))
		{
			block->plus_flag = 0;
			block->is_nan = 1;
		}
		else
		{
			block->is_inf = 1;
			if (f == -(1.0 / 0))
				block->is_neg = 1;
		}
	}
	if (block->minus_flag)
		block->zero_flag = 0;
	if (block->plus_flag)
		block->space_flag = 0;
	if (!block->p_flag)
	{
		block->p_flag = 1;
		block->p = 6;
	}
}

void	free_helper_f(t_block *block, char *big_s, char *little_s)
{
	if (!block->is_inf && !block->is_nan)
	{
		free(big_s);
		free(little_s);
	}
}
