/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:34:06 by jbeall            #+#    #+#             */
/*   Updated: 2018/11/29 11:35:21 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_star_width(t_block *block, va_list ap, int star_flag)
{
	int garbage;

	if (!block->width || !star_flag)
	{
		block->width = va_arg(ap, int);
		if (block->width < 0)
		{
			block->width = -block->width;
			block->minus_flag = 1;
		}
		return (1);
	}
	else
	{
		garbage = va_arg(ap, int);
		return (star_flag);
	}
}
