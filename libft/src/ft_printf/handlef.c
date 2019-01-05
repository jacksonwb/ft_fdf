/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlef.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 14:28:54 by jbeall            #+#    #+#             */
/*   Updated: 2018/11/29 20:55:12 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pad_block_f(int len, t_block *block, int seg)
{
	if (!block->zero_flag && !block->minus_flag && block->width >
		len && seg == START)
		write_padding(block->width - len, ' ');
	else if (!block->zero_flag && block->minus_flag && block->width >
		len && seg == END)
		write_padding(block->width - len, ' ');
	else if (seg == ZEROS)
	{
		if (block->zero_flag && block->width)
			write_padding(block->width > len ? block->width - len : 0, '0');
	}
}

int		block_len_f(char *big_s, t_block *block)
{
	int len;

	if (block->is_inf || block->is_nan)
		len = 3;
	else
		len = ft_strlen(big_s) + block->p;
	if (block->p > 0 || block->hash_flag)
		len += 1;
	if (block->space_flag || block->plus_flag)
		len += 1;
	return (len);
}

char	set_sign_f(long double f, t_block *block)
{
	char sign;

	sign = block->space_flag ? ' ' : '+';
	if (f < 0)
	{
		sign = '-';
		block->is_neg = 1;
	}
	return (sign);
}

int		write_f(t_block *block, char sign, char *big_s, char *little_s)
{
	int len;

	len = block_len_f(big_s, block);
	pad_block_f(len, block, START);
	if (block->space_flag || block->plus_flag || block->is_neg)
		write(1, &sign, 1);
	pad_block_f(len, block, ZEROS);
	write(1, big_s, ft_strlen(big_s));
	if (block->p || block->hash_flag)
		write(1, ".", 1);
	write(1, little_s, ft_strlen(little_s));
	pad_block_f(len, block, END);
	return (len);
}

int		handle_f(t_block *block, va_list ap)
{
	long double	f;
	char		*little_s;
	char		*big_s;
	char		sign;
	int			len;

	f = float_handle_mod(block, ap);
	flag_manager_f(f, block);
	sign = set_sign_f(f, block);
	if (!block->is_inf && !block->is_nan)
	{
		f = ft_round(f, block);
		big_s = big_f(f);
		little_s = little_f(f, block->p, big_s);
	}
	else
	{
		big_s = block->is_inf ? "inf" : "nan";
		little_s = "";
	}
	len = write_f(block, sign, big_s, little_s);
	free_helper_f(block, big_s, little_s);
	return (MAX(block->width, len));
}
