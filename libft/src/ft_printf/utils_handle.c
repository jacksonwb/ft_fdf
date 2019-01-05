/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 14:30:51 by jbeall            #+#    #+#             */
/*   Updated: 2018/11/26 21:18:47 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long int			signed_handle_mod(t_block *block, va_list ap)
{
	long long int n;

	if (block->mod == LL)
		n = va_arg(ap, long long int);
	else if (block->mod == L)
		n = va_arg(ap, long int);
	else if (block->mod == H)
		n = (short int)va_arg(ap, int);
	else if (block->mod == HH)
		n = (char)va_arg(ap, int);
	else
		n = (int)va_arg(ap, int);
	return (n);
}

unsigned long long int	unsigned_handle_mod(t_block *block, va_list ap)
{
	unsigned long long int n;

	if (block->mod == LL)
		n = va_arg(ap, unsigned long long int);
	else if (block->mod == L)
		n = va_arg(ap, unsigned long int);
	else if (block->mod == H)
		n = (unsigned short int)va_arg(ap, unsigned int);
	else if (block->mod == HH)
		n = (unsigned char)va_arg(ap, unsigned int);
	else
		n = (unsigned int)va_arg(ap, unsigned int);
	return (n);
}

char					set_sign(long long int n, t_block *block)
{
	char sign;

	sign = block->space_flag ? ' ' : '+';
	if (n < 0)
	{
		sign = '-';
		block->is_neg = 1;
	}
	return (sign);
}

void					flag_manager(t_block *block)
{
	if (block->p_flag || block->minus_flag)
		block->zero_flag = 0;
	if (block->plus_flag)
		block->space_flag = 0;
}

void					pad_block(t_block *block, int len, int b_len, int seg)
{
	if (!block->zero_flag && !block->minus_flag && block->width >
		b_len && seg == START)
		write_padding(block->width - b_len, ' ');
	else if (!block->zero_flag && block->minus_flag && block->width >
		b_len && seg == END)
		write_padding(block->width - b_len, ' ');
	else if (seg == ZEROS)
	{
		if (block->p_flag)
			write_padding(block->p > len ? block->p - len : 0, '0');
		else if (block->zero_flag && block->width)
			write_padding(block->width > b_len ? block->width - b_len : 0, '0');
	}
}
