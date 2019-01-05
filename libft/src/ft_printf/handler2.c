/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 14:26:34 by jbeall            #+#    #+#             */
/*   Updated: 2018/11/26 20:55:40 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			handle_u(t_block *block, va_list ap)
{
	unsigned long long int	n;
	char					*s;

	n = unsigned_handle_mod(block, ap);
	s = pf_dtoa_u(n, 10, 0);
	return (write_unsigned(block, n, s, NULL));
}

int			handle_o(t_block *block, va_list ap)
{
	unsigned long long int	n;
	char					*s;

	n = unsigned_handle_mod(block, ap);
	s = pf_dtoa_u(n, 8, 0);
	if (block->hash_flag)
	{
		block->p_flag = 1;
		if (!n)
			block->p = MAX(block->p, 1);
		else
			block->p = MAX(block->p, (int)ft_strlen(s) + 1);
	}
	return (write_unsigned(block, n, s, NULL));
}

int			handle_x(t_block *block, va_list ap)
{
	unsigned long long int	n;
	char					*s;
	char					*prepend;
	char					hex_char;

	n = unsigned_handle_mod(block, ap);
	hex_char = block->c == 6 ? 'a' : 'A';
	s = pf_dtoa_u(n, 16, hex_char);
	if (block->hash_flag && n)
	{
		prepend = block->c == 6 ? "0x" : "0X";
		block->prepend = 1;
	}
	return (write_unsigned(block, n, s, (block->prepend ? prepend : NULL)));
}

inline int	is_signed_conv(int c)
{
	if (c == 3)
		return (1);
	else
		return (0);
}

int			block_len(t_block *block, int len, char *prepend)
{
	int b_len;

	b_len = (block->p_flag && block->p > len ? block->p : len);
	b_len += (is_signed_conv(block->c) && (block->space_flag ||
		block->plus_flag || block->is_neg) ? 1 : 0);
	if (block->prepend)
		b_len += ft_strlen(prepend);
	return (b_len);
}
